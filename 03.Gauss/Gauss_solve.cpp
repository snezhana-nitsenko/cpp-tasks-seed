#include "Gauss_solve.h"

#include <cmath>
#include <stdexcept>

namespace
{
constexpr double eps = 1e-12;
}

GaussVector Gauss_solve(GaussMatrix& ab)
{
    const Eigen::Index rows = ab.rows();
    const Eigen::Index cols = ab.cols();

    if (rows == 0)
    {
        throw std::invalid_argument("empty system");
    }
    if (cols != rows + 1)
    {
        throw std::invalid_argument("augmented matrix must have n rows and n + 1 columns");
    }

    for (Eigen::Index col = 0; col < rows; ++col)
    {
        Eigen::Index pivot = col;
        double best = std::abs(ab(col, col));

        for (Eigen::Index row = col + 1; row < rows; ++row)
        {
            const double candidate = std::abs(ab(row, col));
            if (candidate > best)
            {
                best = candidate;
                pivot = row;
            }
        }

        if (best < eps)
        {
            throw std::runtime_error("system has no unique solution");
        }

        if (pivot != col)
        {
            ab.row(col).swap(ab.row(pivot));
        }

        const double pivot_value = ab(col, col);
        ab.row(col) /= pivot_value;

        for (Eigen::Index row = 0; row < rows; ++row)
        {
            if (row == col)
            {
                continue;
            }

            const double factor = ab(row, col);
            if (std::abs(factor) > eps)
            {
                ab.row(row) -= factor * ab.row(col);
            }
        }
    }

    return ab.col(rows);
}
