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
//  Verify breeze::is_default and breeze::filter_default.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/default.hpp>
#include <breeze/static_assert.hpp>

#include <boost/type_traits/is_same.hpp>

namespace {

    struct something_else;

}

int main()
{
    BREEZE_STATIC_ASSERT(breeze::is_default<breeze::default_>::value,
        fundamental_error, default_not_recognized_as_default);
    BREEZE_STATIC_ASSERT(!breeze::is_default<something_else>::value,
        fundamental_error, non_default_recognized_as_default);

    BREEZE_STATIC_ASSERT((boost::is_same<breeze::filter_default<
        breeze::default_, double >::type, double>::value), fundamental_error,
        filter_default_not_working);
    BREEZE_STATIC_ASSERT((boost::is_same<breeze::filter_default<int, double
        >::type, int>::value), fundamental_error, filter_default_not_working);
}
