#include "Gauss_solve.h"
#include "util.h"

#include <exception>
#include <fstream>
#include <iostream>

int main(int argc, const char *argv[])
{
    if (argc != 2 && argc != 3)
    {
        std::cerr << "usage: " << argv[0] << " input.csv [output.csv]\n";
        return 1;
    }

    try
    {
        GaussMatrix ab = load_csv_to_matrix(argv[1]);
        GaussVector answer = Gauss_solve(ab);

        if (argc == 3)
        {
            std::ofstream out(argv[2]);
            if (!out.is_open())
            {
                throw std::runtime_error("cannot open output csv file");
            }
            print_vector_as_csv(out, answer);
        }
        else
        {
            print_vector_as_csv(std::cout, answer);
        }
    }
    catch (const std::exception& error)
    {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}
