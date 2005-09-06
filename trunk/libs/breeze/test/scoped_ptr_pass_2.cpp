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
//  Verify functioning of scoped_ptr with a custom deleter.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/scoped_ptr.hpp>
#include <breeze/debug/track_instances.hpp>

#include <boost/scoped_ptr.hpp>

struct noop_deleter
{
    template <class T>
    void operator()(T const &)
    {
    }
};

int main()
{
    typedef breeze::debug::track_instances<> test_type;
    typedef breeze::scoped_ptr<test_type, breeze::default_, breeze::default_,
        noop_deleter> noop_scoped_ptr;
    typedef boost::scoped_ptr<test_type> scoped_ptr;

    {
        noop_scoped_ptr nosp(new test_type());
        scoped_ptr sp(nosp.get());
    }
}
