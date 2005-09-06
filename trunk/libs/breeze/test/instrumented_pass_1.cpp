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
//  Verify after_destructor and before constructor are being called.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/debug/instrumented.hpp>

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <cassert>

int static_variable = 0;

struct instrumented_constructor
    : breeze::debug::instrumented<instrumented_constructor>
{
protected:
    friend class breeze::debug::instrumented<instrumented_constructor>;

    void before_constructor()
    {
        static_variable += 20;
    }
};

struct instrumented_destructor
    : breeze::debug::instrumented<instrumented_destructor>
{
protected:
    friend class breeze::debug::instrumented<instrumented_destructor>;

    void after_destructor()
    {
        static_variable /= 4;
    }
};

struct instrumented_class
    : instrumented_constructor
    , instrumented_destructor
{
};

int main()
{
    assert(static_variable == 0);

    {
        instrumented_class ic1, ic2, ic3, ic4;
        assert(static_variable == 80);
    }

    assert(static_variable == 0);

    {
        instrumented_class ic1, ic2;
        assert(static_variable == 40);

        {
            instrumented_class ic;
            assert(static_variable == 60);
        }

        assert(static_variable == 15);
    }

    assert(static_variable == 0);

    {
        instrumented_constructor ictor1;
        assert(static_variable == 20);
    }

    assert(static_variable == 20);

    {
        instrumented_destructor idtor1;
        assert(static_variable == 20);
    }

    assert(static_variable == 5);
}
