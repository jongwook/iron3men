/*
 *  PeepholeMatch.cpp
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/16/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#include "PeepholeMatch.h"

#include <iterator>
#include <sstream>
#include <algorithm>

PeepholeMatch::PeepholeMatch() {
	
}

PeepholeMatch::PeepholeMatch(std::vector<InstTemplate> from, std::vector<InstTemplate> to) {
	
}


std::istream& operator >>(std::istream &is,PeepholeMatch &obj)
{
	int from;
	is.read((char *)&from, sizeof(from));
	obj.from.clear();
	for(int i=0; i<from; i++) {
		InstTemplate inst;
		is >> inst;
	}
	int to;
	is.read((char *)&to, sizeof(to));
	obj.to.clear();
	for(int i=0; i<to; i++) {
		InstTemplate inst;
		is >> inst;
	}
	
	return is;
}

std::ostream& operator <<(std::ostream &os,const PeepholeMatch &obj)
{
	int from = obj.from.size();
	os.write((char *)&from, sizeof(from));
	for(std::vector<InstTemplate>::const_iterator it=obj.from.begin(); it!=obj.from.end(); ++it) {
		os << *it;
	}
	int to = obj.to.size();
	os.write((char *)&to, sizeof(to));
	for(std::vector<InstTemplate>::const_iterator it=obj.to.begin(); it!=obj.to.end(); ++it) {
		os << *it;
	}
	return os;
}
