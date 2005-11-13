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

#include <boost/utility/base_from_member.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/assert.hpp>

#include <iterator>

namespace breeze { namespace iterator {

    template <class Iterator, class Source>
    struct pull
        : boost::base_from_member<Source>
        , boost::iterator_adaptor<
            pull<Iterator, Source>,
            Iterator,
            boost::use_default,
            std::input_iterator_tag
        >
    {
        pull()
        {
            this->fill_from_source();
        }

        pull(Source const & src)
            : source_base(src)
        {
            this->fill_from_source();
        }

        Source & source()
        {
            return this->member;
        }

        Source const & source() const
        {
            return this->member;
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
        typedef boost::base_from_member<Source> source_base;

        using source_base::member;

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
            boost::tie(this->base_reference(), this->last_) =
                this->member();
        }

        Iterator last_;
    };

}} // namespace breeze::iterator

#endif // include guard
