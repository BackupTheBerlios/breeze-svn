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
//  Verify basic functionality of and proper cleanup of resources by
//  scoped_array.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/scoped_array.hpp>

#include <breeze/debug/track_instances.hpp>

#include "iterator_traits_test.hpp"

struct test_exception {};

// Intel compiler has trouble with function scope using declarations, so we put
// this here.
using std::swap;

int main()
{
    typedef breeze::debug::track_instances<> test_type;
    typedef breeze::scoped_array<test_type> pointer;

    breeze::test::std_iterator_traits<pointer>();

    {
        pointer p1(new test_type[1]), p2;
    }

    try
    {
        pointer p(new test_type[2]);
        throw test_exception();
    }
    catch (test_exception &)
    {
    }

    {
        pointer p(new test_type[3]);
        delete [] p.release();
    }

    {
        pointer p(new test_type[4]);
        p.reset(new test_type[5]);
        p.reset();
    }

    {
        pointer p1(new test_type[6]), p2;

        for (std::size_t i = 0; i < 6; ++i)
            p1[i].verify();

        swap(p1, p2);

        for (std::size_t i = 0; i < 6; ++i)
            p2[i].verify();
    }
}
