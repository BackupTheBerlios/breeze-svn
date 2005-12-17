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
//  Test shared_proxy interface
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/shared_proxy.hpp>
#include <breeze/debug/track_instances.hpp>
#include <breeze/debug/unused_variable.hpp>

#include <cassert>

struct A;
struct B;
struct C;

struct A
    : breeze::debug::track_instances<A>
{
    A() {}
    A(B const &) {}

    A & operator=(C const &) { return *this; }

    void function() {}
    void const_function () const {}
};

struct B {};
struct C {};

int main()
{
    {
        breeze::shared_proxy<A> * ptr_proxy = new breeze::shared_proxy<A>();
        ptr_proxy->increment_use_count();

        B B_;
        breeze::shared_proxy<A> proxy1(*ptr_proxy), proxy2(B_);
        breeze::shared_proxy<A> const cproxy(proxy1);

        (*proxy1).function();
        proxy1->function();
        proxy1.get().function();

        (*cproxy).const_function();
        cproxy->const_function();
        cproxy.get().const_function();

        proxy2 = C();

        assert(ptr_proxy->unique());
        assert(0 == proxy1.use_count());
        assert(0 == proxy2.use_count());

        ptr_proxy->decrement_use_count();
    }

    {
        breeze::shared_proxy<A> * ptr_proxy = new breeze::shared_proxy<A>();
        ptr_proxy->get_deleter()(ptr_proxy);
    }

    {
        breeze::shared_proxy<A> const * ptr_proxy = new breeze::shared_proxy<A>();
        ptr_proxy->get_deleter()(ptr_proxy);
    }
}
