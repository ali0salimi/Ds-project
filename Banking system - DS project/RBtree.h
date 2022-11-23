#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>	
#include "nillnode.h"

class RBtree{
	public: 
		void rotateRight(RBtreeNode *);
		void rotateLeft(RBtreeNode *);
		void replaceParentChild(RBtreeNode * ,RBtreeNode *,RBtreeNode *);
		void fixInsert(RBtreeNode * );
		void fixDelete(RBtreeNode *);
		void handleRedSibling(RBtreeNode *,RBtreeNode *);
		void handleBlackSiblingWithAtLeastOneRedChild(RBtreeNode * , RBtreeNode *);
		RBtreeNode * findInorderSuccessor(RBtreeNode *);
		RBtreeNode * deleteRBtreeNodewithOneOrZeroChild(RBtreeNode *);
		RBtreeNode * getUncle(RBtreeNode *);
		RBtreeNode * getSibling(RBtreeNode *);
		string nodeInfoToSave(RBtreeNode *);
		void saveTreeInorder(RBtreeNode *);
		void printTree(string,RBtreeNode*,bool);
		void loadTree();
		RBtree(){};
	public :
		bool isBlack(RBtreeNode *);
		RBtreeNode *root = NULL;
		RBtreeNode * search(int);
		Customer* retrieveUser();
		void insert(Customer);
		void remove(int );
		void saveTree(string);
		void loadTree(string);
		void printTree();
		

};

