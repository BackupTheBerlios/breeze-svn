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
//  Verify Max instances of breeze::debug::limit_instances<Max> can be
//  simultaneously alive.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/debug/limit_instances.hpp>
#include <breeze/debug/unused_variable.hpp>

int main()
{
    typedef breeze::debug::limit_instances<10> test_type;

    {
        test_type t0, t1, t2, t3, t4, t5, t6, t7, t8, t9;

        breeze::debug::unused_variable(t0);
        breeze::debug::unused_variable(t1);
        breeze::debug::unused_variable(t2);
        breeze::debug::unused_variable(t3);
        breeze::debug::unused_variable(t4);
        breeze::debug::unused_variable(t5);
        breeze::debug::unused_variable(t6);
        breeze::debug::unused_variable(t7);
        breeze::debug::unused_variable(t8);
        breeze::debug::unused_variable(t9);
    }

    {
        test_type t0;
        test_type t1;
        test_type t2;
        test_type t3;
        test_type t4;
        test_type t5;
        test_type t6;
        test_type t7;
        test_type t8;
        test_type t9;

        breeze::debug::unused_variable(t0);
        breeze::debug::unused_variable(t1);
        breeze::debug::unused_variable(t2);
        breeze::debug::unused_variable(t3);
        breeze::debug::unused_variable(t4);
        breeze::debug::unused_variable(t5);
        breeze::debug::unused_variable(t6);
        breeze::debug::unused_variable(t7);
        breeze::debug::unused_variable(t8);
        breeze::debug::unused_variable(t9);
    }

    {
        test_type t[10];

        breeze::debug::unused_variable(t);
    }

    {
        test_type t[8];
        test_type t8 = test_type();
        test_type t9;

        breeze::debug::unused_variable(t);
        breeze::debug::unused_variable(t8);
        breeze::debug::unused_variable(t9);
    }
}
