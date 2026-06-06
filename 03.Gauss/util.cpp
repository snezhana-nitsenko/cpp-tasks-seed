#include "util.h"

#include <cctype>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
std::string trim(const std::string& value)
{
    std::size_t left = 0;
    while ((left < value.size()) && (std::isspace(static_cast<unsigned char>(value[left])) != 0))
    {
        ++left;
    }

    std::size_t right = value.size();
    while ((right > left) && (std::isspace(static_cast<unsigned char>(value[right - 1])) != 0))
    {
        --right;
    }

    return value.substr(left, right - left);
}

bool parse_csv_numbers(const std::string& line, std::vector<double>& result)
{
    result.clear();

    std::stringstream input(line);
    std::string cell;
    while (std::getline(input, cell, ','))
    {
        cell = trim(cell);
        if (cell.empty())
        {
            return false;
        }

        try
        {
            std::size_t parsed = 0;
            const double value = std::stod(cell, &parsed);
            if (parsed != cell.size())
            {
                return false;
            }
            result.push_back(value);
        }
        catch (const std::exception&)
        {
            return false;
        }
    }

    return !result.empty();
}
} // namespace

GaussMatrix load_csv_to_matrix(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("cannot open csv file");
    }

    std::vector<std::vector<double>> rows;
    std::string line;
    while (std::getline(file, line))
    {
        line = trim(line);
        if (line.empty())
        {
            continue;
        }

        std::vector<double> row;
        if (!parse_csv_numbers(line, row))
        {
            if (rows.empty())
            {
                continue;
            }
            throw std::runtime_error("bad numeric row in csv file");
        }

        if (!rows.empty() && row.size() != rows.front().size())
        {
            throw std::runtime_error("csv rows have different sizes");
        }
        rows.push_back(row);
    }

    if (rows.empty())
    {
        throw std::runtime_error("csv file has no numeric rows");
    }

    GaussMatrix matrix(static_cast<Eigen::Index>(rows.size()),
                       static_cast<Eigen::Index>(rows.front().size()));
    for (Eigen::Index i = 0; i < matrix.rows(); ++i)
    {
        for (Eigen::Index j = 0; j < matrix.cols(); ++j)
        {
            matrix(i, j) = rows[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)];
        }
    }

    return matrix;
}

void print_matrix_as_csv(std::ostream& out, const GaussMatrix& matrix, int prec)
{
    for (Eigen::Index j = 0; j < matrix.cols(); ++j)
    {
        if (j > 0)
        {
            out << ',';
        }
        out << 'c' << j;
    }
    out << '\n';

    out << std::fixed << std::setprecision(prec);
    for (Eigen::Index i = 0; i < matrix.rows(); ++i)
    {
        for (Eigen::Index j = 0; j < matrix.cols(); ++j)
        {
            if (j > 0)
            {
                out << ',';
            }
            out << matrix(i, j);
        }
        out << '\n';
    }
}

void print_vector_as_csv(std::ostream& out, const GaussVector& vector, int prec)
{
    out << "x\n";
    out << std::fixed << std::setprecision(prec);
    for (Eigen::Index i = 0; i < vector.size(); ++i)
    {
        out << vector(i) << '\n';
    }
}
