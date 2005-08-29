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

#include <breeze/static_assert.hpp>

BREEZE_STATIC_ASSERT(false, static_assert_test,
    this_test_is_supposed_to_fail);

int main()
{
    BREEZE_STATIC_ASSERT(false, static_assert_test,
        this_test_is_supposed_to_fail);
}
