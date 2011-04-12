//===--- specialization_needs_decl.cc - test input file for iwyu ----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

// Tests that when we specialize a template class, we require a declaration
// of that class.

#include "tests/specialization_needs_decl-d1.h"

template<> struct TplStruct<int> { };


/**** IWYU_SUMMARY

tests/specialization_needs_decl.cc should add these lines:
template <typename T> struct TplStruct;

tests/specialization_needs_decl.cc should remove these lines:
- #include "tests/specialization_needs_decl-d1.h"  // lines XX-XX

The full include-list for tests/specialization_needs_decl.cc:
template <typename T> struct TplStruct;

***** IWYU_SUMMARY */
