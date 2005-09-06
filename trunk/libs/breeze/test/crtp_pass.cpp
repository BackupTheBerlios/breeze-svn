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
//  Test inheriting from breeze::base:crtp and actually using it.
//
//  FIXME: Output generated should be checked to ensure the correct function
//      overloads are being called.
//
////////////////////////////////////////////////////////////////////////////////

#include "crtp_tests.hpp"

using namespace breeze::test;

int main()
{
    base_class<> bc;
    base_class<> const bcc = base_class<>();

    good_derived_class gdc;
    good_derived_class const gdcc = good_derived_class();

    bc.call_function();
    bcc.call_function();

    gdc.call_function();
    gdcc.call_function();
}
