///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <cmath>
#include <limits>

namespace trial
{
namespace online
{
namespace correlation
{

template <typename T, template <typename, bool> class Avg>
void basic_pearson<T, Avg>::clear()
{
    covariance.clear();
    average_x.clear();
    average_y.clear();
}

template <typename T, template <typename, bool> class Avg>
auto basic_pearson<T, Avg>::size() const -> size_type
{
    return covariance.size();
}

template <typename T, template <typename, bool> class Avg>
void basic_pearson<T, Avg>::push(value_type x, value_type y)
{
    covariance.push(x, y);
    average_x.push(x);
    average_y.push(y);
}

template <typename T, template <typename, bool> class Avg>
auto basic_pearson<T, Avg>::value() const -> value_type
{
    const value_type variance_product = average_x.variance() * average_y.variance();
    if (variance_product < std::numeric_limits<value_type>::epsilon())
        return value_type(1);
    return covariance.normalized_value() / std::sqrt(variance_product);
}

} // namespace correlation
} // namespace online
} // namespace trial
