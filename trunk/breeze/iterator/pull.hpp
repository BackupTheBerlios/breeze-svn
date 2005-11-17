//
//  Copyright (c) 2005 João Abecasis
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(BREEZE_ITERATOR_PULL_HPP_INCLUDED)
#define BREEZE_ITERATOR_PULL_HPP_INCLUDED

#include <breeze/static_assert.hpp>

#include <boost/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <iterator>

namespace breeze { namespace iterator {

    namespace detail {

        template <class Iterator, class Range>
        inline void expand_range(Range const & range, Iterator & begin,
            Iterator & end)
        {
            begin = boost::begin(range);
            end = boost::end(range);
        }

    } // namespace detail

    //
    //  Requirements:
    //
    //      Iterator    - an Input Iterator
    //      Source      - defines an operator()() returning a range
    //
    template <class Iterator, class Source>
    struct pull
        : boost::iterator_adaptor<
            pull<Iterator, Source>,
            Iterator,
            boost::use_default,
            std::input_iterator_tag
        >
    {
        typedef Source source_type;
        typedef typename boost::add_reference<source_type>::type
            source_reference;
        typedef typename boost::add_reference<typename boost::add_const<
            source_type>::type>::type source_const_reference;

        pull()
        {
            this->fill_from_source();
        }

        pull(source_const_reference src)
            : source_(src)
        {
            this->fill_from_source();
        }

        source_reference source()
        {
            return this->source_;
        }

        source_const_reference source() const
        {
            return this->source_;
        }

    private:
        BREEZE_STATIC_ASSERT(
            (boost::is_convertible<
                typename boost::iterator_category<Iterator>::type,
                std::input_iterator_tag
            >::value),
            invalid_template_argument,
            breeze_pull_iterator_requires_InputIterator
        );

        friend class boost::iterator_core_access;

        typedef typename pull::iterator_adaptor_ iterator_adaptor_;

        void increment()
        {
            BOOST_ASSERT(this->base_reference() != this->last_
                && "Incrementing past end of range."
                && "Or incrementing on empty range.");

            ++this->base_reference();

            if (this->base_reference() == last_)
            {
                this->fill_from_source();
            }
        }

        void fill_from_source()
        {
            detail::expand_range(this->source_(), this->base_reference(),
                this->last_);
        }

        Iterator last_;
        source_type source_;
    };

}} // namespace breeze::iterator

#endif // include guard
