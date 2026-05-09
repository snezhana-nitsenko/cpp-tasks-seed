#ifndef SORTING_H
#define SORTING_H

// Header-only

#include <algorithm>
#include <iterator>

// Для swap
#include "collvalue.h"

// ----------------------------- Пузырёк (например) --------------------------------------
template <typename Iterator>
void bubble_sort(Iterator begin, Iterator end)
{
    if (begin == end)
    {
        return;
    }

    bool swapped = true;
    while (swapped)
    {
        swapped = false;
        Iterator current = begin;
        Iterator next = current;
        ++next;

        while (next != end)
        {
            if (*next < *current)
            {
                using std::iter_swap;
                iter_swap(current, next);
                swapped = true;
            }

            ++current;
            ++next;
        }
    }
}

// --------------------------- QuickSort (например) ---------------------------------------
template <typename Iterator>
void quick_sort(Iterator begin, Iterator end)
{
    const auto size = std::distance(begin, end);
    if (size < 2)
    {
        return;
    }

    Iterator left = begin;
    Iterator right = end - 1;
    const auto pivot = *(begin + size / 2);

    while (left <= right)
    {
        while (*left < pivot)
        {
            ++left;
        }

        while (pivot < *right)
        {
            --right;
        }

        if (left <= right)
        {
            using std::iter_swap;
            iter_swap(left, right);
            ++left;

            if (right == begin)
            {
                break;
            }
            --right;
        }
    }

    quick_sort(begin, right + 1);
    quick_sort(left, end);
}

#endif // SORTING_H
