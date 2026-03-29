/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2026
 *
 * @file    bubble_sort_strategy.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   TODO: Fill me accordingly
 * @version 1.0.0
 * @date    3/28/26
 *
 * @copyright Copyright (c) 2026 James R. Daehn
 */

#ifndef LAB11_BUBBLE_SORT_STRATEGY_H
#define LAB11_BUBBLE_SORT_STRATEGY_H

#include "sort_strategy.h"

namespace csc232
{

    template < typename T >
    class bubble_sort_strategy : public sort_strategy< T >
    {
    public:
        void sort( T *array, std::size_t size ) const override;

    private:
        static void bubble_sort( T *array, std::size_t size );
    };

} // csc232

#endif // LAB11_BUBBLE_SORT_STRATEGY_H
