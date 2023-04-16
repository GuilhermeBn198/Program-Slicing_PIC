all: 
	frama-c -slice-return="printf" -print ./tests/test3.c