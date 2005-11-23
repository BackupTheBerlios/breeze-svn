//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_DETAIL_SCOPED_PTR_HPP_INCLUDED)
#define BREEZE_DETAIL_SCOPED_PTR_HPP_INCLUDED

#include <breeze/void.hpp>
#include <breeze/default.hpp>
#include <breeze/detail/trivial_iterator_tag.hpp>

#include <boost/iterator/iterator_traits.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/indirect_reference.hpp>
#include <boost/checked_delete.hpp>
#include <boost/compressed_pair.hpp>
#include <boost/noncopyable.hpp>
#include <boost/assert.hpp>

#include <algorithm> // std::swap

namespace breeze {

    template <
        class T,
        class Pointer = default_,
        class Reference = default_,
        class Deleter = default_
    >
    struct scoped_ptr
        : boost::noncopyable
    {
        typedef T element_type;

        typedef typename filter_default<Pointer, typename boost::add_pointer<
            element_type>::type>::type pointer;
        typedef typename filter_default<Reference, typename
            boost::iterator_reference<pointer>::type>::type reference;
        typedef typename filter_default<Deleter, boost::checked_deleter<T>
            >::type deleter_type;

    private:
        friend struct std::iterator_traits<scoped_ptr>;

        typedef T value_type;
        typedef void_ difference_type;
        typedef detail::trivial_iterator_tag iterator_category;

        typedef boost::compressed_pair<pointer, deleter_type> data_type;

    public:

        explicit scoped_ptr(
            pointer p = pointer(),
            deleter_type const & d = deleter_type()
        )
            : data_(p, d)
        {
        }

        ~scoped_ptr()
        {
            this->clear();
        }

        void reset(pointer p = pointer())
        {
            this->clear();
            data_.first() = p;
        }

        reference operator*() const
        {
            BOOST_ASSERT(data_.first()
                && "Dereferencing singular pointer.");
            return *data_.first();
        }

        pointer operator->() const
        {
            BOOST_ASSERT(data_.first()
                && "Dereferencing singular pointer.");
            return data_.first();
        }

        pointer get() const
        {
            // May return singular value.
            return data_.first();
        }

        pointer release()
        {
            pointer ret = data_.first();
            data_.first() = pointer();
            return ret;
        }

        void swap(scoped_ptr & other)
        {
            using std::swap;
            swap(this->data_, other.data_);
        }

        typename data_type::second_reference get_deleter()
        {
            return data_.second();
        }

        typename data_type::second_const_reference get_deleter() const
        {
            return data_.second();
        }

    private:
        void clear()
        {
            if (data_.first())
            {
                data_.second()(data_.first());
            }
        }

        data_type data_;
    };

    template <class T, class P, class R, class D>
    void swap(scoped_ptr<T, P, R, D> & a, scoped_ptr<T, P, R, D> & b)
    {
        a.swap(b);
    }

} // namespace breeze

namespace boost {

    template <class T, class P, class R, class D>
    struct indirect_reference<breeze::scoped_ptr<T, P, R, D> >
    {
        typedef typename breeze::scoped_ptr<T, P, R, D>::reference reference;
    };

} // namespace boost

#endif // include guard
