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
//  breeze::debug::count_instances asserts if live_count overflows.
//
//  Note: This test may take a long time to run. It enters an infinite loop and
//  constructs count_instances until it breaks. All instances are created at the
//  same memory address so memory consumption should be low.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/debug/count_instances.hpp>

#include <boost/utility/addressof.hpp>

#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/aligned_storage.hpp>

#include <memory> // for placement new

int main()
{
    typedef breeze::debug::count_instances<> test_type;

    typedef boost::aligned_storage<sizeof(test_type),
        boost::alignment_of<test_type>::value> buffer_type;

    buffer_type buffer;

    test_type * const p = reinterpret_cast<test_type *>(boost::addressof(buffer));

    while (true)
    {
        new (p) test_type();
    }
}
