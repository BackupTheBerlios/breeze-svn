//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: run-fail
//
//  breeze::debug::limit_instances<Max> asserts when the number of instances
//  exceeds Max.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/debug/limit_instances.hpp>
#include <breeze/debug/unused_variable.hpp>

int main()
{
    typedef breeze::debug::limit_instances<10> test_type;
    test_type t[11];

    breeze::debug::unused_variable(t);
}
