/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2026
 *
 * @file    selection_sort_strategy.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   Selection sort implementation using recursion.
 * @version 1.0.0
 * @date    3/28/26
 *
 * @copyright Copyright (c) 2026 James R. Daehn
 */

#include "selection_sort_strategy.h"
#include <utility>

namespace csc232
{
    template < typename T >
    void selection_sort_strategy< T >::sort( T *array, std::size_t size ) const
    {
        selection_sort( array, size, 0 );
    }

    template < typename T >
    void selection_sort_strategy< T >::selection_sort( T *array, std::size_t size, std::size_t start_index )
    {
        // TODO: Task 1 - Implement me accordingly
    }

} // csc232
