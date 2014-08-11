/* Boost.MultiIndex example of a bidirectional map.
 *
 * Copyright 2003-2005 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BDMAP_H_
#define BDMAP_H_

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <utility>

using boost::multi_index_container;
using namespace boost::multi_index;

struct first {
};

struct second {
};

template<typename FirstType, typename SecondType>
struct bdmap {
    typedef std::pair<FirstType, SecondType> value_type;

    typedef multi_index_container<
            value_type,
            indexed_by<
            ordered_unique<
            tag<first>, member<value_type, FirstType, &value_type::first> >,
            ordered_unique<
            tag<second>, member<value_type, SecondType, &value_type::second> >
            >
            > type;
};


#endif /*BDMAP_H_*/
