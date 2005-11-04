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
//  Requirements: <warnings>on <warnings-as-errors>on
//
//  Make sure no warnings are generated when breeze::debug::always or
//  breeze::debug::never are used in control statements. Make sure
//  breeze::debug::always doesn't produce assertion failures.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/debug/always.hpp>
#include <breeze/debug/never.hpp>

#include <cassert>

int main()
{
    while(breeze::debug::never)
    {
        assert(breeze::debug::never && "Test failed.");
    }

    try
    {
        while(breeze::debug::always)
        {
            throw "Test";
        }

        assert(breeze::debug::never && "Test failed.");
    }
    catch(...)
    {
        assert(breeze::debug::always && "Test failed.");
    }
}
