#ifndef TRIAL_ONLINE_DECAY_MOMENT_HPP
#define TRIAL_ONLINE_DECAY_MOMENT_HPP

///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2018 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/detail/type_traits.hpp>
#include <trial/online/with.hpp>

namespace trial
{
namespace online
{
namespace decay
{

template <typename T, online::with Moment>
class basic_moment;

//! @brief Exponential smoothing with compensation for bias towards the initial value.
//!
//! See http://breese.github.io/2015/10/26/on-average.html

template <typename T>
class basic_moment<T, with::mean>
{
protected:
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type");

public:
    using value_type = T;

    basic_moment(value_type mean_factor) noexcept;

    basic_moment(const basic_moment&) = default;
    basic_moment(basic_moment&&) = default;
    basic_moment& operator= (const basic_moment&) = default;
    basic_moment& operator= (basic_moment&&) = default;

    void clear() noexcept;
    void push(value_type) noexcept;

    value_type mean() const noexcept;

protected:
    const value_type mean_factor;
    value_type normalization = value_type(0);
    struct
    {
        value_type mean = value_type(0);
    } sum;
};

// With variance

template <typename T>
class basic_moment<T, with::variance>
    : public basic_moment<T, with::mean>
{
protected:
    using super = basic_moment<T, with::mean>;

public:
    using typename super::value_type;

    basic_moment(value_type mean_factor, value_type var_factor) noexcept;

    basic_moment(const basic_moment&) = default;
    basic_moment(basic_moment&&) = default;
    basic_moment& operator= (const basic_moment&) = default;
    basic_moment& operator= (basic_moment&&) = default;

    void clear() noexcept;
    void push(value_type) noexcept;

    using super::mean;
    value_type variance() const noexcept;

protected:
    const value_type var_factor;
    value_type normalization = value_type(0);
    struct
    {
        value_type variance = value_type(0);
    } sum;
};

// With skewness

template <typename T>
class basic_moment<T, with::skewness>
    : public basic_moment<T, with::variance>
{
protected:
    using super = basic_moment<T, with::variance>;

public:
    using typename super::value_type;

    basic_moment(value_type mean_factor, value_type var_factor, value_type skewness_factor) noexcept;

    basic_moment(const basic_moment&) = default;
    basic_moment(basic_moment&&) = default;
    basic_moment& operator= (const basic_moment&) = default;
    basic_moment& operator= (basic_moment&&) = default;

    void clear() noexcept;
    void push(value_type) noexcept;

    using super::mean;
    using super::variance;
    value_type skewness() const noexcept;

protected:
    const value_type skewness_factor;
    value_type normalization = value_type(0);
    struct
    {
        value_type skewness = value_type(0);
    } sum;
};

// With kurtosis

template <typename T>
class basic_moment<T, with::kurtosis>
    : public basic_moment<T, with::skewness>
{
protected:
    using super = basic_moment<T, with::skewness>;

public:
    using typename super::value_type;

    basic_moment(value_type mean_factor, value_type var_factor, value_type skewness_factor, value_type kurtosis_factor) noexcept;

    basic_moment(const basic_moment&) = default;
    basic_moment(basic_moment&&) = default;
    basic_moment& operator= (const basic_moment&) = default;
    basic_moment& operator= (basic_moment&&) = default;

    void clear() noexcept;
    void push(value_type) noexcept;

    using super::mean;
    using super::variance;
    using super::skewness;
    value_type kurtosis() const noexcept;

protected:
    const value_type kurtosis_factor;
    struct
    {
        value_type kurtosis = value_type(0);
    } sum;
    value_type normalization = value_type(0);
};

// Convenience

template <typename T>
using moment = basic_moment<T, with::mean>;

template <typename T>
using moment_variance = basic_moment<T, with::variance>;

template <typename T>
using moment_skewness = basic_moment<T, with::skewness>;

template <typename T>
using moment_kurtosis = basic_moment<T, with::kurtosis>;

} // namespace decay
} // namespace online
} // namespace trial

#include <trial/online/decay/detail/moment.ipp>

#endif // TRIAL_ONLINE_DECAY_MOMENT_HPP
