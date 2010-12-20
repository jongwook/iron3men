/*
 *  InstTemplate.h
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/18/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#ifndef __INSTTEMPLATE_H__
#define __INSTTEMPLATE_H__

#include "MetaValue.h"

class InstTemplate {
public:
	int opcode;			// opcode of this instruction
	std::string opcodestr;	// string represenation of the opcode
	std::vector<MetaValue> operands;	
	
	InstTemplate();
	InstTemplate(const std::string &str);
	
	std::string toString();
	
	static int parseOpCode(const std::string &str);
	
	friend std::istream& operator >>(std::istream &is,InstTemplate &obj);
	friend std::ostream& operator <<(std::ostream &os,const InstTemplate &obj);
};

#endif