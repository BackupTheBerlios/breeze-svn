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
//  breeze::base::crtp statically asserts when Derived template parameter does
//  not actually derive from it.
//
////////////////////////////////////////////////////////////////////////////////

#include "crtp_tests.hpp"

using namespace breeze::test;

int main()
{
    bad_derived_class bdc;
}
