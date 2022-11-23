#include <string>
#include "Linkedlist.h"


class HashTable{			///use template for this 
	private:
		int const static TABLE_SIZE = 1000;
		Linkedlist *Table = new Linkedlist[TABLE_SIZE];
		unsigned long  DJB2hash(string);
		string tableInfo();
	public : 
		void insert(string);
		void remove(string);
		bool search(string);
		void saveTable(string);
		void loadTable(string);
		HashTable(){};
};

