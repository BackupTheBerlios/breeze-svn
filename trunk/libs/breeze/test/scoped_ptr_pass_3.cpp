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
//  Use a custom deleter with breeze::scoped_ptr to handle deletion of a
//  specially crafted incomplete array.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/scoped_ptr.hpp>
#include <breeze/debug/track_instances.hpp>

#include <cstddef>
#include <memory>

struct test_exception {};

template <std::size_t N>
struct will_throw_on
    : breeze::debug::track_instances<will_throw_on<N> >
{
    will_throw_on()
    {
        static std::size_t count = 0;
        ++count;
        if (count == N)
            throw test_exception();
    }
};

struct incremental_array_deleter
{
    incremental_array_deleter()
        : live_count()
    {
    }

    template <class T>
    void operator()(T * p)
    {
        for (std::size_t i = live_count; i > 0;)
        {
            (p + --i)->~T();
        }

        delete [] reinterpret_cast<char *>(p);
    }

    std::size_t live_count;
};

int main()
{
    typedef will_throw_on<5> test_type;
    typedef breeze::scoped_ptr<test_type, breeze::default_, breeze::default_,
        incremental_array_deleter> pointer;
    typedef test_type * raw_pointer;

    try {
        pointer p(reinterpret_cast<test_type *>(
            new char[10*sizeof(test_type)]));

        for (std::size_t i = 0; i < 10; ++i)
        {
            new (p.get() + i) test_type();
            ++p.get_deleter().live_count;
        }
    } catch (test_exception &)
    {
    }
}
