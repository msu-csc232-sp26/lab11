/**
 * @file    expanded_templates.cpp
 * @brief   Template class expansions.
 * @details Expanded templates provide the means to organizing template class declarations
 *          and definitions into separate header and source files like any other class, but
 *          without having to #include the source file in the header file itself. If we
 *          don't do that and try to compile our programs, we would be faced with an error
 *          that says that the instantiated member functions are not found. This issue is
 *          fixed by creating this separate source file that is compiled along with any target
 *          that wishes to use memory cell objects. This file is compiled as part of the project,
 *          and the template implementation file (memory_cell.cpp) is not compiled as part of
 *          the project. The downside to this strategy is that all the template expansions
 *          have to be listed by the programmer, and when the class template uses other class
 *          templates, sometimes those need to be listed too. The advantage is that if the
 *          implementation of the member functions in MemoryCell changes, only this file
 *          (expanded_templates.cpp) needs to be recompiled. Entries such as the following then,
 *          would appear here in this file:
 * @code
 * template class csc232::memory_cell< int >;
 * @endcode
 *          Notice too, how this is built into some target in the CMakeLists.txt file, as
 *          seen in the following code block, where we specify the files used to build, in
 *          this case, the main target.
 * @code
 * set(SRC_MAIN_FILES src/main/cpp/main.cpp src/main/cpp/expanded_templates.cpp)
 * @endcode
 * @see     The Weiss textbook, Appendix A Separate Compilation of Class Templates
 *
 * @author  Jim Daehn <jdaehn@missouristate.edu>
 * @version 1.0.0
 * @date    5/29/25
 *
 * @copyright Copyright (c) 2026 James R. Daehn. All rights reserved.
 */

// #include "csc232.h" // usually used to conditional declare based on current task
