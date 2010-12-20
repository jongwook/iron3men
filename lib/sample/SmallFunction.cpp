/*
 *  SmallFunction.cpp
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/18/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#include "SmallFunction.h"
#include "Polynomial.h"

const char * SmallFunction::Node::ops[]={" "," "," "," "," "," "," "," ",
	" + "," + "," - "," - "," * "," * "," / "," / "," / "," % "," % "," % ",
	" << "," >> "," >> "," & "," | "," ^ "};

SmallFunction::Node::Node() {
	opcode = -1;
	op1 = NULL;
	op2 = NULL;
}

SmallFunction::Node::Node(char _type) {
	opcode = -1;
	value.type = _type;
	op1 = NULL;
	op2 = NULL;
}

SmallFunction::Node::Node(int _value) {
	opcode = -1;
	value.type = '\0';
	value.value = _value;
	op1 = NULL;
	op2 = NULL;
}

SmallFunction::Node::~Node() {

}

std::string SmallFunction::Node::toString() {
	if(opcode == -1) {
		if(value.type != '\0') {
			return std::string(1,value.type);
		} else {
			return value.toString();
		} 
	}
	return std::string("( ") + op1->toString() + ops[opcode] + op2->toString() + " )";
}


SmallFunction::SmallFunction() {
	length=0;
	root=NULL;
	poly=NULL;
}

SmallFunction::SmallFunction(const std::vector<InstTemplate> &from) {
	length=from.size();
	nodes=new Node*[length];
	poly=NULL;
	
	for(int i=0;i<length;++i) {
		const InstTemplate &inst=from[i];
		
		// create a node for this instruction
		nodes[i]=new Node;
		nodes[i]->opcode = inst.opcode;
		if(inst.operands.size()<2) continue;
		
		// find operands
		const MetaValue &value1 = inst.operands[0];
		const MetaValue &value2 = inst.operands[1];
		
		if(value1.isInternal()) {
			// find the referencing node;
			int ref=(value1.type-'a');
			if(ref>=i || ref<0) {
				std::cerr << "invalid reference : " << ref << std::endl;
				continue;
			}
			nodes[i]->op1=nodes[ref];
		} else if(value1.isVariable()) {
			// create a new node with the variable
			nodes[i]->op1 = new Node(value1.type);
		} else {
			// create a new node with the value
			nodes[i]->op1 = new Node(value1.value);
		}
		
		if(value2.isInternal()) {
			// find the referencing node;
			int ref=(value2.type-'a');
			if(ref>=i || ref<0) {
				std::cerr << "invalid reference : " << ref << std::endl;
				continue;
			}
			nodes[i]->op2=nodes[ref];
		} else if(value2.isVariable()) {
			// create a new node with the variable
			nodes[i]->op2 = new Node(value2.type);
		} else {
			// create a new node with the value
			nodes[i]->op2 = new Node(value2.value);
		}
	}
	root = nodes[length-1];
}

SmallFunction::~SmallFunction() {
	for(int i=0; i<length; i++) {
		delete nodes[i];
	}
	if(poly) {
		delete poly;
	}
}

std::string SmallFunction::toString() {
	return (root)?root->toString():"";
}

bool SmallFunction::operator==(const SmallFunction &other) {
	Polynomial *p1 = poly = (poly)?poly:new Polynomial(*this);
	Polynomial *p2 = (other.poly)?(other.poly):new Polynomial(other);

	return *p1==*p2;
}



