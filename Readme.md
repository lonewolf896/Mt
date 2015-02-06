# Mt [![Build Status](https://travis-ci.org/XAMPP/Mt.svg)](https://travis-ci.org/XAMPP/Mt)
Mt is an environment for interacting with the Simple[Sane] Math Language (SML)

It was built for linear algebra MAT342 at UAT


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
