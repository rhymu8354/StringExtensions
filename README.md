# StringExtensions

This is library contains C++ string-oriented utilities, many of which ought to
be in the standard library, but aren't.

## Usage

The `StringExtensions::vsprintf` function is the C++ equivalent of the
`vsprintf` function from the standard C library.

The `StringExtensions::sprintf` function is the C++ equivalent of the
`sprintf` function from the standard C library.

The `StringExtensions::wcstombs` function is the C++ equivalent of the
`wcstombs` function from the standard C library.

The `StringExtensions::Trim` function makes a copy of a string and removes any
whitespace from the front and back of the copy.

The `StringExtensions::Indent` function breaks input text into lines and
indents them.

The `StringExtensions::ParseComponent` function is used to break apart a
composite string into pieces, according to commonly-used delimiters, and
respecting escaped characters.

The `StringExtensions::Escape` and `StringExtensions::Unescape` functions are
useful for dealing with string that contain characters that need to be
"escaped" to avoid parsing issues when used within structures or compositions.

The `StringExtensions::Split` and `StringExtensions::Join` functions are useful
for dealing with strings which compose lists of smaller strings.

The `StringExtensions::ToLower` function is used to convert all upper-case
characters in a string to lower-case.

The `StringExtensions::ToInteger` function is used to parse integers
represented in strings.

## Supported platforms / recommended toolchains

This is a portable C++11 library which depends only on the C++11 compiler and
standard library, so it should be supported on almost any platform.  The
following are recommended toolchains for popular platforms.

* Windows -- [Visual Studio](https://www.visualstudio.com/)
  (Microsoft Visual C++)
* Linux -- clang or gcc
* MacOS -- Xcode (clang)

## Building

This library is not intended to stand alone.  It is intended to be included in
a larger solution which uses [CMake](https://cmake.org/) to generate the build
system and build applications which will link with the library.

There are two distinct steps in the build process:

1. Generation of the build system, using CMake
2. Compiling, linking, etc., using CMake-compatible toolchain

### Prerequisites

* [CMake](https://cmake.org/) version 3.8 or newer
* C++11 toolchain compatible with CMake for your development platform (e.g.
  [Visual Studio](https://www.visualstudio.com/) on Windows)

### Build system generation

Generate the build system using [CMake](https://cmake.org/) from the solution
root.  For example:

```bash
mkdir build
cd build
cmake -G "Visual Studio 15 2017" -A "x64" ..
```

### Compiling, linking, et cetera

Either use [CMake](https://cmake.org/) or your toolchain's IDE to build.
For [CMake](https://cmake.org/):

```bash
cd build
cmake --build . --config Release
```
