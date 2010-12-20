/*
 *  Value.h
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/18/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#ifndef __METAVALUE_H__
#define __METAVALUE_H__

#include <vector>
#include <iostream>


class MetaValue {
public:
	char type;
	int value;
	
	MetaValue();
	MetaValue(char type);
	MetaValue(int value);
	std::string toString();
	
	bool isVariable() const { return (type >= 'A' && type <= 'Z'); }
	bool isInternal() const { return (type >= 'a' && type <= 'z'); }
	bool isLiteral() const { return !isVariable() && !isInternal(); }
	
	bool operator==(char _type);
	bool operator==(int _value);
	
	friend std::istream& operator >>(std::istream &is, MetaValue &obj);
	friend std::ostream& operator <<(std::ostream &os, const MetaValue &obj);
};

#endif