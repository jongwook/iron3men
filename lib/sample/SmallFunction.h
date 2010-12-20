/*
 *  SmallFunction.h
 *  This function represents a function composed of some LLVM IRs.
 *
 *  Created by Jong Wook Kim on 12/18/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#ifndef __SMALLFUNCTION_H__
#define __SMALLFUNCTION_H__

#include "PeepholeMatch.h"
#include <set>
#include <sstream>

class Polynomial;

class SmallFunction {
public:
	class Node {
	public:
		static const char *ops[];
		int opcode;
		
		MetaValue value;		
		Node *op1;
		Node *op2;	// currently support only two-operand instructions.
		
		Node();
		Node(char _type);		
		Node(int _value);		
		virtual ~Node();
		
		std::string toString();
	};
	
	int length;
	Node **nodes;
	Node *root;
	std::set<char> inputs;
	std::string type;
	Polynomial *poly;
	
	SmallFunction();
	SmallFunction(const std::vector<InstTemplate> &match);
	virtual ~SmallFunction();
	
	std::string toString();
	
	bool operator==(const SmallFunction &other);
};

#endif