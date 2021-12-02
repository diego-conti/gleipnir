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

#ifndef CLASSIFICATION_H
#define CLASSIFICATION_H

#include <vector>
#include <wedge/liegroup.h>


using namespace Wedge;
using std::string;

/** Represents an immutable list of mathematical objects corresponding to a classification */
template <typename Classified> class Classification {
	vector<unique_ptr<Classified>> elements;
	vector<string> names;
protected:
/** Add an entry to the classification

 @param element The entry to be added. Ownership is transferred to this container
*/
	void add (unique_ptr<Classified>&& element) {elements.emplace_back(move(element)); names.push_back(ToString(elements.size()));}
/** Add an entry to the classification

 @param element The entry to be added. Ownership is transferred to this container
 @param name A name for this entry
*/
	void add (unique_ptr<Classified>&& element, string name) {elements.push_back(move(element)); names.push_back(name);}
	Classification() {}
public:
	template<typename T> Classification(std::initializer_list<T> args_for_elems) {
		for (auto& args: args_for_elems)
			elements.emplace_back(args);
	}

	const Classified& entry (OneBased index) {return *elements[index-1];}
	const string& name (OneBased index) {return names[index-1];}
	auto begin() const {return elements.begin();}
	auto end() const {return elements.end();}
};

/* Nonnice nilpotent Lie groups of dimension 7, as per
 	Diego Conti, Federico Rossi. Construction of nice nilpotent Lie groups. Journal of Algebra, (2019) 525:311-340. doi:10.1016/j.jalgebra.2019.01.020 [Table 2]
 */
class NonniceNilpotentLieGroups7 : public Classification<LieGroup> {
	void add(const char* structure_constants) {
		Classification<LieGroup>::add(make_unique<AbstractLieGroup<false>>	(structure_constants));
	}
	template <typename... T>
	void add(const char* structure_constants, const T&... names) {
		Classification<LieGroup>::add(make_unique<AbstractLieGroup<true>>	(structure_constants, names...));
	}

public:
	NonniceNilpotentLieGroups7() {
		//reducible
		add("0,0,12,13,0,14+23+25,0");


		add("0,0,12,13,14,15+23,16+23+24");
		add("0,0,12,13,14,15+23,16+24+25-34");		
		add("0,0,12,13,14+23,15+24,16+23+25");	
		add("0,0,12,13,14+23,15+24,-16+23-25");	//123457H1

		add("0,0,12,13,14+23,15+24,23");
		add("0,0,12,13,14+23,25-34,23");
		add("0,0,12,13,14,23,16+25+24-34");
		add("0,0,12,13,14,23,15+25+26-34");
		add("0,0,12,13,23,15+24,14+16+25+34");
		add("0,0,12,13,23,15+24,14+16-25+34");
		add("0,0,12,13,23,15+24,14+16+34");
		add("0,0,12,13,23,15+24,14+16+[lambda]*25+26+34-35",N.lambda);

		add("0,0,12,13,23,-14-25,16+25-35");
		add("0,0,12,13,23,-14-25,15+16+24+[lambda]*25-35",N.lambda);
		add("0,0,12,13,14,0,15+23+26");
		add("0,0,12,13,14+23,0,15+24+26");
		add("0,0,12,13,0,14+25,35+16");
		add("0,0,12,13,0,14+23+25,16+24+35");
		add("0,0,12,13,0,14+23+25,26-34");
		add("0,0,12,13,0,14+23+25,15+26-34");
		add("0,0,0,12,14+23,15-34,16+23-35");
		add("0,0,12,13,0,25+23,14");
		add("0,0,12,13,0,14+23,23+25");
		add("0,0,12,0,13,23+24,15+16+25+[lambda]*26+34",N.lambda);
		add("0,0,12,13,0,14+23+25,0");
		add("0,0,12,13,0,14+25+23,15");
		add("0,0,0,12,14+23,23,15-34");
		add("0,0,12,0,23,14,16+26+25-34");
		add("0,0,12,0,24+13,14,15+23+1/2*26+1/2*34");
		add("0,0,12,0,24+13,14,15+[lambda]*23+34+46",N.lambda);
		add("0,0,0,12,13,14+24-35,25+34");
		add("0,0,0,12,13,15+35,25+34");
		add("0,0,0,12,23,-13,15+16+26-2*34");
		add("0,0,0,12,23,-13,[-lambda]*16+[lambda]*25+2*26-2*34",N.lambda);
		add("0,0,0,12,14+23,0,15-34+36");
		add("0,0,0,12,14+23,0,15-34+24+36");
		add("0,0,12,0,0,13+14,15+23");
		add("0,0,12,0,0,13+14+25,15+23");
	}
};


#endif
