//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: run
//
//  Exemplify usage of shared_proxy with boost::intrusive_ptr.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/shared_proxy.hpp>
#include <breeze/debug/track_instances.hpp>

#include <boost/intrusive_ptr.hpp>

#include <cassert>

struct A
    : breeze::debug::track_instances<A>
{
    void function() {}
};

int main()
{
    boost::intrusive_ptr<breeze::shared_proxy<A> >
        ptr1(new breeze::shared_proxy<A>()),
        ptr2,
        ptr3,
        ptr4;
    assert(1 == ptr1->use_count());
    assert(ptr1->unique());

    ptr2 = new breeze::shared_proxy<A>();
    assert(1 == ptr2->use_count());
    assert(ptr2->unique());
    ptr2 = ptr2;
    assert(1 == ptr2->use_count());
    assert(ptr2->unique());

    ptr2 = boost::intrusive_ptr<breeze::shared_proxy<A> >(ptr1);
    ptr3 = ptr1;
    ptr4 = ptr1;

    assert(ptr1.get() == ptr2.get());
    assert(ptr1.get() == ptr3.get());
    assert(ptr1.get() == ptr4.get());
    assert(4 == ptr1->use_count());

    (**ptr1).function();
    (*ptr1).get().function();
    (*ptr1)->function();
    (**ptr1.get()).function();
    (*ptr1.get())->function();
    (*ptr1.get()).get().function();
}
