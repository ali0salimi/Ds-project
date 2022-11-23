#include <string>
#include "LinkedlistNode.h"

using namespace std;


class Linkedlist{
	public : 
		LinkedlistNode *head = NULL;		
		int size=0; 
		void add(string);
		void remove(string);
		bool found(string);
		string content();
		Linkedlist(){};
	};
