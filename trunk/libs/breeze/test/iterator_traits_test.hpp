//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_TEST_ITERATOR_TRAITS_TEST_HPP_INCLUDED)
#define BREEZE_TEST_ITERATOR_TRAITS_TEST_HPP_INCLUDED

#include <iterator>

namespace breeze { namespace test {

    template <class T>
    static inline void std_iterator_traits()
    {
        typedef typename std::iterator_traits<T>::value_type value_type;
        typedef typename std::iterator_traits<T>::difference_type
            difference_type;
        typedef typename std::iterator_traits<T>::pointer pointer;
        typedef typename std::iterator_traits<T>::reference reference;
        typedef typename std::iterator_traits<T>::iterator_category
            iterator_category;
    }

}} // namespace breeze::test

#endif // include guard
