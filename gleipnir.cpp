/*  Copyright (C) 2021 by Diego Conti, diego.conti@unimib.it      
                                                                     
    This file is part of Gleipnir
	                                                                     
    Gleipnir is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Gleipnir is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Gleipnir.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "derivations.h"
#include "horizontal.h"
#include "classification.h"


/** Return the linear equations corresponding to Tr(ND)=D for all D in some subspace of gl
	@param N A generic element of gl, depending on parameters
	@param subspace A subspace of gl
	@param gl The Lie algebra of the general Lie group	
	@return The linear equations corresponding to Tr(ND)=D for all D in subspace
*/
	
exvector nikolayevsky_equations(ex N, const exvector& subspace, const GL& gl) {
	set<ex,ex_is_less> eqns;
	auto N_as_matrix=gl.glToMatrix(N);
	for (auto e: subspace) {
		auto M=gl.glToMatrix(e);
		eqns.insert(N_as_matrix.mul(M).sub(M).trace());
	}
	return {eqns.begin(),eqns.end()};
}

/** An affine space N+W in gl(n,R) */
struct AffineSpaceInGl {
	ex N;
	VectorSpace<DifferentialForm> W;
};

/** Return the affine space N+W of derivations satisfying tr(ND)=tr(D) for all derivations D
	@param G a Lie group of dimension n without parameters
	@param gl The Lie algebra of GL(n,R).
	@return an AffineSpaceInGl object representing the affine space N+W
	
	The computation is performed by computing the space of derivations exactly
*/
AffineSpaceInGl nikolayevsky_like_derivations(const LieGroup& G, const GL& gl) {
	auto der=derivations(G,gl);
	auto eqns=nikolayevsky_equations(der.GenericElement(),der.e(),gl);	
	exvector solutions;
	AffineSpaceInGl result;
	der.GetSolutions(solutions,eqns.begin(),eqns.end(),&result.N);
	result.W=VectorSpace<DifferentialForm>{solutions};
	return result;
}

/** Return an affine space N+W that is guaranteed to contain the Nikolayevsky derivation
	@param G a Lie group of dimension n, with or without parameters
	@param gl The Lie algebra of GL(n,R).
	@return an AffineSpaceInGl object representing the affine space N+W
	
	The computation is performed like in the case without parameters (@sa nikolayevsky_like_derivations), except that the space of derivations cannot be determined exactly, but only as a VectorSpaceBetween object. This implies that the resulting space N+W may contain elements that are not derivations, or do not satisfy tr(ND)=tr(D) for all derivations.
*/
AffineSpaceInGl nikolayevsky_like_derivations_parametric(const LieGroup& G, const GL& gl) {
	auto derivations=derivations_parametric<StructureConstant>(G,gl);
	VectorSpace<DifferentialForm> der{derivations.basis_of_larger_space};
	auto eqns=nikolayevsky_equations(der.GenericElement(),derivations.basis_of_smaller_space,gl);
	exvector solutions;
	AffineSpaceInGl result;
	der.GetSolutions(solutions,eqns.begin(),eqns.end(),&result.N);
	result.W=VectorSpace<DifferentialForm>{solutions};
	return result;
}

/** Return the centralizer of an element N of gl inside a subspace of gl
	@param N an element of gl
	@param W a subspace of gl
	@param gl The Lie algebra of GL(n,R)
	@return The space of elements of W that commute with N
*/

auto centralizer(ex N, const VectorSpace<DifferentialForm>& W, const GL& gl) {
	auto m=gl.glToMatrix(N);
	auto w=gl.glToMatrix(W.GenericElement());
	lst eqns;
	auto commutator=gl.MatrixTo_gl(ex_to<matrix>((m*w-w*m).evalm()));
	GetCoefficients<DifferentialForm>(eqns,commutator);
	return W.SubspaceFromEquations(eqns.begin(),eqns.end());
}

/** Return the set of linear equations that a matrix should satisfy in order to define a derivation
	@param G a Lie group of dimension n
	@param gl The Lie algebra of GL(n,R)
	@param matrix a square matrix of order n
	@result the equations that must be satisfied for the matrix to define a derivation of the Lie algebra of G
*/	
auto derivation_when(const LieGroup& G, const GL& gl, ex matrix) {
	auto brackets=Xbrackets(G,GLRepresentation<VectorField>(&gl,G.e()),matrix);
	set<ex,ex_is_less> eqns;
	GetCoefficients<VectorField>(eqns,brackets);
	eqns.erase(0);
	return eqns;
}


void print_derivations(const LieGroup& G, const GL& gl) {
	VectorSpace<DifferentialForm> der{derivations_parametric<StructureConstant>(G,gl).basis_of_larger_space};
	auto gen_der=gl.glToMatrix(der.GenericElement());
	cout<<dflt;
	cout<<"generic derivation "<<gen_der<<endl;
	cout<<"derivation when the following are zero: "<<derivation_when(G,gl,der.GenericElement())<<endl;	
	cout<<latex;
}

class Nikolayevsky {
	matrix N;
	set<ex,ex_is_less> derivation_when;
	bool is_diagonal() const {
		for (int i=0;i<N.cols();++i)
		for (int j=i+1;j<N.cols();++j)	
			if (!N(i,j).is_zero() || !N(j,i).is_zero()) return false;
		return true;	
	}
	exvector diagonal() const {
			exvector diagonal;		
			for (int i=0;i<N.cols();++i)
				diagonal.push_back(N(i,i));
			return diagonal;
	}	
public:
	Nikolayevsky(const LieGroup& G, const GL& gl, ex nik) {
		N=gl.glToMatrix(nik);
		derivation_when=::derivation_when(G,gl,nik);	
	}
	string to_string() const {
			stringstream result;
			if (!derivation_when.empty()) 
				result<<"cannot compute; Nikolayevsky derivation takes the form "<<N<<", only derivation when the following are zero: "<<derivation_when;			
			else if (is_diagonal()) 
				result<<horizontal(diagonal());
			else 
				result<<"if diagonalizable, "<<N;				
			return result.str() ;
	}
};


void study_group(const LieGroup& G) {
	cout<<latex<<endl;
	GL gl(G.Dimension());
	auto nik_like_derivations=nikolayevsky_like_derivations_parametric(G,gl);
	cout<<"Lie algebra:"<<horizontal(G.StructureConstants())<<endl;
	cout<<"Nikolayevsky derivation: "<<Nikolayevsky(G,gl,nik_like_derivations.N).to_string()<<endl;	
	auto centralizer_of_nik=centralizer(nik_like_derivations.N,nik_like_derivations.W,gl);	//compute a space which contains the centralizer of the Nikolayevsky derivation inside the null space of the trace form
	print_derivations(G,gl);
	if (nik_like_derivations.N.is_zero()) {cout<<"Nikolayevsky derivation is zero"<<endl; return;}	
	cout<<"centralizer contained in space of dimension "<<centralizer_of_nik.Dimension()<<endl;
	if (!centralizer_of_nik.Dimension()) return;
	auto generic_element=gl.glToMatrix(centralizer_of_nik.GenericElement());
	cout<<"generic element "<<generic_element<<endl;
	auto conditions_for_element_of_centralizer_to_be_a_derivation=derivation_when(G,gl,centralizer_of_nik.GenericElement());
	if (!conditions_for_element_of_centralizer_to_be_a_derivation.empty())
		cout<<"derivation when the following are zero: "<<conditions_for_element_of_centralizer_to_be_a_derivation<<endl;
}


int main() {
	for (auto& G : NonniceNilpotentLieGroups7()) 
		study_group(*G);	
}
