/* Copyright 2020 Jaakko Keränen <jaakko.keranen@iki.fi>

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. */

#pragma once

#include <the_Foundation/rect.h>
#include <the_Foundation/string.h>
#include <the_Foundation/vec2.h>
#include <SDL_render.h>

#include "fontpack.h"

/* Content sizes: regular (1x) -> medium (1.2x) -> big (1.33x) -> large (1.67x) -> huge (2x) */

#define FONT_ID(name, style, size)    ((name) + ((style) * max_FontSize) + (size))

enum iFontId {
    default_FontId         = 0,                    /* default is always the first font */
    monospace_FontId       = maxVariants_Fonts,     /* 2nd font is always the monospace font */
    documentBody_FontId    = maxVariants_Fonts * 2, /* 3rd font is the body font */
    documentHeading_FontId = maxVariants_Fonts * 3, /* heading font */
    auxiliary_FontId       = maxVariants_Fonts * 4, /* the first auxiliary font (e.g., symbols) */

    //    defaultMedium_FontId,
//    defaultBig_FontId,
//    defaultLarge_FontId,
//    defaultTiny_FontId,
//    defaultSmall_FontId,
    /* UI fonts: bold weight */
//    defaultBold_FontId,
//    defaultMediumBold_FontId,
//    defaultBigBold_FontId,
//    defaultLargeBold_FontId,
    /* content fonts */
//    bold_FontId,
//    italic_FontId,
//    medium_FontId,
//    big_FontId,
//    largeBold_FontId,
//    largeLight_FontId,
//    hugeBold_FontId,
//    monospaceSmall_FontId,
    /* extra content fonts */
//    defaultContentRegular_FontId, /* UI font but sized to regular_FontId */
//    defaultContentSmall_FontId, /* UI font but sized smaller */
    /* symbols and scripts */
//    userSymbols_FontId,
//    iosevka_FontId           = userSymbols_FontId + max_FontSize,
//    symbols_FontId           = iosevka_FontId + max_FontSize,
//    symbols2_FontId          = symbols_FontId + max_FontSize,
//    smolEmoji_FontId         = symbols2_FontId + max_FontSize,
//    notoEmoji_FontId         = smolEmoji_FontId + max_FontSize,
//    japanese_FontId          = notoEmoji_FontId + max_FontSize,
//    chineseSimplified_FontId = japanese_FontId + max_FontSize,
//    korean_FontId            = chineseSimplified_FontId + max_FontSize,
//    arabic_FontId            = korean_FontId + max_FontSize,
//    max_FontId               = arabic_FontId + max_FontSize,

    /* Meta: */
    mask_FontId               = 0x0000ffff, /* font IDs are 16-bit; see GmRun's packing */
    alwaysVariableFlag_FontId = 0x00010000,

