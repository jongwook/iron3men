/*
 *  InstCombination.h
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/19/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#ifndef __INSTCOMBINATION_H__
#define __INSTCOMBINATION_H__

#include "InstTemplate.h"

class InstCombination {
public:
	InstTemplate *list;
	bool invalid;
	int input;
	int length;
	
	InstCombination(int _input, int _length);
	virtual ~InstCombination();
	
	void next();
};

#endif