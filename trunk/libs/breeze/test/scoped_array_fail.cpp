//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: compile-fail
//
//  By default, breeze::scoped_array cannot be used with incomplete types.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/scoped_array.hpp>

struct incomplete_type;

int main()
{
    typedef breeze::scoped_array<incomplete_type> scoped_array;

    scoped_array p;
}
