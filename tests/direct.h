//===--- direct.h - test input file for iwyu ------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// This file is meant to be directly #included by a .cc file.  All it
// does is #include another file (which the .cc file is thus
// #including indirectly).

#ifndef DEVTOOLS_MAINTENANCE_INCLUDE_WHAT_YOU_USE_TESTS_DIRECT_H_
#define DEVTOOLS_MAINTENANCE_INCLUDE_WHAT_YOU_USE_TESTS_DIRECT_H_

#include "tests/indirect.h"

#endif  // DEVTOOLS_MAINTENANCE_INCLUDE_WHAT_YOU_USE_TESTS_DIRECT_H_

/**** IWYU_SUMMARY

tests/direct.h should add these lines:

tests/direct.h should remove these lines:
- #include "tests/indirect.h"  // lines XX-XX

The full include-list for tests/direct.h:

***** IWYU_SUMMARY */
