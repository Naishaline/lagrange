# Lagrange

Lagrange is a desktop GUI client for browsing Geminispace. It offers modern conveniences familiar from web browsers, such as smooth scrolling, inline image viewing, multiple tabs, visual themes, Unicode fonts, bookmarks, history, and page outlines.

Like Gemini, Lagrange has been designed with minimalism in mind. It depends on a small number of essential libraries. It is written in C and uses [SDL](https://libsdl.org/) for hardware-accelerated graphics. [OpenSSL](https://openssl.org/) is used for secure communications.

![Lagrange window open on URL "about:lagrange"](lagrange_about.png)

## Features

* Beautiful typography using Unicode fonts
* Autogenerated page style and Unicode icon for each Gemini domain
* Smart suggestions when typing the URL — search bookmarks, history, identities
* Sidebar for page outline, managing bookmarks and identities, and viewing history
* Multiple tabs
* Identity management — create and use TLS client certificates
* And more! Open `about:help` in the app, or see [help.gmi](https://git.skyjake.fi/skyjake/lagrange/raw/branch/release/res/about/help.gmi)

## Downloads

Prebuilt binaries for Windows and macOS can be found in [Releases][rel].

## How to compile

This is how to build Lagrange in a Unix-like environment. The required tools are a C11 compiler (e.g., Clang or GCC), CMake and `pkg-config`.

1. Download and extract a source tarball from [Releases][rel]. Alternatively, you may also clone the repository and its submodules: `git clone --recursive --branch release https://git.skyjake.fi/skyjake/lagrange`
2. Check that you have the dependencies installed: CMake, SDL 2, OpenSSL 1.1.1, libpcre, zlib, libunistring. For example, on macOS this would do the trick (using Homebrew): ```brew install cmake sdl2 openssl@1.1 pcre libunistring``` Or on Ubuntu: ```sudo apt install cmake libsdl2-dev libssl-dev libpcre3-dev zlib1g-dev libunistring-dev```
3. Create a build directory.
4. In your empty build directory, run CMake: ```cmake {path_of_lagrange_sources} -DCMAKE_BUILD_TYPE=Release```
5. Build it: ```cmake --build .```
6. Now you can run `lagrange`, `lagrange.exe`, or `Lagrange.app`.

### Installing to a directory

To install to "/dest/path":

1. `cmake {path_of_lagrange_sources} -DCMAKE_INSTALL_PREFIX=/dest/path`
2. `cmake --build . --target install`

This will also install an XDG .desktop file for launching the app.

### macOS-specific notes

When using OpenSSL 1.1.1 from Homebrew, you must add its pkgconfig path to your `PKG_CONFIG_PATH` environment variable, for example:

    export PKG_CONFIG_PATH=/usr/local/Cellar/openssl@1.1/1.1.1g/lib/pkgconfig

Also, SDL's trackpad scrolling behavior on macOS is not optimal for regular GUI apps because it emulates a physical mouse wheel. This may change in a future release of SDL, but at least in 2.0.12 a [small patch](https://git.skyjake.fi/skyjake/lagrange/raw/branch/dev/sdl2-macos-mouse-scrolling-patch.diff) is required to allow momentum scrolling to come through as single-pixel mouse wheel events.

[rel]: https://git.skyjake.fi/skyjake/lagrange/releases
[tf]:  https://git.skyjake.fi/skyjake/the_Foundation
