# Mt [![Build Status](https://travis-ci.org/XAMPP/Mt.svg)](https://travis-ci.org/XAMPP/Mt)
Mt is an environment for interacting with the Simple[Sane] Math Language (SML)

It was built for linear algebra MAT342 at UAT


## Requierd Bits
In order to build Mt, you need a few things, first off is both clang and GCC, we use clang for the debug build, as it provides decent output for errors and such, GCC is used in the release build to it having slightly better native code generation and optimization.

On the clang side, libc++ and libc++abi are needed, other than that what GCC ships with should be fine.

The next thing that is needed would be gperftools, we use the tcmalloc as a malloc replacement and as a wrapper to our object allocation. In addition to that it has built-in heap profiling.

We also use the CPU profiler so thats in there as well.

You can find gperftools over at https://code.google.com/p/gperftools/

doxygen is also needed if you wish to build the docs, but a normal make wont do that anyway so if you just want to build from source and have no interest in documentation then you dont need it.

## Building

In order to build Mt, ensure that you have all of the needed bits installed, then a simple `make` in the Mt directory will make it in debug mode, if you want better optimized code, `make release` is what you want.

To enable the CPU profiler, `make prof`

## Simple[Sane] Math Language (SML)
The language that is used by Mt is called SML, it takes a bit from C style languages in addition to attempting to honer mathematic notation.

SML has one core type `IMtObject` this is the basis for all other items in the language, it is then broken out into the complex types such as the `StaticMatrix` and the `DynamicMatrix` and then all the `INumeric` types.

Everything under `INumeric` consists of the operable types, `double`, `Complex`, `Rational`, and `Integer`

Any `INumeric` type can be mathematically manipulated by any other `INumeric` type. Meaning you can multiply complex and rational numbers together to get a result.


Functions also inherit from `IMtObject` Meaning that just like an `INumeric` They can be passed to any method that takes a `IMtObject`, In this case the function will attempt to be solved prior to the method that is invoking the function, as to resolve to an `INumeric`


### Examples

To perform a basic evaluation

```
1+4
```

To assign the result of an evaluation to a variable

```
A := 1+4
```

To define a function

```
F := (x,y) {
	z = cos(y)*x

	ret z
}

A := F(1,6)*5

```

Just like numerics, functions can be passed into other functions

```
A := (B, C) {
	ret B(C+6)*7
}

B := (C) {
	ret C * cos(-C)
}

C := A(B, 7)

```
