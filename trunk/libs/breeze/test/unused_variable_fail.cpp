//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Test-type: compile-fail
//  Requirements: <warnings>all <warnings-as-errors>on
//
//  Tests whether compiler generates warnings for unused variables.
//
//  Note: Only when this test passes (and thus warnings are emitted by the
//  compiler) will the unused_variable_pass test be meaningful.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/debug/unused_variable.hpp>

int main()
{
    int unused;
}
