# NDS Toolkit Change Log

All changes to the NDS Toolkit will be logged in this change log with each
release.

## 0.1b1

This is my first officially versioned release. It is stable and works to an
extent; the only page that is known to be broken is the Code Porter. It's...
very buggy. Fixing this is top priority for the next release.

## 0.1b2

The second beta has arrived, now with a working Code Porter!

### Bug Fixes

 * Code Porter tab is now functioning as expected, with code type support.

### Known Issues

 * The Code Porter tab strips blank lines from the input when it shouldn't.

## 0.1b3

This is an emergency patch, to fix a bug that broke the Patch Code Builder. The
first line of its output was bogus; this has been fixed and the builder now
functions as it should.

## 0.1

First stable release.

### Bug Fixes from Beta

 * Fixed buggy behavior of Code Parser, the program is now fully working.

### Goals for Next Release

 * Revamp the Button Activator Generator.

## 0.5b1

A big step up from the previous release, a lot of new features are available
in this beta.

### Features

 * Button Activator Generator GUI completely revamped.
   * Added a Code Input to the Button Activator Generator.
 * Added a Code Beautifier page.
 * Pointer Searcher page has been improved.
   * You may now select results from the Search Results box to view the
     pointer code for that result.
   * The Hex Value input, when changed, will now update the Pointer Code
     output live.

### Improvements

 * Minor performance optimizations in the Code Porter.

### Bug Fixes

 * Fixed a crash in the Pointer Searcher that occurred when no search results
   were found; it now alerts you to the lack of results.

## 0.5

### Bug Fixes from Beta

 * Fixed build on Windows and on some build configurations.

### New Features Since Beta

 * The window will no longer allow you to shrink it to the point where widgets
   get trunctuated.
 * The Pointer Searcher will now clear the address box when you load in a new
   .bin file (unless the .bin file has an address at the end of its file name,
   e.g. My_Game_Name_2E71A216.bin, in which case it will still auto-fill the
   address box for you).

## 0.6

This version did not have a beta because it fixed a critical bug that I wanted
at release as quickly as possible.

### Bug Fixes

 * Select button on the Button Activator Generator now works.
 * "All Files" on the file selection box now allows you to actually view all
   files, not just ones with a dot somewhere in them (*.*).

### Tweaks

 * Tweaked padding on some UI elements that seemed too close together.
 * Code Beautifier now trims blank lines from the very top/bottom of the
   output, regardless of settings.

### Usability

 * Made some Pointer Searcher error messages more detailed.
 * Made the Makefile output a lot nicer and cleaned it up a bit.
 * Added more to the documentation.

### Development

 * Added a code testing system, and a couple test suites.
