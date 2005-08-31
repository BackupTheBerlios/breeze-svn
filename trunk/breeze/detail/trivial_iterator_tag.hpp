//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DETAIL_TRIVIAL_ITERATOR_TAG_HPP_INCLUDED)
#define BREEZE_DETAIL_TRIVIAL_ITERATOR_TAG_HPP_INCLUDED

#include <iterator>

namespace breeze { namespace detail {

    struct trivial_iterator_tag
    {
        trivial_iterator_tag(std::input_iterator_tag const &)
        {
        }

        trivial_iterator_tag(std::output_iterator_tag const &)
        {
        }
    };

}} // namespace breeze::detail

#endif // include guard
