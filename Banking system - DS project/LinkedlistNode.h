#include <cstddef>
#include <string>

using namespace std;

class LinkedlistNode{
	public : 
		string val;
		LinkedlistNode *next = NULL;
		LinkedlistNode(string _val){
			val = _val;
		}
};

