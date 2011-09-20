//===--- port.h - OS/cpu specific stuff for include-what-you-use ----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// Source file for architecture-specific logic.

#ifndef DEVTOOLS_MAINTENANCE_INCLUDE_WHAT_YOU_USE_PORT_H_
#define DEVTOOLS_MAINTENANCE_INCLUDE_WHAT_YOU_USE_PORT_H_

#include <stdlib.h>  // for abort
#include <iostream>

namespace include_what_you_use {

// Helper class that allows programmers to log extra information in CHECK_s.
class FatalMessageEmitter {
 public:
  FatalMessageEmitter(const char* file, int line, const char* message) {
    stream() << file << ":" << line << ": Assertion failed: " << message;
  }
  ~FatalMessageEmitter() {
    stream() << ::std::endl;
    ::abort();
  }
  ::std::ostream& stream() { return ::std::cerr; }
};

// Helper class that allows an ostream to 'appear' as a void expression.
class OstreamVoidifier {
 public:
  // This has to be an operator with a precedence lower than << but
  // higher than ?:
  void operator&(::std::ostream&) {}
};

}  // namespace include_what_you_use

// Usage: CHECK_(condition) << extra << information;
// The file, line, condition and extra information will be printed to cerr,
// then the program will abort.
#define CHECK_(x)  (x) ? (void)0 : \
  ::include_what_you_use::OstreamVoidifier() & \
  ::include_what_you_use::FatalMessageEmitter( \
      __FILE__, __LINE__, #x).stream()

#if defined(_MSC_VER)

# define NOMINMAX
# include <windows.h>

# define getcwd _getcwd
# define snprintf _snprintf

# include "Shlwapi.h"  // for PathMatchSpec

# pragma comment(lib, "Shlwapi.lib")

inline bool GlobMatchesPath(const char *glob, const char *path) {
  return PathMatchSpec(path, glob);
}

// FIXME: This undef is necessary to prevent conflicts between llvm
//        and Windows headers.  Eventually fnmatch functionality
//        should be wrapped inside llvm's PathV2 library.
# undef interface    // used in Shlwapi.h

#else  // #if defined(_MSC_VER)

#include <fnmatch.h>

inline bool GlobMatchesPath(const char *glob, const char *path) {
  return fnmatch(glob, path, FNM_PATHNAME) == 0;
}

#endif  // #if defined(_MSC_VER)

#endif  // DEVTOOLS_MAINTENANCE_INCLUDE_WHAT_YOU_USE_PORT_H_