    /* UI fonts: */
    uiLabelTiny_FontId       = FONT_ID(default_FontId, semiBold_FontStyle, uiTiny_FontSize),
    uiLabelSmall_FontId      = FONT_ID(default_FontId, regular_FontStyle,  uiSmall_FontSize),
    uiLabel_FontId           = FONT_ID(default_FontId, regular_FontStyle,  uiNormal_FontSize),
    uiLabelMedium_FontId     = FONT_ID(default_FontId, regular_FontStyle,  uiMedium_FontSize),
    uiLabelMediumBold_FontId = FONT_ID(default_FontId, bold_FontStyle,     uiMedium_FontSize),
    uiLabelBig_FontId        = FONT_ID(default_FontId, regular_FontStyle,  uiBig_FontSize),
    uiLabelBold_FontId       = FONT_ID(default_FontId, bold_FontStyle,     uiNormal_FontSize),
    uiLabelBigBold_FontId    = FONT_ID(default_FontId, bold_FontStyle,     uiBig_FontSize),
    uiLabelLarge_FontId      = FONT_ID(default_FontId, regular_FontStyle,  uiLarge_FontSize),
    uiLabelLargeBold_FontId  = FONT_ID(default_FontId, bold_FontStyle,     uiLarge_FontSize),
    uiLabelSymbols_FontId    = FONT_ID(auxiliary_FontId, regular_FontStyle, uiNormal_FontSize),
    uiShortcuts_FontId       = FONT_ID(default_FontId, regular_FontStyle,  uiNormal_FontSize),
    uiInput_FontId           = FONT_ID(default_FontId, regular_FontStyle,  uiMedium_FontSize),
    uiContent_FontId         = FONT_ID(default_FontId, regular_FontStyle,  uiMedium_FontSize),
    uiContentBold_FontId     = FONT_ID(default_FontId, bold_FontStyle,     uiMedium_FontSize),
    uiContentSymbols_FontId  = FONT_ID(auxiliary_FontId, regular_FontStyle, uiMedium_FontSize),
    /* Document fonts: */
    paragraph_FontId         = FONT_ID(documentBody_FontId,    regular_FontStyle, contentRegular_FontSize),
    bold_FontId              = FONT_ID(documentBody_FontId,    semiBold_FontStyle, contentRegular_FontSize),
    firstParagraph_FontId    = FONT_ID(documentBody_FontId,    regular_FontStyle, contentMedium_FontSize),
    preformatted_FontId      = FONT_ID(monospace_FontId,       regular_FontStyle, contentMono_FontSize),
    preformattedSmall_FontId = FONT_ID(monospace_FontId,       regular_FontStyle, contentMonoSmall_FontSize),
    quote_FontId             = FONT_ID(documentBody_FontId,    italic_FontStyle,  contentRegular_FontSize),
    heading1_FontId          = FONT_ID(documentHeading_FontId, bold_FontStyle,    contentHuge_FontSize),
    heading2_FontId          = FONT_ID(documentHeading_FontId, bold_FontStyle,    contentLarge_FontSize),
    heading3_FontId          = FONT_ID(documentHeading_FontId, regular_FontStyle, contentBig_FontSize),
    banner_FontId            = FONT_ID(documentHeading_FontId, light_FontStyle,   contentLarge_FontSize),
    regularMonospace_FontId  = FONT_ID(monospace_FontId,       regular_FontStyle, contentRegular_FontSize),
};

//iLocalDef iBool isJapanese_FontId(enum iFontId id) {
//    return id >= japanese_FontId && id < japanese_FontId + max_FontSize;
//}

#define emojiVariationSelector_Char     ((iChar) 0xfe0f)

/* TODO: get rid of this; configure using font ID strings, check RTL from FontFile flags */
enum iTextFont {
    undefined_TextFont = -1,
    nunito_TextFont = 0,
    firaSans_TextFont,
    literata_TextFont,
    tinos_TextFont,
    sourceSans3_TextFont,
    iosevka_TextFont,
    /* families: */
    arabic_TextFont,
    emojiAndSymbols_TextFont,
};

extern int gap_Text; /* affected by content font size */

iDeclareType(Text)
iDeclareTypeConstructionArgs(Text, SDL_Renderer *)

void    init_Text               (iText *, SDL_Renderer *);
void    deinit_Text             (iText *);

void    setCurrent_Text         (iText *);

//void    loadUserFonts_Text      (void); /* based on Prefs */

void    setContentFont_Text     (iText *, enum iTextFont font);
void    setHeadingFont_Text     (iText *, enum iTextFont font);
void    setContentFontSize_Text (iText *, float fontSizeFactor); /* affects all except `default*` fonts */
void    resetFonts_Text         (iText *);

int     lineHeight_Text         (int fontId);
iRect   visualBounds_Text       (int fontId, iRangecc text);

iDeclareType(TextMetrics)

struct Impl_TextMetrics {
    iRect bounds;  /* logical bounds: multiples of line height, horiz. advance */
    iInt2 advance; /* cursor offset */
};

iLocalDef int maxWidth_TextMetrics(const iTextMetrics d) {
    return iMax(width_Rect(d.bounds), d.advance.x);
}

