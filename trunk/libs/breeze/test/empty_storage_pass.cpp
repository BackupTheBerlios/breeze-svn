//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: run-pass
//
//  Verify that breeze::empty_storage is an empty class and is capable of
//  storing objects of different types. Verify lazy construction of stored
//  objects.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/empty_storage.hpp>

#include <boost/type_traits/is_empty.hpp>

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <cassert>

struct empty_1
    : breeze::empty_storage<int, empty_1>
{
};

struct empty_2
    : breeze::empty_storage<empty_1, empty_2>
{
};

int main()
{
    typedef breeze::empty_storage<int> test_type1;
    typedef empty_1 test_type2;
    typedef empty_2 test_type3;

    BREEZE_STATIC_ASSERT(boost::is_empty<test_type1>::value, empty_storage,
        not_empty);
    BREEZE_STATIC_ASSERT(boost::is_empty<test_type2>::value, empty_storage,
        not_empty);
    BREEZE_STATIC_ASSERT(boost::is_empty<test_type3>::value, empty_storage,
        not_empty);

    test_type1 tt1_0, tt1_1(55), tt1_2(tt1_0);
    test_type2 tt2_0, tt2_1(tt2_0);

    assert(!tt1_0.has_value());
    assert(!tt2_0.has_value());
    assert(!tt2_1.has_value());

    assert(tt1_0.get() == int());

    tt1_0.get() = 32;
    tt2_0.get() = 33;
    assert(tt1_0.get() == 32);
    assert(tt2_0.get() == 33);
    assert(tt2_1.get() == int());

    test_type3 tt3_0, tt3_1;

    assert(!tt3_0.has_value());
    assert(!tt3_1.has_value());

    tt3_0.get() = tt2_0;

    assert(tt3_0.has_value());

    tt3_0.reset();

    assert(!tt3_0.has_value());
}
