//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: compile-fail
//
////////////////////////////////////////////////////////////////////////////////

#include "safe_bool_tests.hpp"

#include <breeze/bool_type.hpp>

int main()
{
    breeze::test::test_assign_to_int<breeze::bool_type>();
}
