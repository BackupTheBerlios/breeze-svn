//
//  Copyright (c) 2004, 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: run-pass
//
////////////////////////////////////////////////////////////////////////////////

#include "safe_bool_tests.hpp"

using namespace breeze::test;

int main()
{
    test_bool_testable<safe_bool>();
    test_bool_testable<safe_bool_with_compare>();
    test_bool_testable<safe_bool_with_compare_equal>();
    test_bool_testable<safe_bool_with_compare_not_equal>();

    test_comparable<
        safe_bool_with_compare,
        safe_bool_with_compare>();
}
