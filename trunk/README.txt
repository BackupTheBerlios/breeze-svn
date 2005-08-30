Breeze Code Library
===================

A library of small generic utility components written in standard C++. The
Breeze code library builds on top of (and depends on) the excellent Boost
libraries (see http://boost.org/). If you haven't already done so, you should
download and install Boost first.

As of this writing the library has been tested with Boost v1.32.0 and v1.33.0.

To use stuff in the library add the top-level directory to your compiler's
search path and include appropriate headers. Recommended form for includes is,
e.g.,

    #include <breeze/static_assert.hpp>

This is a header only library, no separate compilation step is required for the
library itself.


Compiling the test-suite
------------------------

A test-suite is included in the test/ directory and can be automatically built
using Boost Jam. Make sure the environment variable BOOST_BUILD_PATH is set and
points to BOOST_ROOT/tools/build/v2/, you may also need to write up a
user-config.jam or site-config.jam. Please refer to Boost.Build v2 documentation
for more information on that.

In the test directory run,

    bjam

