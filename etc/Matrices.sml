#############################################################
#															#
#	Mt matrices op test file - Simple Math Language (SML)	#
#															#
#############################################################

## Matrix definition

# Creates an empty matrix of size X,Y filled with 0
M := [3][3]

# Defines the following 3x3 matrix
#	1	2	3
#	3 	2	1
#	2	3	1
M2 :=  <1,2,3><3,2,1><2,3,1>

## Matrix access

M3 := <5,3,7,2><6,3,7,3>

# Adds 4 to the 0th row, all elements
M3[0][] += 4
# Adds 3 to the 4th column for each row
M3[][3] += 3

## Gaussian Elimination

#  uses Gaussian Elimination to  solve the given MxN matrix
M4 := smge(M2)

# Does the same as above but lists out the row operations
smge(M2, true)
