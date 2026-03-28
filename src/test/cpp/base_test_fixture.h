/**
 * @file    base_test_fixture.h
 * @brief   Google Test implementation base test fixture.
 *
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @version 1.0.0
 * @date    01/01/2025
 *
 * @copyright Copyright (c) 2026 James R. Daehn
 */

#ifndef CSC232_BASE_TEST_FIXTURE_H
#define CSC232_BASE_TEST_FIXTURE_H

#include <fstream>
#include <gtest/gtest.h>
#include <regex>

/**
 * Namespace to encapsulate course work in CSC232 - Data Structures.
 */
namespace csc232
{
    // clang-format off
    template < typename T, typename C >
    concept HasReadMethod = requires( const C object )
    {
        { object.read( ) } -> std::same_as< T >;
    };

    template < typename T, typename C >
    concept HasWriteMethod = requires( C &object, const T &value )
    {
        { object.write( value ) } -> std::same_as< void >;
    };
    // clang-format off

    /**
     * @brief Base test fixture that sets up grading for this assignment.
     */
    class CSC232BaseTestFixture : public ::testing::Test // NOLINT(*-special-member-functions)
    {
    public:
        /**
         * Default constructor.
         */
        CSC232BaseTestFixture( ) = default;

        /**
         * Default virtual destructor.
         */
        virtual ~CSC232BaseTestFixture( ) = default;

    protected:
        void SetUp( ) override
        {
            ::testing::FLAGS_gtest_death_test_style = "threadsafe";
            // Redirect cout to our stringstream buffer or any other ostream
            sbuf = std::cout.rdbuf( );
            std::cout.rdbuf( buffer.rdbuf( ) );
            AdditionalSetup( );
        }

        void TearDown( ) override
        {
            // When done, redirect cout to its old self
            std::cout.rdbuf( sbuf );
            sbuf = nullptr;

            AdditionalTearDown( );
        }

        virtual void AdditionalSetup( )
        {
            /* template method for any customized additional setup */
        }

        virtual void AdditionalTearDown( )
        {
            /* template method for any customized additional setup */
        }

        // NOLINTBEGIN(bugprone-easily-swappable-parameters)

        /**
         * @brief Utility method to see if a class has been declared in some particular file.
         *
         * @param file_path the path to the file under interrogation
         * @param class_name a class name whose declaration we seek in the given file
         *
         * @return true if the given class is declared in the given file, false otherwise.
         */
        virtual auto is_class_declared( const std::string &file_path, const std::string &class_name ) -> bool
        {
            std::ifstream file( file_path );
            if ( !file.is_open( ) )
            {
                std::cerr << "Unable to open file\n";
                return false;
            }

            std::string line;
            std::regex class_pattern( "\\bclass\\s+" + class_name + "\\b" );
            while ( std::getline( file, line ) )
            {
                if ( std::regex_search( line, class_pattern ) )
                {
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief Utility method to see if a class has been declared within a given namespace in some particular file.
         *
         * @param file_path the path to the file under interrogation
         * @param namespace_name the namespace under interrogation
         * @param class_name a class name whose declaration we seek in the given file and namespace
         *
         * @return true if the given class is declared in the specfied namespace, false otherwise
         */
        virtual auto is_class_in_namespace_declared( const std::string &file_path, const std::string &namespace_name,
                                                     const std::string &class_name ) -> bool
        {
            std::ifstream file( file_path );
            if ( !file.is_open( ) )
            {
                std::cerr << "Unable to open file\n";
                return false;
            }

            std::string line;
            std::regex namespace_pattern( "\\bnamespace\\s+" + namespace_name + "\\b" );
            std::regex class_pattern( "\\bclass\\s+" + class_name + "\\b" );
            bool in_namespace = false;

            while ( std::getline( file, line ) )
            {
                if ( std::regex_search( line, namespace_pattern ) )
                {
                    in_namespace = true;
                }
                if ( in_namespace && std::regex_search( line, class_pattern ) )
                {
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief Utility method to see if a class has been declared within a given namespace, derived from some base class, in some particular file.
         *
         * @param file_path the path to the file under interrogation
         * @param namespace_name the namespace under interrogation
         * @param class_name a class name whose declaration we seek in the given file and namespace
         * @param base_class_name a class name from which we are deriving
         *
         * @return true if the given class is declared in the given namespace and derived the given base class, false otherwise.
         */
        virtual auto is_class_derived_from_base( const std::string &file_path, const std::string &namespace_name,
                                                 const std::string &class_name, const std::string &base_class_name ) -> bool
        {
            std::ifstream file( file_path );
            if ( !file.is_open( ) )
            {
                std::cerr << "Unable to open file\n";
                return false;
            }

            std::string line;
            std::regex namespace_pattern( "\\bnamespace\\s+" + namespace_name + "\\b" );
            std::regex class_pattern( "\\bclass\\s+" + class_name + R"(\s*:\s*public\s+)" + base_class_name + "\\b" );
            bool in_namespace = false;

            while ( std::getline( file, line ) )
            {
                if ( std::regex_search( line, namespace_pattern ) )
                {
                    in_namespace = true;
                }
                if ( in_namespace && std::regex_search( line, class_pattern ) )
                {
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief Utility method to see if a particular method has been declared in a given class.
         *
         * @param file_path the path to the file under interrogation
         * @param namespace_name the namespace under interrogation
         * @param class_name a class name whose declaration we seek in the given file and namespace
         * @param method_name a method name we wish to determine is declared in the given class
         *
         * @return true if the given method is declared in a class found in the given namespace, false otherwise.
         */
        virtual auto is_method_declared_in_class( const std::string &file_path, const std::string &namespace_name, const std::string &class_name, const std::string &method_name ) -> bool
        {
            std::ifstream file( file_path );
            if ( !file.is_open( ) )
            {
                std::cerr << "Unable to open file\n";
                return false;
            }

            std::string line;
            std::regex namespace_pattern( "\\bnamespace\\s+" + namespace_name + "\\b" );
            std::regex class_pattern( "\\bclass\\s+" + class_name + "\\b" );
            std::regex method_pattern( "\\b" + method_name + "\\s*\\(" );
            bool in_namespace = false;
            bool in_class = false;

            while ( std::getline( file, line ) )
            {
                if ( std::regex_search( line, namespace_pattern ) )
                {
                    in_namespace = true;
                }
                if ( in_namespace && std::regex_search( line, class_pattern ) )
                {
                    in_class = true;
                }
                if ( in_class && std::regex_search( line, method_pattern ) )
                {
                    return true;
                }
            }
            return false;
        }
        // NOLINTEND(bugprone-easily-swappable-parameters)

    private:
        // Reusable objects for each unit test in this test fixture and any of its children
        std::stringstream buffer{ std::stringstream{} };
        std::streambuf *sbuf{ nullptr };
        /*
         * With the above in place, you can now have tests on output statements
         * like this:
         *
         * <some function call or executable that inserts info into output stream...>
         * const std::string expected{ "1/1/1902\n" }; // what you expect to have been inserted
         * const std::string actual{ buffer.str( ) };  // what was actually inserted
         * EXPECT_EQ( expected, actual );
         */
    };
}

#endif
