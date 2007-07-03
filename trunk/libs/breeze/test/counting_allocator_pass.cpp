//
//  Copyright (c) 2007 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: run-pass
//
//  Description goes here...
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/counting_allocator.hpp>
#include <breeze/debug/track_instances.hpp>

#include <cassert>

int main()
{
    typedef breeze::debug::track_instances<> element;
    typedef breeze::allocator::counting_allocator<element> allocator;
    typedef allocator::pointer pointer;

    allocator a;
    assert(0 == a.count());

    pointer p = a.allocate(10, 0);
    assert(0 == a.count());

    for (std::size_t i = 0; i < 10; ++i)
    {
        BOOST_ASSERT(a.count() == i);
        a.construct(p + i, element());
    }
    BOOST_ASSERT(10 == a.count());

    for (std::size_t i = 10; i > 0; --i)
    {
        BOOST_ASSERT(a.count() == i);
        a.destroy(p + i - 1);
    }
    BOOST_ASSERT(0 == a.count());

    a.deallocate(p, 10);
}

