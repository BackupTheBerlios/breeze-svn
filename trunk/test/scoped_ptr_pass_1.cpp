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
//  Verify proper cleanup of resources by scoped_ptr.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/scoped_ptr.hpp>
#include <breeze/debug/track_instances.hpp>
#include <breeze/debug/unused_variable.hpp>

#include <iterator>
#include <algorithm>

template <class T>
void test_std_iterator_traits()
{
    typedef typename std::iterator_traits<T>::value_type value_type;
    typedef typename std::iterator_traits<T>::difference_type difference_type;
    typedef typename std::iterator_traits<T>::pointer pointer;
    typedef typename std::iterator_traits<T>::reference reference;
    typedef typename std::iterator_traits<T>::iterator_category
        iterator_category;
}

struct test_exception {};

int main()
{
    typedef breeze::debug::track_instances<> test_type;
    typedef breeze::scoped_ptr<test_type> pointer;
    typedef test_type * raw_pointer;

    test_std_iterator_traits<pointer>();

    try {
        pointer p(new test_type());
        throw test_exception();
    } catch (test_exception &)
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
        using std::swap;

        pointer p1(new test_type()), p2;
        p1->verify();
        swap(p1, p2);
    }
}
