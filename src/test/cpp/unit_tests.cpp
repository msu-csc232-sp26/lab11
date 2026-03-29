/**
 * @file    unit_tests.cpp
 * @brief   Assignment unit testing for evaluation.
 *
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @version 1.0.0
 * @date    12/13/25
 *
 * @copyright Copyright (c) 2025 James R. Daehn
 */

// unit_tests.cpp
#include "base_test_fixture.h"
#include "csc232.h"
#include "selection_sort_strategy.h"
#include "sort_strategy.h"

#include "gtest/gtest.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <type_traits>

// Helper to test sorting behavior
template < typename T >
void expect_sorted( csc232::sort_strategy< T > &strategy, std::vector< T > input )
{
    std::vector< T > expected = input;
    std::sort( expected.begin( ), expected.end( ) );

    strategy.sort( input.data( ), input.size( ) );

    EXPECT_EQ( input, expected );
}

// -----------------------------------------------------------------------------
// Task 1 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK1
class Task1TestFixture : public csc232::CSC232BaseTestFixture
{
protected:
    void SetUp( ) override
    {
        // Initialize any shared state/resources for Task 1 tests.
    }

    void TearDown( ) override
    {
        // Cleanup for Task 1.
    }

    csc232::selection_sort_strategy< int > sorter; // NOLINT
};

TEST_F( Task1TestFixture, ItDoesNothingWithAnEmptyArray )
{
    expect_sorted( sorter, std::vector< int >{ } );
}

TEST_F( Task1TestFixture, ItCanSortArrayWithOneValue )
{
    expect_sorted( sorter, std::vector< int >{ 42 } ); // NOLINT
}

TEST_F( Task1TestFixture, ItCanSortSortedArray )
{
    expect_sorted( sorter, std::vector< int >{ 1, 2, 3, 4, 5 } ); // NOLINT
}

TEST_F( Task1TestFixture, ItCanSortReverseSortedArray )
{
    expect_sorted( sorter, std::vector< int >{ 5, 4, 3, 2, 1 } ); // NOLINT
}

TEST_F( Task1TestFixture, ItCanSortRandomUnsortedArray )
{
    expect_sorted( sorter, std::vector< int >{ 3, 1, 4, 2, 5, 9 } ); // NOLINT
}

TEST_F( Task1TestFixture, ItCanSortRandomUnsortedWithDuplicatesArray )
{
    expect_sorted( sorter, std::vector< int >{ 3, 1, 4, 1, 9, 9, 5, 9 } ); // NOLINT
}

