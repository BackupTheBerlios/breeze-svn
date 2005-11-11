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
//  Requirements: <warnings>on <warnings-as-errors>on
//
//  Make sure no warnings are generated when breeze::debug::never is used in
//  control statements. Make sure breeze::debug::never produces assertion
//  failures.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/debug/never.hpp>

#include <cassert>

int main()
{
    assert(breeze::debug::never && "Test passed.");
}
