/*
 *  InstTemplate.cpp
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/18/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#include "InstTemplate.h"
#include <sstream>
#include <iterator>
#include <algorithm>

/*
static const char *opcodes[]={" "," "," "," "," "," "," "," ",
	"add","fadd","sub","fsub","mul","fmul","udiv","sdiv","fdiv","urem","srem","frem",
	"shl","lshr","ashr","and","or","xor"};
*/

InstTemplate::InstTemplate() {
	
}

InstTemplate::InstTemplate(const std::string &str) {
	std::stringstream ss(str);
	std::istream_iterator<std::string> it(ss), end;
	std::vector<std::string> tokens(it,end);
	
	opcode=-1;
	
	for(std::vector<std::string>::iterator token=tokens.begin(); token!=tokens.end(); ++token) {
		if(opcode==-1) {
			opcode=InstTemplate::parseOpCode(*token);
			if(opcode==-1) {
				std::cerr << "unknown opcode\n";
				return;
			}
			opcodestr = *token;
			
			continue;
		}
		
		if(isalpha(token->at(0))) {
			operands.push_back(MetaValue(token->at(0)));
		} else {
			operands.push_back(MetaValue(atoi(token->c_str())));
		}
	}
}

std::string InstTemplate::toString() {
	std::stringstream ss;
	ss << opcodestr;
	for(std::vector<MetaValue>::iterator it=operands.begin(); it!=operands.end(); ++it) {
		ss << " ";
		if (it->type == '\0') {
			ss << it->value;
		} else {
			ss << it->type;
		}
	}
	return ss.str();
}

int InstTemplate::parseOpCode(const std::string &str) {
	std::string copy(str);
	transform(copy.begin(), copy.end(), copy.begin(), (int(*)(int))tolower);
	if(copy == "add")	return 8;
	if(copy == "fadd")	return 9;
	if(copy == "sub")	return 10;
	if(copy == "fsub")	return 11;
	if(copy == "mul")	return 12;
	if(copy == "fmul")	return 13;
	if(copy == "udiv")	return 14;
	if(copy == "sdiv")	return 15;
	if(copy == "fdiv")	return 16;
	if(copy == "urem")	return 17;
	if(copy == "srem")	return 18;
	if(copy == "frem")	return 19;
	if(copy == "shl")	return 20;
	if(copy == "lshr")	return 21;
	if(copy == "ashr")	return 22;
	if(copy == "and")	return 23;
	if(copy == "or")	return 24;
	if(copy == "xor")	return 25;
	return -1;
	
}

std::istream& operator >>(std::istream &is,InstTemplate &obj)
{
	is.read((char *)&obj.opcode, sizeof(obj.opcode));
	int len;
	is.read((char *)&len, sizeof(len));
	obj.operands.clear();
	for(int i=0; i<len; i++) {
		MetaValue operand;
		is.read((char *)&operand, sizeof(operand));
		obj.operands.push_back(operand);
	}
	return is;
}

std::ostream& operator <<(std::ostream &os,const InstTemplate &obj)
{
	int len = obj.operands.size();
	os.write((char *)&obj.opcode, sizeof(obj.opcode));
	os.write((char *)&len, sizeof(len));
	for(std::vector<MetaValue>::const_iterator it=obj.operands.begin(); it!=obj.operands.end(); ++it) {
		os << *it;
	}
	
	return os;
}
