#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd "/Users/shileimao/Documents/Programming Languages/C++/player/player/build"
  make -f /Users/shileimao/Documents/Programming\ Languages/C++/player/player/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd "/Users/shileimao/Documents/Programming Languages/C++/player/player/build"
  make -f /Users/shileimao/Documents/Programming\ Languages/C++/player/player/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd "/Users/shileimao/Documents/Programming Languages/C++/player/player/build"
  make -f /Users/shileimao/Documents/Programming\ Languages/C++/player/player/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd "/Users/shileimao/Documents/Programming Languages/C++/player/player/build"
  make -f /Users/shileimao/Documents/Programming\ Languages/C++/player/player/build/CMakeScripts/ReRunCMake.make
fi

