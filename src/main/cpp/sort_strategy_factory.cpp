/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2026
 *
 * @file    sort_strategy_factory.cpp
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   TODO: Fill me accordingly
 * @version 1.0.0
 * @date    3/28/26
 *
 * @copyright Copyright (c) 2026 James R. Daehn
 */

#include "sort_strategy_factory.h"
#include "bubble_sort_strategy.h"
#include "insertion_sort_strategy.h"
#include "selection_sort_strategy.h"

namespace csc232
{
    template < typename T >
    auto sort_strategy_factory< T >::create( sort_type type ) -> std::unique_ptr< sort_strategy< T > >
    {
        switch ( type )
        {
        case sort_type::bubble:
            return std::make_unique< bubble_sort_strategy< T > >( );
        case sort_type::insertion:
            return std::make_unique< insertion_sort_strategy< T > >( );
        case sort_type::selection:
            return std::make_unique< selection_sort_strategy< T > >( );
        default:
            return nullptr;
        }
    }
} // csc232
