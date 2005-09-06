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
//  Verify before_constructor is actually called before the constructor.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/debug/instrumented.hpp>

#include <cassert>

struct instrumented_constructor
    : breeze::debug::instrumented<instrumented_constructor>
{
    instrumented_constructor()
        : value()
    {
    }

    int value;

protected:
    friend class breeze::debug::instrumented<instrumented_constructor>;

    void before_constructor()
    {
        //  NOTE: Because this is called before the constructor, initialization
        //  done in the constructors overrides any values explicitly set here.
        value = 32;
    }
};

int main()
{
    instrumented_constructor ictor;
    assert(ictor.value == 0);
}

