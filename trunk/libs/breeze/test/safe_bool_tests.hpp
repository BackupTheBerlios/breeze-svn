//
//  Copyright (c) 2004, 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_TEST_SAFE_BOOL_TESTS_HPP_INCLUDED)
#define BREEZE_TEST_SAFE_BOOL_TESTS_HPP_INCLUDED

#include <breeze/base/safe_bool.hpp>

#include <cassert>

namespace breeze { namespace test {

    struct safe_bool
        : breeze::base::safe_bool<safe_bool>
    {
        bool operator_safe_bool() const
        {
            return value;
        }

        bool value;
    };

    struct safe_bool_with_compare
        : breeze::base::safe_bool<safe_bool_with_compare>
    {
        bool operator_safe_bool() const
        {
            return value;
        }

        bool value;
    };

    inline bool operator==(safe_bool_with_compare const & lhs,
        safe_bool_with_compare const & rhs)
    {
        return (lhs.value == rhs.value);
    }

    inline bool operator!=(safe_bool_with_compare const & lhs,
        safe_bool_with_compare const & rhs)
    {
        return !(lhs == rhs);
    }

    struct safe_bool_with_compare_equal
        : breeze::base::safe_bool<safe_bool_with_compare_equal>
    {
        bool operator_safe_bool() const
        {
            return value;
        }

        bool value;
    };

    inline bool operator==(safe_bool_with_compare_equal const & lhs,
        safe_bool_with_compare_equal const & rhs)
    {
        return (lhs.value == rhs.value);
    }

    struct safe_bool_with_compare_not_equal
        : breeze::base::safe_bool<safe_bool_with_compare_not_equal>
    {
        bool operator_safe_bool() const
        {
            return value;
        }

        bool value;
    };

    inline bool operator!=(safe_bool_with_compare_not_equal const & lhs,
        safe_bool_with_compare_not_equal const & rhs)
    {
        return (lhs.value == rhs.value);
    }

    template <class T>
    static void test_bool_testable()
    {
        T t1, t2;
        t1.value = true;
        t2.value = false;

        assert((bool)t1);
        assert((bool)!t2);
    }

    template <class T1, class T2>
    static void test_comparable()
    {
        T1 t1;
        T2 t2;

        t1.value = true;
        t2.value = false;

        assert(t1 != t2);

        t2.value = true;

        assert(t1 == t2);
    }

    template <class T>
    static void test_assign_int()
    {
        T t;
        int i;

        i = t;
    }

    template <class T>
    static void test_less_than_operator()
    {
        T t1, t2;

        t1 < t2;
    }

    template <class T>
    static void test_left_shift_operator()
    {
        T t;

        t << 1;
    }

    template <class T>
    static void test_delete()
    {
        T t;

        delete t;
    }

}} // namespace breeze::test

#endif // include guard
