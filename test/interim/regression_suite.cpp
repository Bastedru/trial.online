///////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 2019 Bjorn Reese <breese@users.sourceforge.net>
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
///////////////////////////////////////////////////////////////////////////////

#include <trial/online/detail/lightweight_test.hpp>
#include <trial/online/detail/functional.hpp>
#include <trial/online/interim/regression.hpp>

using namespace trial::online;

//-----------------------------------------------------------------------------

namespace double_suite
{

void test_ctor()
{
    interim::regression<double, 4> filter;
    TRIAL_TEST_EQ(filter.size(), 0);
}

void test_same()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::regression<double, 4> filter;

    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.size(), 1);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 1.0, tolerance);

    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.size(), 2);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 1.0, tolerance);

    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.size(), 3);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 1.0, tolerance);

    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.size(), 4);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 1.0, tolerance);

    // Window full

    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.size(), 4);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 1.0, tolerance);

    filter.push(1.0, 1.0);
    TRIAL_TEST_EQ(filter.size(), 4);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 1.0, tolerance);
}

void test_linear_increase_slope_1()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::regression<double, 4> filter;

    filter.push(0.0, 0.0);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);

    filter.push(1.0, 1.0);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(1.0), 1.0, tolerance);

    filter.push(2.0, 2.0);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(2.0), 2.0, tolerance);

    filter.push(3.0, 3.0);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(3.0), 3.0, tolerance);

    // Window full

    filter.push(4.0, 4.0);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(4.0), 4.0, tolerance);

    filter.push(5.0, 5.0);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(5.0), 5.0, tolerance);

    filter.push(6.0, 6.0);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(6.0), 6.0, tolerance);

    filter.push(7.0, 7.0);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(7.0), 7.0, tolerance);

    filter.push(8.0, 8.0);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(8.0), 8.0, tolerance);
}

void test_linear_increase_slope_2()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::regression<double, 4> filter;

    filter.push(0.0, 0.0);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);

    filter.push(1.0, 2.0);
    TRIAL_TEST_WITH(filter.slope(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(1.0), 2.0, tolerance);

    filter.push(2.0, 4.0);
    TRIAL_TEST_WITH(filter.slope(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(2.0), 4.0, tolerance);

    filter.push(3.0, 6.0);
    TRIAL_TEST_WITH(filter.slope(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(3.0), 6.0, tolerance);

    // Window full

    filter.push(4.0, 8.0);
    TRIAL_TEST_WITH(filter.slope(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(4.0), 8.0, tolerance);

    filter.push(5.0, 10.0);
    TRIAL_TEST_WITH(filter.slope(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(5.0), 10.0, tolerance);

    filter.push(6.0, 12.0);
    TRIAL_TEST_WITH(filter.slope(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(6.0), 12.0, tolerance);

    filter.push(7.0, 14.0);
    TRIAL_TEST_WITH(filter.slope(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(7.0), 14.0, tolerance);

    filter.push(8.0, 16.0);
    TRIAL_TEST_WITH(filter.slope(), 2.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(8.0), 16.0, tolerance);
}

void test_linear_increase_slope_1_alternating_noise()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::regression<double, 4> filter;

    // Fixed absolute error on increasing values means reduced relative error

    filter.push(0.0, 0.0);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);

    filter.push(1.0, 1.01);
    TRIAL_TEST_WITH(filter.slope(), 1.01, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(1.0), 1.01, tolerance);

    filter.push(2.0, 1.99);
    TRIAL_TEST_WITH(filter.slope(), 0.995, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.005, tolerance);
    TRIAL_TEST_WITH(filter.at(2.0), 1.995, tolerance);

    filter.push(3.0, 3.01);
    TRIAL_TEST_WITH(filter.slope(), 1.001, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.001, tolerance);
    TRIAL_TEST_WITH(filter.at(3.0), 3.004, tolerance);

    // Window full

    filter.push(4.0, 3.99);
    TRIAL_TEST_WITH(filter.slope(), 1.001, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.005, tolerance);
    TRIAL_TEST_WITH(filter.at(4.0), 3.999, tolerance);

    filter.push(5.0, 5.01);
    TRIAL_TEST_WITH(filter.slope(), 1.00181, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.00549645, tolerance);
    TRIAL_TEST_WITH(filter.at(5.0), 5.00355, tolerance);

    filter.push(6.0, 5.99);
    TRIAL_TEST_WITH(filter.slope(), 1.00065, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.0054348, tolerance);
    TRIAL_TEST_WITH(filter.at(6.0), 5.99848, tolerance);

    filter.push(7.0, 7.01);
    TRIAL_TEST_WITH(filter.slope(), 1.00357, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.019643, tolerance);
    TRIAL_TEST_WITH(filter.at(7.0), 7.00536, tolerance);

    filter.push(8.0, 7.99);
    TRIAL_TEST_WITH(filter.slope(), 1.004, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.03, tolerance);
    TRIAL_TEST_WITH(filter.at(8.0), 8.002, tolerance);

    filter.push(9.0, 9.01);
    TRIAL_TEST_WITH(filter.slope(), 1.00468, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.0351064, tolerance);
    TRIAL_TEST_WITH(filter.at(9.0), 9.00702, tolerance);

    filter.push(10.0, 9.99);
    TRIAL_TEST_WITH(filter.slope(), 1.00261, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.0250311, tolerance);
    TRIAL_TEST_WITH(filter.at(10.0), 10.0011, tolerance);

    filter.push(11.0, 11.01);
    TRIAL_TEST_WITH(filter.slope(), 1.004, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.038, tolerance);
    TRIAL_TEST_WITH(filter.at(11.0), 11.006, tolerance);

    filter.push(12.0, 11.99);
    TRIAL_TEST_WITH(filter.slope(), 1.004, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.046, tolerance);
    TRIAL_TEST_WITH(filter.at(12.0), 12.002, tolerance);

    filter.push(13.0, 13.01);
    TRIAL_TEST_WITH(filter.slope(), 1.00468, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.05383, tolerance);
    TRIAL_TEST_WITH(filter.at(13.0), 13.007, tolerance);

    filter.push(14.0, 13.99);
    TRIAL_TEST_WITH(filter.slope(), 1.00261, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -0.035466, tolerance);
    TRIAL_TEST_WITH(filter.at(14.0), 14.0011, tolerance);
}

void test_exponential_increase()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::regression<double, 4> filter;

    filter.push(1e0, 1e0);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 1.0, tolerance);

    filter.push(1e1, 1e1);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);

    filter.push(1e2, 1e2);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);

    filter.push(1e3, 1e3);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);

    // Window full

    filter.push(1e4, 1e4);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);

    filter.push(1e5, 1e5);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);

    filter.push(1e6, 1e6);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0), 0.0, tolerance);
}

