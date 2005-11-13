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
//  Test basic functionality of breeze::iterator::pull.
//
////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#   undef NDEBUG
#endif

#include <breeze/iterator/pull.hpp>

#include <algorithm>
#include <string>

#include <cassert>

#include "iterator_traits_test.hpp"

std::string const test_string = "This is a string of text.";

struct no_skip_tokenizer
{
    no_skip_tokenizer(char const * str = 0)
        : next_(str)
    {
    }

    std::pair<char const *, char const *> operator()()
    {
        char const * first = next_, * last = 0;

        if (next_)
        {
            ++next_;

            while (' ' != *next_ && '\0' != *next_)
            {
                ++next_;
            }

            last = next_;

            if ('\0' == *next_)
            {
                next_ = 0;
            }
        }

        return std::pair<char const *, char const *>(first, last);
    }

private:
    char const * next_;
};

int main()
{
    typedef breeze::iterator::pull<char const *, no_skip_tokenizer> test_type;

    breeze::test::std_iterator_traits<test_type>();

    test_type piecewise_test_string(test_string.c_str());

    {
        char const * begin = test_string.c_str();
        while ('\0' != *begin)
        {
            assert(*begin == *piecewise_test_string);

            ++begin;
            ++piecewise_test_string;
        }
    }

    piecewise_test_string = test_type(test_string.c_str());

    assert(std::equal(test_string.begin(), test_string.end(),
        piecewise_test_string));
}
