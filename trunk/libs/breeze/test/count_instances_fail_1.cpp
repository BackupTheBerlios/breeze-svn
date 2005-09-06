//
//  Copyright (c) 2004, 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: run-fail
//
//  count_instances asserts if there are live objects when the counter's
//  destructor is called.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/debug/count_instances.hpp>
#include <breeze/debug/unused_variable.hpp>

int main()
{
    typedef breeze::debug::count_instances<> test_type;

    test_type * a = new test_type();

    breeze::debug::unused_variable(a);
}
