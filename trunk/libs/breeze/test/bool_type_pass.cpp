//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: run
//
//  Make sure bool_type interface is usable.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include "safe_bool_tests.hpp"

#include <breeze/bool_type.hpp>

#include <algorithm> // std::swap

#include <cassert>

int main()
{
    breeze::bool_type bool1 = breeze::bool_type(true), bool2 = false;

    assert(bool1);
    assert(!bool2);

    {
        using std::swap;

        swap(bool1, bool2);
    }

    assert(!bool1);
    assert(bool2);

    assert(bool1 || bool2);
    assert(bool1 != bool2);

    bool1 = !bool1;
    bool2 = true;
    
    assert(bool1 && bool2);
    assert(bool1 == bool2);

    bool1 = 55;

    assert(bool1);

    bool1 = 0;

    assert(!bool1);
}
