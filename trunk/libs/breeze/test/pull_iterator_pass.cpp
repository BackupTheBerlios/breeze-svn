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

static std::string const test_string = "This is a string of text.";
static char const * broken_string[] = { "This", " ", "is", " ", "a", " ",
    "string", " ", "of", " ", "text", ".", 0};

static std::size_t counter = 0;

struct no_skip_tokenizer
{
    no_skip_tokenizer(char const * str = 0)
        : next_(str)
    {
    }

    std::pair<char const *, char const *> operator()()
    {
        ++counter;

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

    char const * next_;
};

struct string_merger
{
    string_merger(char const ** strs)
        : strings_(strs)
    {
    }

    std::string operator()()
    {
        ++counter;
        if (strings_ && *strings_)
        {
            return std::string(*strings_++);
        }
        else
        {
            return std::string();
        }
    }

    char const ** strings_;
};

int main()
{
    typedef breeze::iterator::pull<char const *, no_skip_tokenizer> test_type1;
    typedef breeze::iterator::pull<std::string::const_iterator, string_merger>
        test_type2;
    typedef breeze::iterator::pull<std::string::const_iterator, string_merger &>
        test_type3;

    breeze::test::std_iterator_traits<test_type1>();

    test_type1 piecewise_test_string(test_string.c_str());

    {
        char const * begin = test_string.c_str();
        while ('\0' != *begin)
        {
            assert(*begin == *piecewise_test_string && "Test failed!");
            ++begin;
            ++piecewise_test_string;
        }
        assert(7 == counter && "Test failed!");
    }

    piecewise_test_string = test_type1(test_string.c_str());

    assert(std::equal(test_string.begin(), test_string.end(),
        piecewise_test_string) && "Test failed!");
    assert(14 == counter && "Test failed!");

    assert(std::equal(test_string.begin(), test_string.end(),
        test_type2(string_merger(broken_string))) && "Test failed!");
    assert(27 == counter && "Test failed!");

    assert(std::equal(test_string.begin(), test_string.end(),
        test_type2(string_merger(broken_string))) && "Test failed!");
    assert(40 == counter && "Test failed!");

    string_merger merge_broken_string(broken_string);
    assert(std::equal(test_string.begin(), test_string.end(),
        test_type3(merge_broken_string)) && "Test failed!");
    assert(53 == counter && "Test failed!");
    assert(std::string() == merge_broken_string() && "Test failed!");
    assert(&test_type3(merge_broken_string).source() == &merge_broken_string);
}
