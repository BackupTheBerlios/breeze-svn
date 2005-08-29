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
////////////////////////////////////////////////////////////////////////////////

#include <breeze/static_assert.hpp>

BREEZE_STATIC_ASSERT(true, static_assert_test,
    this_is_NOT_supposed_to_fail);
BREEZE_STATIC_ASSERT(true, static_assert_test,
    this_is_NOT_supposed_to_fail);

namespace /* unnamed */ {

    BREEZE_STATIC_ASSERT(true, static_assert_test,
        this_is_NOT_supposed_to_fail);
    BREEZE_STATIC_ASSERT(true, static_assert_test,
        this_is_NOT_supposed_to_fail);

}

namespace named {

    BREEZE_STATIC_ASSERT(true, static_assert_test,
        this_is_NOT_supposed_to_fail);
    BREEZE_STATIC_ASSERT(true, static_assert_test,
        this_is_NOT_supposed_to_fail);

}

struct static_assert_test
{
    BREEZE_STATIC_ASSERT(true, static_assert_test,
        this_is_NOT_supposed_to_fail);
    BREEZE_STATIC_ASSERT(true, static_assert_test,
        this_is_NOT_supposed_to_fail);
};

template <typename T>
struct static_assert_test2
{
    BREEZE_STATIC_ASSERT(sizeof(T) != 0, static_assert_test,
        this_is_NOT_supposed_to_fail);
    BREEZE_STATIC_ASSERT(true, static_assert_test,
        this_is_NOT_supposed_to_fail);
};

template struct static_assert_test2<static_assert_test>;

int main()
{
    BREEZE_STATIC_ASSERT(true, static_assert_test,
        this_is_NOT_supposed_to_fail);
    BREEZE_STATIC_ASSERT(true, static_assert_test,
        this_is_NOT_supposed_to_fail);
}
