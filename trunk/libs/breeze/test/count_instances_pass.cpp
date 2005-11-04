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
//  Directly verifies live_count maintained by breeze::debug::count_instances.
//  Checks for interference between different instantiations of count_instances.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/debug/count_instances.hpp>
#include <breeze/debug/unused_variable.hpp>

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <cassert>

struct counted_1
    : breeze::debug::count_instances<counted_1>
{
};

struct counted_2
    : breeze::debug::count_instances<counted_2>
{
};

template <class T>
static void test(long n)
{
    long const initial_count = T::live_count();

    T * a = new T();
    assert(T::live_count() == initial_count + 1);

    T b;
    assert(T::live_count() == initial_count + 2);

    delete a;
    assert(T::live_count() == initial_count + 1);

    a = new T[n];
    assert(T::live_count() == initial_count + 1 + n);

    delete [] a;
    assert(T::live_count() == initial_count + 1);
}

int main()
{
    typedef breeze::debug::count_instances<> test_type1;
    typedef counted_1 test_type2;
    typedef counted_2 test_type3;

    assert(test_type1::live_count() == 0);
    assert(test_type2::live_count() == 0);
    assert(test_type3::live_count() == 0);

    test_type1 tt[33];
    assert(test_type1::live_count() == 33);
    assert(test_type2::live_count() == 0);
    assert(test_type3::live_count() == 0);

    test<test_type1>(10);

    assert(test_type1::live_count() == 33);
    assert(test_type2::live_count() == 0);
    assert(test_type3::live_count() == 0);

    {
        test_type2 tt2_1, tt2_2;
        assert(test_type1::live_count() == 33);
        assert(test_type2::live_count() == 2);
        assert(test_type3::live_count() == 0);
    }
    assert(test_type1::live_count() == 33);
    assert(test_type2::live_count() == 0);
    assert(test_type3::live_count() == 0);

    breeze::debug::unused_variable(tt);
}
