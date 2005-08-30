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
//
//  Ensure unused_variable does not perform unnecessary copies.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/debug/unused_variable.hpp>

#include <boost/noncopyable.hpp>

struct non_copyable
    : boost::noncopyable
{
};

int main()
{
    non_copyable nc;
    non_copyable const ncc;

    //breeze::debug::unused_variable(non_copyable());
    breeze::debug::unused_variable(nc);
    breeze::debug::unused_variable(ncc);
}
