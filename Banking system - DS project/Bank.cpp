#include "Bank.h"

void Bank::search_customer(int id){
    RBtreeNode *res = DB.search(id);
    if (res==NULL){
        cout << "FAILED!"<<endl;
        return;
    }
    else{
        res->data.status();
    }
}


void Bank::negative_balance_customers(RBtreeNode* root){
	DB.saveTree("tempSaveForTree.txt");
	DB.constructPositiveBST("tempSaveForTree.txt");
	DB.colorTree();
}

void Bank::negative_balance_customers(){
	negative_balance_customers(DB.root);
	if(numOfNegativeCustomers==0) cout<<"SUCCESS!"<<endl;
	numOfNegativeCustomers=0;
}


void Bank::richest_customer(){
	DB.search(RichestCustomerID)->data.status_id();
}

void Bank::greater_than_val_customers(RBtreeNode *root,int val){
	if(root==NULL) return;
	if(root->data.balance > val){
		root->data.status_id();
		numOfGTCustomers+=1;
	}
	greater_than_val_customers(root->left,val);
	greater_than_val_customers(root->right,val);
}

void Bank::greater_than_val_customers(int val){
	greater_than_val_customers(DB.root,val);  
	if (numOfGTCustomers==0) cout << "FAILED!"<<endl;
	numOfGTCustomers=0;
}

void Bank::add_customer(string first_name,string last_name,int balance){
	if(RegisteredUsers.search(first_name+last_name)){
		cout<<"FAILED!"<<endl;
		return;
	}
	int customerID = IDgenerator();
	RegisteredUsers.insert(first_name+last_name);
	DB.insert(Customer(customerID,balance,first_name,last_name));
	DB.printTree();
	update_richest_customer(customerID);
}

void Bank::delete_customer(int id){
	if(DB.search(id)==NULL){
		cout<<"FAILED!"<<endl;
		return;
	}
	RBtreeNode *node = DB.search(id);
	RegisteredUsers.remove(node->data.first_name+node->data.last_name);
	DB.remove(id);
	//DB.printTree();
	cout<<"SUCCESS!"<<endl;
}

void Bank::remove_customers_with_negative_balance(RBtreeNode *root){
	//if(root==NULL) return;
	//if(root->data.balance < 0){
	//	delete_customer(root->data.id);
	//	numOfNegativeCustomers+=1;	
	//}
//	remove_customers_with_negative_balance(root->left);
//	remove_customers_with_negative_balance(root->right);
}

void Bank::remove_customers_with_negative_balance(){
//	remove_customers_with_negative_balance(DB.root);
//	DB.printTree();
//	cout<<numOfNegativeCustomers;
//	numOfNegativeCustomers=0;
}

void Bank::change_balance(int id,int val){
	RBtreeNode *node = DB.search(id);
	node->data.balance+=val;
	update_richest_customer(id);
	DB.printTree();
}

int Bank::IDgenerator(){
	int static piv=-1;
	piv+=1;
	return piv;
}

void Bank::update_richest_customer(int id){				///check if this works
	RBtreeNode *node = DB.search(id);
	RBtreeNode *richest_customer = DB.search(RichestCustomerID);
	if(node->data.balance > richest_customer->data.balance){
		RichestCustomerID = id;
	}
	
}

void Bank::loadInfo(string DB_PATH,string TABLE_PATH){
	DB.loadTree(DB_PATH);
	DB.printTree();
	RegisteredUsers.loadTable(TABLE_PATH);
}

void Bank::saveInfo(string DB_PATH_TO_SAVE,string TABLE_PATH_TO_SAVE){
	DB.saveTree(DB_PATH_TO_SAVE);
	RegisteredUsers.saveTable(TABLE_PATH_TO_SAVE);
}

