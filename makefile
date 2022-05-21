#	Author: Peyton Anderson

#	COMPILER:
COM=g++

#	COMMON FLAGS:
FLAG= -g -std=c++11

a.out: wordle.cpp
	$(COM) $(FLAG) wordle.cpp