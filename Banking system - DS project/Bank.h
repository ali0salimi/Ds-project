#include "RBtree.h"
#include "hash.h"
#include <iostream>


using namespace std;


class Bank{
	private : 
		RBtree DB;
		HashTable RegisteredUsers;
		int RichestCustomerID;
		int IDgenerator();
		void negative_balance_customers(RBtreeNode*);
		void greater_than_val_customers(RBtreeNode*,int);
		void remove_customers_with_negative_balance(RBtreeNode *root);
		void update_richest_customer(int );
		int numOfNegativeCustomers=0;
		int numOfGTCustomers=0;
	public :
		void search_customer(int);
		void negative_balance_customers();
		void richest_customer();
		void greater_than_val_customers(int val);
		void add_customer(string,string,int);
		void delete_customer(int);
		void remove_customers_with_negative_balance();
		void change_balance(int,int);
		void loadInfo(string,string);
		void saveInfo(string,string);
		Bank(){};


};



