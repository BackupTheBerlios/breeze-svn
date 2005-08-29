//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: compile-pass
//
//  Verify breeze::is_default.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/static_assert.hpp>
#include <breeze/default.hpp>

void test()
{
    BREEZE_STATIC_ASSERT(breeze::is_default<breeze::default_>::value,
        fundamental_error, default_not_recognized_as_default);
    BREEZE_STATIC_ASSERT(!breeze::is_default<struct something_else>::value,
        fundamental_error, non_default_recognized_as_default);
}
