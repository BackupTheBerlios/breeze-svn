//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Test-type: compile
//  Requirements: <warnings>all <warnings-as-errors>on
//
//  Ensure warnings are not generated for wrapped unused variables.
//  Ensure unused_variable does not perform unnecessary copies.
//
//  Note: This test is meaningful only when unused_variable_fail fails, as
//  expected.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/debug/unused_variable.hpp>

#include <boost/noncopyable.hpp>

struct construct_type {};

const construct_type construct = construct_type();

struct non_copyable
    : boost::noncopyable
{
    non_copyable(construct_type const &) { }
};

int main()
{
    non_copyable nc(construct);
    non_copyable const ncc(construct);
    non_copyable volatile vcc(construct);
    non_copyable const volatile cvcc(construct);

    int unused;

    // This one tries to copy the argument
    // breeze::debug::unused_variable(non_copyable());

    breeze::debug::unused_variable(nc);
    breeze::debug::unused_variable(ncc);

    breeze::debug::unused_variable(unused);
}
