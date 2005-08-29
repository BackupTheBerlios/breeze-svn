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
//  breeze::empty_storage asserts if the store is not empty when it is
//  destroyed, which is and indication that there might be leaked objects.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/empty_storage.hpp>
#include <breeze/debug/unused_variable.hpp>

int main()
{
    typedef breeze::empty_storage<int> test_type;
    test_type * tt = new test_type(1143);

    breeze::debug::unused_variable(tt);
}
