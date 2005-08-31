//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

////////////////////////////////////////////////////////////////////////////////
//
//  Type: compile-pass
//
//  Standard iterators are also trivial iterators.
//
////////////////////////////////////////////////////////////////////////////////

#include <breeze/detail/trivial_iterator_tag.hpp>
#include <breeze/static_assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <iterator>

int main()
{
    BREEZE_STATIC_ASSERT((boost::is_convertible<std::input_iterator_tag,
        breeze::detail::trivial_iterator_tag>::value), fundamental_error,
        input_iterator_is_not_trivial_iterator);
    BREEZE_STATIC_ASSERT((boost::is_convertible<std::output_iterator_tag,
        breeze::detail::trivial_iterator_tag>::value), fundamental_error,
        output_iterator_is_not_trivial_iterator);
    BREEZE_STATIC_ASSERT((boost::is_convertible<std::forward_iterator_tag,
        breeze::detail::trivial_iterator_tag>::value), fundamental_error,
        forward_iterator_is_not_trivial_iterator);
    BREEZE_STATIC_ASSERT((boost::is_convertible<std::bidirectional_iterator_tag,
        breeze::detail::trivial_iterator_tag>::value), fundamental_error,
        bidirectional_iterator_is_not_trivial_iterator);
    BREEZE_STATIC_ASSERT((boost::is_convertible<std::random_access_iterator_tag,
        breeze::detail::trivial_iterator_tag>::value), fundamental_error,
        random_access_iterator_is_not_trivial_iterator);
}