void test_scatter()
{
    const auto tolerance = detail::close_to<double>(1e-5);
    interim::regression<double, 4> filter;

    filter.push(1.0, 1.0);
    TRIAL_TEST_WITH(filter.slope(), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(1.0), 1.0, tolerance);

    filter.push(2.0, 2.0);
    TRIAL_TEST_WITH(filter.slope(), 1.0, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.0, tolerance);
    TRIAL_TEST_WITH(filter.at(2.0), 2.0, tolerance);

    filter.push(3.0, 1.3);
    TRIAL_TEST_WITH(filter.slope(), 0.15, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 1.13333, tolerance);
    TRIAL_TEST_WITH(filter.at(3.0), 1.58333, tolerance);

    filter.push(4.0, 3.75);
    TRIAL_TEST_WITH(filter.slope(), 0.755, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), 0.125, tolerance);
    TRIAL_TEST_WITH(filter.at(4.0), 3.145, tolerance);

    // Window full

    filter.push(5.0, 2.25);
    TRIAL_TEST_WITH(filter.slope(), 0.755, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), -0.535, tolerance);
    TRIAL_TEST_WITH(filter.at(5.0), 3.24, tolerance);

    filter.push(6.0, 4.5);
    TRIAL_TEST_WITH(filter.slope(), 0.818617, tolerance);
    TRIAL_TEST_WITH(filter.at(0.0), -0.762943, tolerance);
    TRIAL_TEST_WITH(filter.at(6.0), 4.14876, tolerance);

    filter.push(7.0, 4.5);
    TRIAL_TEST_WITH(filter.slope(), 0.883696, tolerance);
    TRIAL_TEST_WITH(filter.at(0), -1.35854, tolerance);
    TRIAL_TEST_WITH(filter.at(7.0), 4.82733, tolerance);
}

void run()
{
    test_ctor();
    test_same();
    test_linear_increase_slope_1();
    test_linear_increase_slope_2();
    test_linear_increase_slope_1_alternating_noise();
    test_exponential_increase();
    test_scatter();
}

} // namespace double_suite

//-----------------------------------------------------------------------------
// main
//-----------------------------------------------------------------------------

int main()
{
    double_suite::run();

    return boost::report_errors();
}