iTextMetrics    measureRange_Text       (int fontId, iRangecc text);
iTextMetrics    measureWrapRange_Text   (int fontId, int maxWidth, iRangecc text);
iTextMetrics    measureN_Text           (int fontId, const char *text, size_t n); /* `n` in characters */

iLocalDef iTextMetrics measure_Text(int fontId, const char *text) {
    return measureRange_Text(fontId, range_CStr(text));
}

iInt2   tryAdvance_Text         (int fontId, iRangecc text, int width, const char **endPos);
iInt2   tryAdvanceNoWrap_Text   (int fontId, iRangecc text, int width, const char **endPos);

enum iAlignment {
    left_Alignment,
    center_Alignment,
    right_Alignment,
};

void    setOpacity_Text     (float opacity);

void    cache_Text          (int fontId, iRangecc text); /* pre-render glyphs */

void    draw_Text               (int fontId, iInt2 pos, int color, const char *text, ...);
void    drawAlign_Text          (int fontId, iInt2 pos, int color, enum iAlignment align, const char *text, ...);
void    drawCentered_Text       (int fontId, iRect rect, iBool alignVisual, int color, const char *text, ...);
void    drawCenteredRange_Text  (int fontId, iRect rect, iBool alignVisual, int color, iRangecc text);
void    drawCenteredOutline_Text(int fontId, iRect rect, iBool alignVisual, int outlineColor,
                                 int fillColor, const char *text, ...);
void    drawString_Text         (int fontId, iInt2 pos, int color, const iString *text);
void    drawRange_Text          (int fontId, iInt2 pos, int color, iRangecc text);
void    drawRangeN_Text         (int fontId, iInt2 pos, int color, iRangecc text, size_t maxLen);
void    drawOutline_Text        (int fontId, iInt2 pos, int outlineColor, int fillColor, iRangecc text);
void    drawBoundRange_Text     (int fontId, iInt2 pos, int boundWidth, int color, iRangecc text); /* bound does not wrap */
int     drawWrapRange_Text      (int fontId, iInt2 pos, int maxWidth, int color, iRangecc text); /* returns new Y */

iDeclareType(WrapText)

enum iWrapTextMode {
    anyCharacter_WrapTextMode,
    word_WrapTextMode,
};

struct Impl_WrapText {
    /* arguments */
    iRangecc    text;
    int         maxWidth;
    enum iWrapTextMode mode;
    iBool     (*wrapFunc)(iWrapText *, iRangecc wrappedText, int origin, int advance, iBool isBaseRTL);
    void *      context;
    iChar       overrideChar; /* use this for all characters instead of the real ones */
    int         baseDir; /* set to +1 for LTR, -1 for RTL */
    iInt2       hitPoint; /* sets hitChar_out */
    const char *hitChar; /* sets hitAdvance_out */
    /* output */
    const char *hitChar_out;
    iInt2       hitAdvance_out;
    float       hitGlyphNormX_out; /* normalized X inside the glyph */
    /* internal */
    iRangecc    wrapRange_;
};

iTextMetrics    measure_WrapText    (iWrapText *, int fontId);
iTextMetrics    draw_WrapText       (iWrapText *, int fontId, iInt2 pos, int color);

SDL_Texture *   glyphCache_Text     (void);

enum iTextBlockMode { quadrants_TextBlockMode, shading_TextBlockMode };

iString *   renderBlockChars_Text   (const iBlock *fontData, int height, enum iTextBlockMode,
                                     const iString *text);

/*-----------------------------------------------------------------------------------------------*/

iDeclareType(TextBuf)
iDeclareTypeConstructionArgs(TextBuf, iWrapText *wrap, int fontId, int color)
    
struct Impl_TextBuf {
    SDL_Texture *texture;
    iInt2        size;
};

iTextBuf *  newRange_TextBuf (int font, int color, iRangecc text);

void        draw_TextBuf    (const iTextBuf *, iInt2 pos, int color);
