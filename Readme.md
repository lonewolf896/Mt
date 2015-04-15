# Mt [![Build Status](https://travis-ci.org/XAMPP/Mt.svg)](https://travis-ci.org/XAMPP/Mt)
Mt is developed as a part of MAT342 - Linear Algebra as a free, cross-platform student made replacement for MathWorks MatLab. Mt uses a new language called SML, or Simple[Sane] Math Language. SML allows for one to describe mathematical problems in a simple, succinct way.

Mt is also built to be extensible and open, anyone can build a module that can expand Mt or SML and have it work with any other Mt setup.

## Building from source

In order to build MT from source, you need a few things

 * clang ( >= 3.5 ), g++ ( >= 4.9 )
 * libc++, libc++abi (http://libcxx.llvm.org/ , http://libcxxabi.llvm.org/)
 * gperftools (https://code.google.com/p/gperftools/)
 * Protocol Buffers AKA. protobuf (https://github.com/google/protobuf)
 * doxygen
 * latex, pdflatex

Once you have everything, you can issue a `make` and it should build a debug build for you. If you wish for a release build `make release` is what you want.

To build the documentation, issue a `make docs` and it will build the docs for you.

If you wish to enable CPU profiling, `make perf` will build the profiling library into the binary.

## Modules

Mt is modular by default, allowing for anyone to build extensions onto the core Mt engine, to do so, all one needs to do is implement the Mt::Module class in their module and call the MODULE macro to make it a module, a simple module will look like this.

~~~{.cpp}
#include <Module.hh>

Mt::Module::Module(void) {
	// Initialization Code
}

Mt::Module::~Module(void) {
	// Teardown Code
}

MODULE("SuperMath")

~~~

And that is all there is to it.

## SML

Simple[Sane] Math Language is the language that is used by Mt. It allows for the user to express mathematical constructs in a way that seems as natural as possible. Disbanding all of the forced pragmatic constructs such as for loops, allowing one to express even things like summations in a succinct way.

A mathematic expression written in SML looks just like it would on paper

~~~
1+2-sin(4)
~~~

More complex examples can be expressed as well, like functions

~~~
F := (x) {
	ret sin(x)+x/1
}
~~~

For more information see the SML.md document
