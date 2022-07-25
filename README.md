# Gleipnir

A program to study the Nikolayevsky derivation on Lie algebras with a parameter.

The Nikolayevksy (or pre-Einstein) derivation of a Lie algebra g was defined in 

Yuri Nikolayevsky. *Einstein solvmanifolds and the pre-Einstein derivation*. [Trans. Amer. Math. Soc. 363 (2011), 3935-3958](https://doi.org/10.1090/S0002-9947-2011-05045-2)

It is the unique (up to automorphisms) *semisimple* derivation N such that 

	(*)	tr(ND)=tr D, D in Der(g)
	
The nilradical in Der(g) can be identified with the null space of the trace form,

	n = {X in Der(g) : tr(ND)=0 for all D in Der(g)}

If the Lie algebra does not contain parameters, N and n can be computed explicitly. **Gleipnir** is also able to compute the centralizer of N in n. This is useful in order to compute the space of *all* derivations N verifying (*).

In the presence of parameters, **Gleipnir** is not always capable of producing the Nikolayevsky derivation N and the null space n. In this case, it only computes a space that is guaranteed to contain N+n.

This program has been used in the calculations leading to Proposition 2.7 in

Diego Conti and Federico A. Rossi. *Indefinite nilsolitons and Einstein solvmanifolds*. [https://doi.org/10.1007/s12220-021-00850-7](Journal of Geometric Analysis (2022) 32:88 )

The code is based on joint work with Federico A. Rossi, and partly taken from [DEMONbLAST](https://github.com/diego-conti/DEMONbLAST)

## Requirements

*Gleipnir* requires [cmake](https://cmake.org/) and [Wedge](https://github.com/diego-conti/wedge)

To compile, run

	mkdir build
	cd build
	cmake ..
	cmake --build .

You may need to set the WEDGE_PATH environment variable to point to your installation of Wedge, e.g.

	export WEDGE_PATH=/home/user/wedge

## Usage

To invoke the program on a single Lie algebra without parameters, pass it as an argument, as in 

	./gleipnir 0,0,12,0,24+13,14-23,15-26+2*34

Invoke **Gleipnir** without parameters to run it over all nilpotent Lie algebras of dimension 7, as appearing in 

M.P. Gong. *Classification of nilpotent Lie algebras of dimension 7 (over algebraically closed fields and R)*, Thesis (Ph.D.)--University of Waterloo (Canada), 1998.




