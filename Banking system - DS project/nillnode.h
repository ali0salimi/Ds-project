#include <iostream>
#include "RBtreeNode.h"

using namespace std;

class nillnode : public RBtreeNode{
	public :
		nillnode(){
			is_black = true;
		}
};

