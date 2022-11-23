#include "RBtree.h"


ofstream fout;
ifstream fin;

using namespace std;

RBtreeNode * RBtree::search(int id){
	RBtreeNode *node = root;
	while (node!=NULL){
		if (node->data.id == id){
			return node;
		}
		else if(root->data.id < id){
			node = node->right;
		}
		else{
			node = node->left;
		}
	}
	return NULL;
}

void RBtree::insert(Customer customer){
	RBtreeNode *curr = root;
	RBtreeNode *parent = NULL;
	while (curr!=NULL){
		parent = curr;
		if(customer.id < curr->data.id){
			curr = curr->left;
		}
		else{
			curr = curr->right;
		}
	}
	RBtreeNode  * newRBtreeNode = new RBtreeNode(customer);
	if(parent == NULL){
		root = newRBtreeNode;
	}
	else if(customer.id < parent->data.id){
		parent->left = newRBtreeNode;
	}
	else{
		parent->right = newRBtreeNode;;
	}
	newRBtreeNode->parent = parent;
	fixInsert(newRBtreeNode);
}

void RBtree::remove(int id){
	RBtreeNode *node = root;
	while (node!=NULL and node->data.id != id){
		if(node->data.id < id){
			node = node->right;
		}
		else{
			node = node->left;
		}
	}
	if (node==NULL){
		return;	
	}
	
	RBtreeNode *substituteRBtreeNode;
	bool deletedRBtreeNodeColor;
	
	if(node->left == NULL || node->right == NULL){
		substituteRBtreeNode = deleteRBtreeNodewithOneOrZeroChild(node);
		deletedRBtreeNodeColor = node->is_black;
	}
	else{
		RBtreeNode *inorderSuccessor = findInorderSuccessor(node->right);
		node->data = inorderSuccessor->data;
		substituteRBtreeNode = deleteRBtreeNodewithOneOrZeroChild(inorderSuccessor);
		deletedRBtreeNodeColor = inorderSuccessor->is_black;
	}
	if (deletedRBtreeNodeColor){
		fixDelete(substituteRBtreeNode);
		if(typeid(substituteRBtreeNode) == typeid(nillnode)){
			replaceParentChild(substituteRBtreeNode->parent,substituteRBtreeNode,NULL);
		}
	}
	
	

}


void RBtree::rotateRight(RBtreeNode *node){
	RBtreeNode *parent = node->parent;
	RBtreeNode *leftchild = node->left;

	node->left = leftchild->right;
	if(leftchild->right != NULL){
		leftchild->right->parent = node;
	}

	leftchild->right = node;
	node->parent = leftchild;
	replaceParentChild(parent,node,leftchild);
}

void RBtree::rotateLeft(RBtreeNode *node){
	RBtreeNode *parent = node->parent;
	RBtreeNode *rightchild = node->right;

	node->right = rightchild->left;
	if(rightchild->left!=NULL){
		rightchild->left->parent = node;
	}

	rightchild->left = node;
	node->parent = rightchild;

	replaceParentChild(parent,node,rightchild);
}

void RBtree::replaceParentChild(RBtreeNode *parent,RBtreeNode *oldChild,RBtreeNode *newChild){

	if(parent == NULL){
		root = newChild;
	}
	else if(parent->left == oldChild){
		parent->left = newChild;
	}
	else{
		parent->right = newChild;
	}

	if(newChild != NULL){
		newChild->parent = parent;
	}
}


void RBtree::fixInsert(RBtreeNode * node){
	RBtreeNode * parent = node->parent;
	if(parent == NULL){
		node->is_black = true;
		return;
	}
	if(parent->is_black){
		return;
	}
	RBtreeNode * grandparent = parent->parent;
	RBtreeNode * uncle = getUncle(parent);
	if(uncle != NULL and !uncle->is_black){
		parent->is_black = true;
		grandparent->is_black = false;
		uncle->is_black = true;
		fixInsert(grandparent);
	}
	else if (parent == grandparent->left){
		if(node == parent->right){
			rotateLeft(parent);
		parent = node;
		}

	rotateRight(grandparent);

	parent->is_black = true;
	grandparent->is_black = true;
	}
	else{
		if(node == parent->left){
			rotateRight(parent);
			parent = node;

		}
	rotateLeft(grandparent);
	parent->is_black = true;
	grandparent->is_black = false;
	}
}

void RBtree::fixDelete(RBtreeNode *node){
	if(node==root){
		node->is_black = true;
		return;
	}
	RBtreeNode *sibling = getSibling(node);
	if(!sibling->is_black){
		handleRedSibling(node, sibling);
		sibling = getSibling(node);
	}
	if(isBlack(sibling->left) and isBlack(sibling->right)){
		sibling->is_black = false;
		if(!node->parent->is_black){
			node->parent->is_black = true;
			}
		else{
			fixDelete(node->parent);
			}
		}
	else{
		handleBlackSiblingWithAtLeastOneRedChild(node,sibling);
	}
}

