#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "sorting.h"

template <typename Sort>
void expect_sort_works(Sort sort)
{
    const std::vector<std::vector<int>> inputs =
    {
        {},
        {1},
        {1, 2, 3, 4, 5},
        {5, 4, 3, 2, 1},
        {3, 1, 2, 3, 1, 0, -4, 8},
        {7, 7, 7, 7},
    };

    for (const auto& input : inputs)
    {
        auto actual = input;
        auto expected = input;
        std::sort(expected.begin(), expected.end());

        sort(actual.begin(), actual.end());

        EXPECT_EQ(expected, actual);
    }
}

TEST(SortingSuite, BubbleSortWorks)
{
    expect_sort_works([](auto begin, auto end)
    {
        bubble_sort(begin, end);
    });
}

TEST(SortingSuite, QuickSortWorks)
{
    expect_sort_works([](auto begin, auto end)
    {
        quick_sort(begin, end);
    });
}