#else
TEST( Task1Primer, ItIsNotReady )
{
    std::cerr << "Task 1 is not ready for evaluation; please toggle the TEST_TASK1 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK_1

// -----------------------------------------------------------------------------
// Task 2 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK2
class Task2TestFixture : public csc232::CSC232BaseTestFixture
{
protected:
    void SetUp( ) override { }
    void TearDown( ) override { }
    csc232::bubble_sort_strategy< int > sorter; // NOLINT
};

TEST_F( Task2TestFixture, ItDoesNothingWithAnEmptyArray )
{
    expect_sorted( sorter, std::vector< int >{ } );
}

TEST_F( Task2TestFixture, ItCanSortArrayWithOneValue )
{
    expect_sorted( sorter, std::vector< int >{ 42 } ); // NOLINT
}

TEST_F( Task2TestFixture, ItCanSortSortedArray )
{
    expect_sorted( sorter, std::vector< int >{ 1, 2, 3, 4, 5 } ); // NOLINT
}

TEST_F( Task2TestFixture, ItCanSortReverseSortedArray )
{
    expect_sorted( sorter, std::vector< int >{ 5, 4, 3, 2, 1 } ); // NOLINT
}

TEST_F( Task2TestFixture, ItCanSortRandomUnsortedArray )
{
    expect_sorted( sorter, std::vector< int >{ 3, 1, 4, 2, 5, 9 } ); // NOLINT
}

TEST_F( Task2TestFixture, ItCanSortRandomUnsortedWithDuplicatesArray )
{
    expect_sorted( sorter, std::vector< int >{ 3, 1, 4, 1, 9, 9, 5, 9 } ); // NOLINT
}
#else
TEST( Task2Primer, ItIsNotReady )
{
    std::cerr << "Task 2 is not ready for evaluation; please toggle the TEST_TASK2 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK_2

// -----------------------------------------------------------------------------
// Task 3 Fixture and Tests
// -----------------------------------------------------------------------------
#if TEST_TASK3
class Task3TestFixture : public csc232::CSC232BaseTestFixture
{
protected:
    void SetUp( ) override { }
    void TearDown( ) override { }
    csc232::insertion_sort_strategy< int > sorter; // NOLINT
};

TEST_F( Task3TestFixture, ItDoesNothingWithAnEmptyArray )
{
    expect_sorted( sorter, std::vector< int >{ } );
}

TEST_F( Task3TestFixture, ItCanSortArrayWithOneValue )
{
    expect_sorted( sorter, std::vector< int >{ 42 } ); // NOLINT
}

TEST_F( Task3TestFixture, ItCanSortSortedArray )
{
    expect_sorted( sorter, std::vector< int >{ 1, 2, 3, 4, 5 } ); // NOLINT
}

TEST_F( Task3TestFixture, ItCanSortReverseSortedArray )
{
    expect_sorted( sorter, std::vector< int >{ 5, 4, 3, 2, 1 } ); // NOLINT
}

TEST_F( Task3TestFixture, ItCanSortRandomUnsortedArray )
{
    expect_sorted( sorter, std::vector< int >{ 3, 1, 4, 2, 5, 9 } ); // NOLINT
}

TEST_F( Task3TestFixture, ItCanSortRandomUnsortedWithDuplicatesArray )
{
    expect_sorted( sorter, std::vector< int >{ 3, 1, 4, 1, 9, 9, 5, 9 } ); // NOLINT
}

#else
TEST( Task3Primer, ItIsNotReady )
{
    std::cerr << "Task 3 is not ready for evaluation; please toggle the TEST_TASK3 macro to TRUE\n";
    SUCCEED( );
}
#endif // TEST_TASK_3

// -----------------------------------------------------------------------------
// Helper: Print task-by-task summary and compute score
// -----------------------------------------------------------------------------
struct SuiteSummary
{
    std::string name;
    int passed = 0;
    int failed = 0;
    int disabled = 0;
    int total = 0;
    double percent = 0.0; // passing percentage among executed tests (pass+fail)
};

static void PrintPerTaskSummaryAndScore( )
{
    using testing::TestSuite;
    using testing::UnitTest;

    const UnitTest *unitTest = UnitTest::GetInstance( );

    // Aggregate per suite (fixture) results
    std::vector< SuiteSummary > summaries;
    int overall_passed = 0;
    int overall_failed = 0;

    for ( int i = 0; i < unitTest->total_test_suite_count( ); ++i )
    {
        const TestSuite *suite = unitTest->GetTestSuite( i );
        // Only include suites that correspond to our tasks.
        // (Optional) You can filter by name prefix "Task" if needed.
        SuiteSummary suiteSummary;
        suiteSummary.name = suite->name( );
        suiteSummary.passed = suite->successful_test_count( );
        suiteSummary.failed = suite->failed_test_count( );
        suiteSummary.disabled = suite->disabled_test_count( );
        suiteSummary.total = suite->total_test_count( );
        const int executed = suiteSummary.passed + suiteSummary.failed;
        suiteSummary.percent = ( executed > 0 ) ? ( 100.0 * suiteSummary.passed / executed ) : 0.0;

        summaries.push_back( suiteSummary );
        overall_passed += suiteSummary.passed;
        overall_failed += suiteSummary.failed;
    }

    const int overall_executed = overall_passed + overall_failed;
    const double overall_percent = ( overall_executed > 0 )
                                       ? ( 100.0 * static_cast< double >( overall_passed ) / overall_executed )
                                       : 0.0;

    // Pretty print
    std::cout << "\n========== Assignment Task Results ==========\n";
    for ( const auto &suiteSummary : summaries )
    {
        // Recommend naming fixtures exactly "Task1", "Task2", "Task3"
        if ( suiteSummary.name == "Task1TestFixture" ||
             suiteSummary.name == "Task2TestFixture" ||
             suiteSummary.name == "Task3TestFixture" )
        {
            std::cout << "Task: " << suiteSummary.name << "\n"
                      << "  Passing: " << suiteSummary.passed << "\n"
                      << "  Failing: " << suiteSummary.failed << "\n"
                      << "  Disabled: " << suiteSummary.disabled << "\n"
                      << "  Total (compiled): " << suiteSummary.total << "\n"
                      << "  Score (% passing among executed): "
                      << std::fixed << std::setprecision( 1 ) << suiteSummary.percent << "%\n\n";
        }
    }

    std::cout << "-------------- Overall Summary --------------\n"
              << "Passing: " << overall_passed << "\n"
              << "Failing: " << overall_failed << "\n"
              << "Executed: " << overall_executed << "\n"
              << "Overall Score: " << std::fixed << std::setprecision( 1 )
              << overall_percent << "%\n"
              << "=============================================\n\n";
}

// -----------------------------------------------------------------------------
// Custom main (do NOT link gtest_main)
// -----------------------------------------------------------------------------
auto main( int argc, char **argv ) -> int
{
    ::testing::InitGoogleTest( &argc, argv );
    const int gtest_return = RUN_ALL_TESTS( );

    // After tests run, compute/print summaries & score
    PrintPerTaskSummaryAndScore( );

    // Return gtest's status (0 means all tests passed)
    return gtest_return;
}
