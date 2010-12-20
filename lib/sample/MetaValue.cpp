/*
 *  Value.cpp
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/18/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#include "MetaValue.h"
#include <sstream>

MetaValue::MetaValue() {
}

MetaValue::MetaValue(char _type) {
	type=_type;
}

MetaValue::MetaValue(int _value) {
	type='\0';
	value=_value;
}

std::string MetaValue::toString() {
	std::stringstream ss;
	if(isalpha(type)) {
		ss << type;
	} else {
		ss << value;
	}
	return ss.str();
}

bool MetaValue::operator==(char _type) {
	return type == _type;
}

bool MetaValue::operator==(int _value) {
	return type == '\0' && value == _value;
}

std::istream& operator >>(std::istream &is, MetaValue &obj) {
	is.read((char *)&obj.type,sizeof(obj.type));
	if(!isalpha(obj.type)) {
		is.read((char *)&obj.value,sizeof(obj.value));
	}
	return is;
}

std::ostream& operator <<(std::ostream &os, const MetaValue &obj) {
	os.write((char*)&obj.type,sizeof(obj.type));
	if(!isalpha(obj.type)) {
		os.write((char*)&obj.value,sizeof(obj.value));
	}
	return os;
}
