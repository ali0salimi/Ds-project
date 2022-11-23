#include "customer.h"

class RBtreeNode {
	public : 
		Customer data;
		RBtreeNode *left=NULL;
		RBtreeNode *right=NULL;
		RBtreeNode *parent=NULL;
		bool  is_black = false;
		RBtreeNode(Customer DATA){
			data = DATA;
		}
		RBtreeNode(){};
};
