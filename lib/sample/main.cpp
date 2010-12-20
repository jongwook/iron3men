#include <iostream>

#include "PeepholeMatch.h"
#include "SmallFunction.h"
#include "Polynomial.h"
#include "InstCombination.h"

void print(std::vector<InstTemplate> &list) {
	for(int i=0;i<list.size();++i) {
		std::cout << list[i].toString() << std::endl;
	}
}

int main (int argc, char * const argv[]) {
	std::vector<InstTemplate> temp;
	temp.push_back(InstTemplate("mul A A")); // a = A^2
	temp.push_back(InstTemplate("mul a A")); // b = A^3
	temp.push_back(InstTemplate("mul a B")); // c = A^2*B
	temp.push_back(InstTemplate("mul B B")); // d = B^2
	temp.push_back(InstTemplate("mul d B")); // e = B^3
	temp.push_back(InstTemplate("mul d A")); // f = A*B^2
	temp.push_back(InstTemplate("mul c 3")); // g = 3A^2B
	temp.push_back(InstTemplate("mul f 3")); // h = 3AB^2
	temp.push_back(InstTemplate("add b e")); // i
	temp.push_back(InstTemplate("add g h")); // j
	temp.push_back(InstTemplate("add i j")); // k
	SmallFunction func(temp);
	
	for(InstCombination combi(2, 3); !combi.invalid; combi.next() ) {
		std::vector<InstTemplate> list(combi.list, combi.list+combi.length);
		SmallFunction test(list);
		if(func==test) {
			std::cout << "simpler version : " << std::endl;
			print(list);
			break;
		}
	}
	
	return 0;
}
