/**
 * @file    main.cpp
 * @brief   Entry-point for main target.
 *
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2026 James R. Daehn
 */

#include "bubble_sort_strategy.h"

#include <cstdlib>
#include <iostream>

#include "sort_strategy_factory.h"
using csc232::sort_strategy_factory;
using csc232::sort_type;

auto main( ) -> int
{

    int data[] = { 7, 3, 5, 2, 9, 1 }; // NOLINT
    const std::size_t size = std::size( data );

    const auto sorter = sort_strategy_factory< int >::create( sort_type::bubble );

    sorter->sort( data, size );

    for ( const int value : data )
    {
        std::cout << value << " ";
    }

    return EXIT_SUCCESS;
}
