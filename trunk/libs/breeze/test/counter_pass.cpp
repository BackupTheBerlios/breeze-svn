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
//  Tests basic operations of breeze::debug::counter and verifies correctness of
//  its count.
//  Tests increment up to largest boost::int32_t.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/debug/counter.hpp>

#include <boost/cstdint.hpp>
#include <boost/integer_traits.hpp>

#include <cstddef>
#include <cassert>

int main()
{
    breeze::debug::counter<> counter1, counter2;
    assert(0 == counter1);
    assert(0 == counter2);

    counter1.increment();
    assert(1 == counter1);
    assert(0 == counter2);

    for (std::size_t i = 0; i < 100; ++i)
        counter2.increment();
    assert(1 == counter1);
    assert(100 == counter2);

    for (std::size_t i = 0; i < 50; ++i)
        counter2.decrement();
    assert(1 == counter1);
    assert(50 == counter2);

    counter1.decrement();
    assert(0 == counter1);
    assert(50 == counter2);

    breeze::debug::counter<> counter3;
    assert(0 == counter3);

    for (std::size_t i = 0; i < boost::integer_traits<boost::int32_t>::const_max; ++i)
        counter3.increment();

    assert(0 == counter1);
    assert(50 == counter2);
    assert(boost::integer_traits<boost::int32_t>::const_max == counter3);
}
