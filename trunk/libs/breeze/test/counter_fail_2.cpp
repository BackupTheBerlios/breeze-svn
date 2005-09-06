//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: run-fail
//
//  breeze::debug::counter asserts on overflow.
//
//  Note: This test may take a while to complete. The program enters an infinite
//  loop while incrementing the counter.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/debug/counter.hpp>

int main()
{
    breeze::debug::counter<> counter;
    while (true)
        counter.increment();
}