void RBtree::handleRedSibling(RBtreeNode *node,RBtreeNode *sibling){
	sibling->is_black = true;
	node->parent->is_black = false;
	if(node = node->parent->left){
		rotateLeft(node->parent);
	}
	else{
		rotateRight(node->parent);
	}
}

void RBtree::handleBlackSiblingWithAtLeastOneRedChild(RBtreeNode *node,RBtreeNode *sibling){
	bool nodeIsLeftChild = (node == node->parent->left);
	if(nodeIsLeftChild and isBlack(sibling->right)){
		sibling->left->is_black = true;
		sibling->is_black = false;
		rotateRight(sibling);
		sibling = node->parent->left;
	}
	else if(!nodeIsLeftChild and isBlack(sibling->left)){
		sibling->right->is_black = true;
		sibling->is_black = false;
		rotateLeft(sibling);
		sibling = node->parent->left;
	}
	sibling->is_black = node->parent->is_black;
	node->parent->is_black = true;
	if(nodeIsLeftChild){
		sibling->right->is_black = true;
		rotateLeft(node->parent);
	}
	else{
		sibling->left->is_black = true;
		rotateRight(node->parent);
	}
}

RBtreeNode * RBtree::findInorderSuccessor(RBtreeNode *node){
	while (node->left!=NULL){
		node = node->left;
	}
	return node;
}

RBtreeNode * RBtree::deleteRBtreeNodewithOneOrZeroChild(RBtreeNode *node){
	if(node->left!=NULL){
		replaceParentChild(node->parent,node,node->left);
		return node->left;
	}
	else if(node->right!=NULL){
		replaceParentChild(node->parent,node,node->right);
		return node->right;
	}
	else{
		RBtreeNode *newchild = node->is_black ? new nillnode():NULL;
		replaceParentChild(node->parent, node, newchild);
		return newchild;
	}

}

RBtreeNode * RBtree::getUncle(RBtreeNode *parent){
	RBtreeNode * grandparent = parent->parent;
	if(grandparent->left == parent){
		return grandparent->right;
		}
	else{
		return grandparent->left;
		}
	}
	
RBtreeNode * RBtree::getSibling(RBtreeNode *node){
	RBtreeNode *parent = node->parent; 
	if(node == parent->left){
		return parent->right;
	}
	else{
		return parent->left;
	}
}

bool RBtree::isBlack(RBtreeNode *node){
	return (node==nullptr or node->is_black);
}


string RBtree::nodeInfoToSave(RBtreeNode *node){		//DONT_NEED_COLOR
	string id = to_string(node->data.id);
	string balance = to_string(node->data.balance);
	string name = node->data.first_name + "," + node->data.last_name;
	string color = (node->is_black) ? "BLACK":"RED";
	string nodeInfo = id +","+balance+","+name+","+color;
	return nodeInfo;
}

void RBtree::saveTreeInorder(RBtreeNode *root){			///chera kar kard ? chera typeid be moshkel khord?
									///maybe removing nillnode make problem in saving for neg_bal_cus
	if(root==NULL or root->data.first_name=="") return;
	string nodeInfo = nodeInfoToSave(root);
	saveTreeInorder(root->left);
	fout << nodeInfo<<endl;
	saveTreeInorder(root->right);
}

void RBtree::saveTree(string PATH_TO_SAVE_TREE){
	fout.open(PATH_TO_SAVE_TREE);
	saveTreeInorder(root);
	fout.close();
}


Customer* RBtree::retrieveUser(){
	string line;
	Customer *customer;
	getline(fin,line);
	stringstream ss(line);
	if(line=="") return NULL;
	string *nodeInfo = new string[10]; 
	int ind=0;
	while(ss.good()){				
		string substr;
		getline(ss,substr,',');
		nodeInfo[ind] = substr;
		ind++;
		}
	customer = new Customer(stoi(nodeInfo[0]),stoi(nodeInfo[1]),nodeInfo[2],nodeInfo[3]);
	ss.str(string());
	return customer;
	}

void RBtree::loadTree(){
	Customer *temp;
	temp = retrieveUser();
	while(temp!=NULL){
		insert(*temp);
		temp = retrieveUser();
	}
}

void RBtree::loadTree(string PATH_TO_LOAD_TREE){
	fin.open(PATH_TO_LOAD_TREE);
	loadTree();
	fin.close();
}

void RBtree::printTree(string prefix,RBtreeNode *node,bool isLeft){	
	if(node!=NULL){
		cout<<prefix;
		cout<<(isLeft ? "├──" : "└──" );
		cout << to_string(node->data.id)+"|"
			+node->data.first_name+" "+node->data.last_name+"|"
			+to_string(node->data.balance)+"|"
			+(node->is_black ? "BLACK":"RED")<< endl;
		printTree( prefix + (isLeft ? "│   " : "    "), node->left, true);
		printTree( prefix + (isLeft ? "│   " : "    "), node->right,false);
		}
	}

void RBtree::printTree(){
	printTree("",root,false);
}


