/**
 * CSC232 - Data Structures
 * Missouri State University, Spring 2026
 *
 * @file    sort_strategy.h
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @brief   TODO: Fill me accordingly
 * @version 1.0.0
 * @date    3/28/26
 *
 * @copyright Copyright (c) 2026 James R. Daehn
 */

#ifndef LAB11_SORT_STRATEGY_H
#define LAB11_SORT_STRATEGY_H
#include <cstddef>

namespace csc232
{
    /**
     * An interface for defining different sort strategies.
     * @tparam T the type of data to be sorted by this sort strategy
     * @pre T defines relational operators.
     */
    template < typename T >
    class sort_strategy
    {
    public:
        /**
         * @brief Default destructor.
         */
        virtual ~sort_strategy( ) = default;
        /**
         * @brief Sort the data in place.
         * @param array the array of data to be sorted
         * @param size the size of the given array
         */
        virtual void sort( T *array, std::size_t size ) const = 0;
    };
}
#endif // LAB11_SORT_STRATEGY_H
