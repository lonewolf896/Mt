# Mt
Mt is an environment for interacting with the Simple[Sane] Math Language (SML)

It was built for linear algebra MAT342 at UAT


## Simple[Sane] Math Language (SML)
The language that is used by Mt is called SML, it takes a bit from C style languages in addition to attempting to honer mathematic notation.':='

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
