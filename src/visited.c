#include "visited.h"
#include "app.h"

#include <the_Foundation/file.h>
#include <the_Foundation/path.h>
#include <the_Foundation/sortedarray.h>

static const size_t maxAgeVisited_Visited_ = 3600 * 24 * 30; /* one month */

void init_VisitedUrl(iVisitedUrl *d) {
    initCurrent_Time(&d->when);
    init_String(&d->url);
}

void deinit_VisitedUrl(iVisitedUrl *d) {
    deinit_String(&d->url);
}

static int cmpUrl_VisitedUrl_(const void *a, const void *b) {
    return cmpString_String(&((const iVisitedUrl *) a)->url, &((const iVisitedUrl *) b)->url);
}

static int cmpNewer_VisitedUrl_(const void *insert, const void *existing) {
    return seconds_Time(&((const iVisitedUrl *) insert  )->when) >
           seconds_Time(&((const iVisitedUrl *) existing)->when);
}

/*----------------------------------------------------------------------------------------------*/

struct Impl_Visited {
    iSortedArray visited;
};

iDefineTypeConstruction(Visited)

void init_Visited(iVisited *d) {
    init_SortedArray(&d->visited, sizeof(iVisitedUrl), cmpUrl_VisitedUrl_);
}

void deinit_Visited(iVisited *d) {
    clear_Visited(d);
    deinit_SortedArray(&d->visited);
}

void save_Visited(const iVisited *d, const char *dirPath) {
    iString *line = new_String();
    iFile *f = newCStr_File(concatPath_CStr(dirPath, "visited.txt"));
    if (open_File(f, writeOnly_FileMode | text_FileMode)) {
        iConstForEach(Array, i, &d->visited.values) {
            const iVisitedUrl *item = i.value;
            iDate date;
            init_Date(&date, &item->when);
            format_String(line,
                          "%04d-%02d-%02dT%02d:%02d:%02d %s\n",
                          date.year,
                          date.month,
                          date.day,
                          date.hour,
                          date.minute,
                          date.second,
                          cstr_String(&item->url));
            writeData_File(f, cstr_String(line), size_String(line));
        }
    }
    iRelease(f);
    delete_String(line);
}

void load_Visited(iVisited *d, const char *dirPath) {
    iFile *f = newCStr_File(concatPath_CStr(dirPath, "visited.txt"));
    if (open_File(f, readOnly_FileMode | text_FileMode)) {
        const iRangecc src  = range_Block(collect_Block(readAll_File(f)));
        iRangecc       line = iNullRange;
        iTime          now;
        initCurrent_Time(&now);
        while (nextSplit_Rangecc(&src, "\n", &line)) {
            int y, m, D, H, M, S;
            sscanf(line.start, "%04d-%02d-%02dT%02d:%02d:%02d ", &y, &m, &D, &H, &M, &S);
            if (!y) break;
            iVisitedUrl item;
            init_VisitedUrl(&item);
            init_Time(
                &item.when,
                &(iDate){ .year = y, .month = m, .day = D, .hour = H, .minute = M, .second = S });
            if (secondsSince_Time(&now, &item.when) > maxAgeVisited_Visited_) {
                continue; /* Too old. */
            }
            initRange_String(&item.url, (iRangecc){ line.start + 20, line.end });
            insert_SortedArray(&d->visited, &item);
        }
    }
    iRelease(f);
}

void clear_Visited(iVisited *d) {
    iForEach(Array, v, &d->visited.values) {
        deinit_VisitedUrl(v.value);
    }
    clear_SortedArray(&d->visited);
}

void visitUrl_Visited(iVisited *d, const iString *url) {
    iVisitedUrl visit;
    init_VisitedUrl(&visit);
    set_String(&visit.url, url);
    size_t pos;
    if (locate_SortedArray(&d->visited, &visit, &pos)) {
        iVisitedUrl *old = at_SortedArray(&d->visited, pos);
        if (cmpNewer_VisitedUrl_(&visit, old)) {
            old->when = visit.when;
            deinit_VisitedUrl(&visit);
            return;
        }
    }
    insert_SortedArray(&d->visited, &visit);
}

iTime urlVisitTime_Visited(const iVisited *d, const iString *url) {
    iVisitedUrl item;
    size_t pos;
    iZap(item);
    initCopy_String(&item.url, url);
    if (locate_SortedArray(&d->visited, &item, &pos)) {
        item.when = ((const iVisitedUrl *) constAt_SortedArray(&d->visited, pos))->when;
    }
    deinit_String(&item.url);
    return item.when;
}
