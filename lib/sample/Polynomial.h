/*
 *  Polynomial.h
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/19/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

#include <set>
#include <vector>

#include "SmallFunction.h"

class Polynomial {
public:
	class Term {
	public:
		int coef;
		std::vector<char> vars;
		
		bool operator<(const Term &other) const;
		bool operator==(const Term &other) const;
	};
	std::vector<Term *> terms;
	bool invalid;
	
	Polynomial();
	Polynomial(const SmallFunction::Node *node);
	Polynomial(const SmallFunction &func);
	virtual ~Polynomial();

	void init(const SmallFunction::Node *node);
	void initWithAddition(const Polynomial &one, const Polynomial &other);
	void initWithProduct(const Polynomial &one, const Polynomial &other);
	
	Polynomial operator+(const Polynomial &other);
	Polynomial operator*(const Polynomial &other);
	Polynomial& operator*=(const int factor);
	bool operator==(const Polynomial &other);
};

#endif