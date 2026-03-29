/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2026
 *
 * @file    sort_strategy_factory.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   TODO: Fill me accordingly
 * @version 1.0.0
 * @date    3/28/26
 *
 * @copyright Copyright (c) 2026 James R. Daehn
 */

#ifndef LAB11_SORT_STRATEGY_FACTORY_H
#define LAB11_SORT_STRATEGY_FACTORY_H

#include "sort_strategy.h"
#include "sort_type.h"
#include <memory>

namespace csc232
{
    template < typename T >
    class sort_strategy_factory
    {
    public:
        static auto create( sort_type type ) -> std::unique_ptr< sort_strategy< T > >;
    };

} // csc232

#endif // LAB11_SORT_STRATEGY_FACTORY_H
