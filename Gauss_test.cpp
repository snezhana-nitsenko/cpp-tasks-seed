#include "Gauss_solve.h"

#include <gtest/gtest.h>

#include <random>

namespace
{
void expect_vector_near(const GaussVector& actual, const GaussVector& expected, double eps)
{
    ASSERT_EQ(actual.size(), expected.size());
    for (Eigen::Index i = 0; i < actual.size(); ++i)
    {
        EXPECT_NEAR(actual(i), expected(i), eps);
    }
}

double next_random_value(std::mt19937_64& generator)
{
    const auto value = generator();
    return (static_cast<double>(value % 2001U) - 1000.0) / 100.0;
}

GaussMatrix make_augmented_system(const GaussMatrix& a, const GaussVector& x)
{
    GaussMatrix ab(a.rows(), a.cols() + 1);
    ab.leftCols(a.cols()) = a;
    ab.col(a.cols()) = a * x;
    return ab;
}
} // namespace

TEST(GaussSolve, SmallSolve)
{
    GaussMatrix ab(2, 3);
    ab << 2.0, 1.0, 5.0,
        1.0, -1.0, 1.0;

    const GaussVector actual = Gauss_solve(ab);

    GaussVector expected(2);
    expected << 2.0, 1.0;
    expect_vector_near(actual, expected, 1e-9);
}

TEST(GaussSolve, UsesRowSwap)
{
    GaussMatrix ab(2, 3);
    ab << 0.0, 2.0, 4.0,
        3.0, 4.0, 10.0;

    const GaussVector actual = Gauss_solve(ab);

    GaussVector expected(2);
    expected << 2.0 / 3.0, 2.0;
    expect_vector_near(actual, expected, 1e-9);
}

TEST(GaussSolve, RandomGeneratedBigSystem)
{
    constexpr Eigen::Index n = 80;
    std::mt19937_64 generator(37945656U);

    GaussMatrix a(n, n);
    GaussVector expected(n);

    for (Eigen::Index i = 0; i < n; ++i)
    {
        double row_sum = 0.0;
        for (Eigen::Index j = 0; j < n; ++j)
        {
            const double value = next_random_value(generator);
            a(i, j) = value;
            row_sum += std::abs(value);
        }
        a(i, i) = row_sum + 10.0;
        expected(i) = next_random_value(generator);
    }

    GaussMatrix ab = make_augmented_system(a, expected);
    const GaussVector actual = Gauss_solve(ab);

    expect_vector_near(actual, expected, 1e-7);
}

TEST(GaussSolve, ThrowsOnSingularSystem)
{
    GaussMatrix ab(2, 3);
    ab << 1.0, 2.0, 3.0,
        2.0, 4.0, 6.0;

    EXPECT_THROW(Gauss_solve(ab), std::runtime_error);
}
