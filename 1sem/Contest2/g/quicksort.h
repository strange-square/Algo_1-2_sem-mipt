#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "stack.h"
#include "insertsort.h"

namespace QuickModifier
{
    enum MOD {NONE, ONE_BRANCH, NO_RECURSION,
                      OPTIMISATION_OF_THE_END,
                      OPTIMISATION_OF_THE_PARTITION, END};
    const size_t enumSize = MOD::END - MOD::NONE;
    const std::string dict[enumSize] {
                      "NONE", "ONE_BRANCH", "NO_RECURSION",
                      "OPTIMISATION_OF_THE_END",
                      "OPTIMISATION_OF_THE_PARTITION"};
    std::string toString(MOD x)
    {
        return dict[x];
    }
    enum MODPART{ONEITER, TWOITER};
}

template <typename T>
struct IsLessQuick
{
  	bool operator()(const T& l, const T& r) const
  	{
  		return l < r;
  	}
};

template <typename T>
T* rand_pivot(T* part_begin, T* part_end)
{
    srand(time(0));
    return part_begin + rand() % (part_end - part_begin);
}

template <class T, class TLess = IsLessQuick<T>>
T* partition (T* part_begin, T* part_end, QuickModifier::MODPART mod = QuickModifier::MODPART::ONEITER,
                                const TLess& isLess = TLess())
{
    void (*swap)(T& a, T& b) = [](T& a, T& b)
    {
        T temp = a;
        a = b;
        b = temp;
    };

    T* i = part_begin;
    T* pivot = rand_pivot(part_begin, part_end + 1);
    swap (*pivot, *part_end);

    switch (mod)
    {
        case QuickModifier::MODPART::ONEITER:
        {
            for (T* j = part_begin; j != part_end; j++)
            {
                if (isLess(*j, *part_end))
                {
                    swap(*i, *j);
                    i++;
                }
            }
            break;
        }
        case QuickModifier::MODPART::TWOITER:
        {
            T* j = part_end - 1;
            do {
                while (isLess(*i, *part_end)) i++;
                while ( isLess(*part_end, *j)) j--;
                if (i <= j) {
                  swap(*i, *j);
                  i++; j--;
                }
            } while ( i<=j );
            break;
        }
        default:
            throw "Error: undefined partition modifier";
    }
    swap (*part_end, *i);
    return i;
}

template <class T, class TLess = IsLessQuick<T>>
void quicksort (T* part_begin, T* part_end, QuickModifier::MOD mod = QuickModifier::MOD::NONE,
                            const TLess& isLess = TLess())
{
    QuickModifier::MODPART partMod = QuickModifier::MODPART::ONEITER;
    switch (mod)
    {
        case QuickModifier::MOD::OPTIMISATION_OF_THE_END:
        {
            if (part_end - part_begin <= 50){
                insertsort(part_begin, part_end, isLess);
                return;
            }
        }
        case QuickModifier::MOD::OPTIMISATION_OF_THE_PARTITION:
        {
            if (mod == QuickModifier::MOD::OPTIMISATION_OF_THE_PARTITION)
            {
                partMod = QuickModifier::MODPART::TWOITER;
            }
        }
        case QuickModifier::MOD::NONE:
        {
            if (part_begin != part_end)
            {
                T* pivot = partition(part_begin, part_end - 1, partMod, isLess);
                quicksort(part_begin, pivot, mod, isLess);
                quicksort(pivot + 1, part_end, mod, isLess);
            }
            return;
        }
        default:
            break;
    }


    Stack < Pair<T*> > s;
    Pair <T*> pair_be(part_begin, part_end);
    s.push_back(pair_be);
    while (!s.is_empty())
    {
        Pair <T*> pair = s.pop_back();
        if (pair.r - pair.l < 1)
            continue;
        T* pivot = partition(pair.l, pair.r, partMod, isLess);

        Pair <T*> pair_left(pair.l, pivot - 1);
        Pair <T*> pair_right(pivot + 1, pair.r);

        bool temp = pivot - pair.l > pair.r - pivot;
        s.push_back(temp ? pair_left : pair_right);
        switch (mod)
        {
            case QuickModifier::MOD::NO_RECURSION:
            {
                if (temp) s.push_back(pair_right);
                else s.push_back(pair_left);
                break;
            }
            case QuickModifier::MOD::ONE_BRANCH:
            {
                if (temp) quicksort(pivot + 1, pair.r, mod, isLess);
                else quicksort(pair.l, pivot - 1, mod, isLess);
                break;
            }
            default:
                throw "Error: undefined modifier";
        }
    }
}

#endif /* QUICKSORT_H */
