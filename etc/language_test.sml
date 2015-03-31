## SML Test
# This should result in A being set to 7 in the GST, B 15
# And then the function of F to be stored as an AST with the 
# LST of C and A where A is the argument passed into the function
# It then should return what ever the input is plus B

A := 5+2
B := (A+A)+1

F := (A) {
	C := A+B
	ret C
}

# This should return 30
F(15)
