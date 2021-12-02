# Gleipnir

A program to compute the Nikolayevsky or pre-Einstein derivation on Lie algebras with a parameter, as defined in 

Yuri Nikolayevsky. *Einstein solvmanifolds and the pre-Einstein derivation*. [Trans. Amer. Math. Soc. 363 (2011), 3935-3958](https://doi.org/10.1090/S0002-9947-2011-05045-2)

The Nikolayevsky derivation of a Lie algebra g is the unique (up to automorphisms) *semisimple* derivation N such that 

	(*)	tr(ND)=tr D, D in Der(g)
	
The nilradical in Der(g) can be identified with the null space of the trace form,

	n = {X in Der(g) : tr(ND)=0 for all D in Der(g)}

**Gleipnir** is also able to compute the centralizer of N in n. This is useful in order to compute the space of *all* derivations N verifying (*).

This program has been used in the calculations leading to Proposition 2.7 in

Diego Conti and Federico A. Rossi. *Indefinite nilsolitons and Einstein solvmanifolds*. [arXiv:2105.09209](https://www.arxiv.org/abs/2105.09209)

The code is based on joint work with Federico A. Rossi, and partly taken from [DEMONbLAST](https://github.com/diego-conti/DEMONbLAST)

## Requirements

*Gleipnir* requires a modern C++ compiler, [CLN](https://www.ginac.de/CLN/), [gmp](https://gmplib.org/) and [Wedge](https://github.com/diego-conti/wedge)

To compile, run

	make

or possibly
	
	CPLUS_INCLUDE_PATH=/path/to/wedge make

