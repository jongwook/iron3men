/*
 *  PeepholeMatch.h
 *  CPP
 *
 *  Created by Jong Wook Kim on 12/16/10.
 *  Copyright 2010 jongwook. All rights reserved.
 *
 */

#ifndef __PEEPHOLEMATCH_H__
#define __PEEPHOLEMATCH_H__

#include "InstTemplate.h"

class PeepholeMatch {
public:	
	std::vector<InstTemplate> from;
	std::vector<InstTemplate> to;
	
	PeepholeMatch();
	PeepholeMatch(std::vector<InstTemplate> from, std::vector<InstTemplate> to);
				  
	
	friend std::istream& operator >>(std::istream &is,PeepholeMatch &obj);
	friend std::ostream& operator <<(std::ostream &os,const PeepholeMatch &obj);
};
	
#endif /* __PEEPHOLEMATCH_H__ */