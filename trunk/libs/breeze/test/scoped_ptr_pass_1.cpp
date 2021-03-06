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
//  Verify basic functionality of and proper cleanup of resources by scoped_ptr.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/scoped_ptr.hpp>
#include <breeze/debug/track_instances.hpp>
#include <breeze/debug/unused_variable.hpp>

#include <iterator>
#include <algorithm>

#include "iterator_traits_test.hpp"

struct test_exception {};

// Intel compiler has trouble with function scope using declarations, so we put
// this here.
using std::swap;

int main()
{
    typedef breeze::debug::track_instances<> test_type;
    typedef breeze::scoped_ptr<test_type> pointer;
    typedef test_type * raw_pointer;

    breeze::test::std_iterator_traits<pointer>();

    {
        pointer p1(new test_type()), p2;
    }

    try
    {
        pointer p(new test_type());
        throw test_exception();
    }
    catch (test_exception &)
    {
    }

    {
        pointer p(new test_type());
        delete p.release();
    }

    {
        pointer p(new test_type());
        raw_pointer rp = p.get();

        pointer::reference ref = *p;

        breeze::debug::unused_variable(rp);
        breeze::debug::unused_variable(ref);
    }

    {
        pointer p(new test_type());
        p.reset();
    }

    {
        pointer p1(new test_type()), p2;
        p1->verify();
        swap(p1, p2);
    }
}
