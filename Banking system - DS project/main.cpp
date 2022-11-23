#include "Bank.h"
#include <string>

using namespace std;

Bank bank;

int main(){
	bank.loadInfo("RBTreeSave.txt","HashTableSave.txt");		//double-check functionality for load/save tree and table  
	string command;
	cin >> command;
	while(command!="-1"){
		if(command=="SEARCH"){
			string arg;
			cin >> arg;
			if(arg=="MINUS"){
				bank.negative_balance_customers();
			}
			else if(arg=="RICHEST"){
				bank.richest_customer();
			}
			else if(arg=="GT"){
				string val_str;
				cin >> val_str;
				int val = stoi(val_str);
				bank.greater_than_val_customers(val);
			}
			else{
				int ID = stoi(arg);
				bank.search_customer(ID);
			}
		}
		else if(command=="REGISTER"){
			string first_name;
			string last_name;
			string balance_str;
			int balance;
			cin >> first_name;
			cin >> last_name;
			cin >> balance_str;
			balance = stoi(balance_str);
			bank.add_customer(first_name,last_name,balance);
		}
		else if(command=="DELETE"){
			string arg;
			cin >> arg;
			if(arg=="MINUS"){
				bank.remove_customers_with_negative_balance();
			}
			else{
			int ID;
			ID = stoi(arg);
			bank.delete_customer(ID);}
		}
		else if(command=="CHANGE"){
			int ID;
			int val;
			string val_str;
			string ID_str;
			cin >> ID_str;
			cin >> val_str;
			ID = stoi(ID_str);
			val = stoi(val_str);
			bank.change_balance(ID,val);
		}
		else{
			cout <<"Try again!"<<endl;}///problem - > multiple failed problem
			fflush(stdin);
			cin >> command;
			}
	bank.saveInfo("RBTreeSave.txt","HashTableSave.txt");
}



//problem with register in DB find out with debugger 
///problem with search func
