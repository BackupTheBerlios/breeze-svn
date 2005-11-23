//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_SCOPED_ARRAY_HPP_INCLUDED)
#define BREEZE_SCOPED_ARRAY_HPP_INCLUDED

#include <breeze/scoped_ptr.hpp>
#include <breeze/detail/trivial_iterator_tag.hpp>

#include <boost/iterator/iterator_traits.hpp>
#include <boost/checked_delete.hpp>

#include <iterator>

namespace breeze {

    template <
        class T,
        class Pointer = default_,
        class Reference = default_,
        class Deleter = default_
    >
    struct scoped_array
        : scoped_ptr<T, Pointer, Reference, typename filter_default<Deleter,
            boost::checked_array_deleter<T> >::type >
    {
    private:
        typedef scoped_ptr<T, Pointer, Reference, typename filter_default<
            Deleter, boost::checked_array_deleter<T> >::type > scoped_ptr_base_;

    public:
        typedef typename scoped_ptr_base_::pointer pointer;
        typedef typename scoped_ptr_base_::reference reference;
        typedef typename boost::iterator_difference<pointer>::type
            difference_type;
        typedef typename scoped_ptr_base_::deleter_type deleter_type;

    private:
        friend struct std::iterator_traits<scoped_array>;

        typedef T value_type;
        typedef detail::trivial_iterator_tag iterator_category;

    public:
        explicit scoped_array(
            pointer p = pointer(),
            deleter_type const & d = deleter_type()
        )
            : scoped_ptr_base_(p, d)
        {
        }

        reference operator[](difference_type i) const
        {
            return this->get()[i];
        }
    };

    ////////////////////////////////////////////////////////////////////////////
    template <class T, class P, class R, class D>
    void swap(scoped_array<T, P, R, D> & a, scoped_array<T, P, R, D> & b)
    {
        a.swap(b);
    }

} // namespace breeze

namespace boost {

    template <class T, class P, class R, class D>
    struct indirect_reference<breeze::scoped_array<T, P, R, D> >
    {
        typedef typename breeze::scoped_array<T, P, R, D>::reference reference;
    };

} // namespace boost

#endif // include guard
