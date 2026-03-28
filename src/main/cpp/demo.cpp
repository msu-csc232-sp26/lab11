/**
 * @file    demo.cpp
 * @brief   Entry-point for demo target.
 *
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2026 James R. Daehn
 */

#include "csc232.h"

#if TEST_TASK1
// Placeholder for task 1 demo code
#endif

#if TEST_TASK2
// Placeholder for task 2 demo code
#endif

#if TEST_TASK3
// Placeholder for task 3 demo code
#endif

auto main( ) -> int
{
    std::cout << "Demo target" << std::endl;
    std::cout << "A random UUID: " << csc232::generate_uuid( ) << std::endl;
    return EXIT_SUCCESS;
}
