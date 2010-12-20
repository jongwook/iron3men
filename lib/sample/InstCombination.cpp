/*
 *  InstCombination.cpp
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/19/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#include "InstCombination.h"

static const char *supported_ops[] = {"add","sub","mul"};
static const int supported_opcodes[] = {8, 10, 12};
static const int reverse_opcode[] = {-1, -1, -1, -1, -1, -1, -1, -1, 0, -1, 1, -1, 2};
static const int n_ops = sizeof(supported_ops)/sizeof(char *);
static const int coef_max = 2;
static const int coef_min = -2;
// A~Z a~z -3~3

InstCombination::InstCombination(int _input, int _length) {
	input = _input;
	length = _length;
	invalid = false;
	
	list = new InstTemplate[length];
	
	// init with first combination
	for(int i=0; i<length; ++i) {
		list[i].opcode = supported_opcodes[0];
		list[i].opcodestr = supported_ops[0];
		list[i].operands.push_back(MetaValue('A'));
		list[i].operands.push_back(MetaValue('A'));
	}
}

InstCombination::~InstCombination() {
	delete [] list;
}

void InstCombination::next() {
	if(invalid) return;
	
	// find the position to start change
	int pos = length;
	int which = -1;	// 0:opcode 1:op1 2:op2
	
	while(pos>0) {
		InstTemplate &inst=list[--pos];
		
		if(inst.operands.size()!=2) {
			invalid = true;
			std::cerr << "currently supports only 2-operand instructions\n";
			return;
		}
		
		if(!(inst.operands[1] == coef_max)) {
			which = 2;
			break;
		}
		
		if(!(inst.operands[0] == coef_max)) {
			which = 1;
			break;
		}
		
		if(reverse_opcode[inst.opcode] < n_ops-1) {
			which = 0;
			break;
		}
	}
	
	if(which == -1) {
		invalid = true;
		return;
	}
	
	// change the value at that position
	int index, value;
	char type;
	switch (which) {
		case 0:
			index=reverse_opcode[list[pos].opcode]+1;
			list[pos].opcode = supported_opcodes[index];
			list[pos].opcodestr = supported_ops[index];
			break;
		case 1:
			type = list[pos].operands[0].type;
			value = list[pos].operands[0].value;
			if(type >= 'A' && type <='Z') {
				type++;
				if(type-'A' == input) {
					if(pos==0) {
						list[pos].operands[0] = MetaValue(coef_min);
					} else {
						list[pos].operands[0] = MetaValue('a');
					}
				} else {
					list[pos].operands[0] = MetaValue(type);
				}
			} else if(type >= 'a' && type <= 'z') {
				type++;
				if(type-'a' == pos) {
					list[pos].operands[0] = MetaValue(coef_min);
				} else {
					list[pos].operands[0] = MetaValue(type);
				}
			} else if(type=='\0') {
				value++;
				list[pos].operands[0] = MetaValue(value);
			}
			break;
		case 2:
			type = list[pos].operands[1].type;
			value = list[pos].operands[1].value;
			if(type >= 'A' && type <='Z') {
				type++;
				if(type-'A' == input) {
					if(pos==0) {
						list[pos].operands[1] = MetaValue(coef_min);
					} else {
						list[pos].operands[1] = MetaValue('a');
					}
				} else {
					list[pos].operands[1] = MetaValue(type);
				}
			} else if(type >= 'a' && type <= 'z') {
				type++;
				if(type-'a' == pos) {
					list[pos].operands[1] = MetaValue(coef_min);
				} else {
					list[pos].operands[1] = MetaValue(type);
				}
			} else if(type=='\0') {
				value++;
				list[pos].operands[1] = MetaValue(value);
			}
			break;
	}
	
	// reset all values on the right 
	MetaValue A('A');
	if(which<1) {
		list[pos].operands[0] = A;
	}
	if(which<2) {
		list[pos].operands[1] = A;
	}	
	
	for(int i=pos+1; i<length; ++i) {
		list[i].opcode = supported_opcodes[0];
		list[i].opcodestr = supported_ops[0];
		list[i].operands[0] = A;
		list[i].operands[1] = A;
	}
}


