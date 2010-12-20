/*
 *  Polynomial.cpp
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/19/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#include "Polynomial.h"
#include <algorithm>
#include <stack>

static void print(Polynomial &poly) {
	for(std::vector<Polynomial::Term *>::iterator term=poly.terms.begin(); term != poly.terms.end(); ++term) {
		if(term!=poly.terms.begin()) std::cout << " + ";
		if((*term)->coef != 1) std::cout << (*term)->coef;
		for(std::vector<char>::iterator var=(*term)->vars.begin(); var != (*term)->vars.end(); ++var) {
			std::cout << *var;
		}
	}
	std::cout << std::endl;
}

struct CompareTerms : public std::binary_function<Polynomial::Term*,Polynomial::Term*,bool> {
	inline bool operator()(const Polynomial::Term* a, const Polynomial::Term* b) {
		return *a<*b;
	}
};


bool Polynomial::Term::operator<(const Term &other) const {
	for(std::vector<char>::const_iterator it1=vars.begin(), it2=other.vars.begin(); it1!=vars.end() && it2!=other.vars.end() ;++it1, ++it2) {
		if(*it1 < *it2) return true;
		if(*it1 > *it2) return false;
	}
	return false;
}

bool Polynomial::Term::operator==(const Term &other) const {
	return coef==other.coef && vars==other.vars;
}

Polynomial::Polynomial() {
	invalid = false;
}

Polynomial::Polynomial(const SmallFunction::Node *node) {
	invalid = false;
	init(node);
}

Polynomial::Polynomial(const SmallFunction &func) {
	invalid = false;
	init(func.root);
}

Polynomial::~Polynomial() {
	while(!terms.empty()) {
		delete terms.back();
		terms.pop_back();
	}
}

void Polynomial::init(const SmallFunction::Node *node) {
	if(node->opcode != -1) {
		Polynomial one(node->op1);
		Polynomial other(node->op2);
		if(one.invalid || other.invalid) {
			invalid=true;
			return;
		}
		switch (node->opcode) {
			case 8:	// add
				initWithAddition(one, other);
				break;
			case 10: // sub
				other *= -1;
				initWithAddition(one, other);
				break;
			case 12: // mul
				initWithProduct(one, other);
				break;
			case 20: // shl
				if(other.terms.size()==1 && other.terms[0]->vars.size()==0) {
					// const shift left : convert to multiply
					int factor = 1 << other.terms[0]->coef;
					one *= factor;
					initWithAddition(one, Polynomial());
				} else {
					invalid = true;
				}
				break;
			default:
				invalid = true;
		}
	} else {
		// single term
		Term *term=new Term;
		if(node->value.type != '\0') {
			term->coef = 1;
			term->vars.push_back(node->value.type);
		} else {
			term->coef = node->value.value;
		}
		terms.push_back(term);
	}
}

void Polynomial::initWithAddition(const Polynomial &one, const Polynomial &other) {
	// add terms from this polynomial
	for(std::vector<Term *>::const_iterator it=one.terms.begin(); it!=one.terms.end(); ++it) {
		terms.push_back(new Term(**it));
	}
	
	// add terms from other polynomial
	for(std::vector<Term *>::const_iterator it=other.terms.begin(); it!=other.terms.end(); ++it) {
		terms.push_back(new Term(**it));
	}
	
	// simplify
	sort(terms.begin(), terms.end(), CompareTerms());
	
	// merge terms with same vars
	for(std::vector<Term *>::iterator it=terms.begin(); it!=terms.end();) {
		Term *current = *it++;
		while(it != terms.end()) {
			if(it == terms.end()) break;
			Term *next = *it;
			if(current->vars != next->vars) break;
			current->coef += next->coef;
			it=terms.erase(it);
		};
	}
		
}

void Polynomial::initWithProduct(const Polynomial &one, const Polynomial &other) {
	// add terms from this polynomial
	for(std::vector<Term *>::const_iterator it1=one.terms.begin(); it1!=one.terms.end(); ++it1) {
		for(std::vector<Term *>::const_iterator it2=other.terms.begin(); it2!=other.terms.end(); ++it2) {
			Term *term=new Term;
			term->vars.insert(term->vars.end(),(*it1)->vars.begin(),(*it1)->vars.end());
			term->vars.insert(term->vars.end(),(*it2)->vars.begin(),(*it2)->vars.end());
			sort(term->vars.begin(), term->vars.end());
			term->coef = (*it1)->coef * (*it2)->coef;
			terms.push_back(term);
		}
	}
	
	// simplify
	sort(terms.begin(), terms.end(), CompareTerms());
	
	// merge terms with same vars
	for(std::vector<Term *>::iterator it=terms.begin(); it!=terms.end();) {
		Term *current = *it++;
		while(it != terms.end()) {
			if(it==terms.end()) break;
			Term *next = *it;
			if(current->vars != next->vars) break;
			current->coef += next->coef;
			it=terms.erase(it);
		};
	}
}

Polynomial Polynomial::operator+(const Polynomial &other) {
	Polynomial result;
	result.initWithAddition(*this,other);
	
	return result;
}

Polynomial Polynomial::operator*(const Polynomial &other) {
	Polynomial result;
	
	result.initWithProduct(*this,other);
	
	return result;
}

Polynomial& Polynomial::operator*=(const int factor) {
	for(std::vector<Term *>::iterator it=terms.begin(); it!=terms.end(); ++it) {
		(*it)->coef *= factor;
	}
	
	return *this;
}

bool Polynomial::operator==(const Polynomial &other) {
	if(invalid || other.invalid) return false;
	if(terms.size()!=other.terms.size()) return false;
	for(std::vector<Term *>::const_iterator it1=terms.begin(), it2=other.terms.begin(); it1!=terms.end() && it2!=other.terms.end(); ++it1, ++it2) {
		if(!(**it1 == **it2)) return false;
	}
	return true;
}
