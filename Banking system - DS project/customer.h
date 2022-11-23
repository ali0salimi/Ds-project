
#include <string>
#include <iostream>

using namespace std;

class Customer{
	public :
	int id;
	int balance;
	string first_name;
	string last_name;
	Customer(){};
	Customer(int ID,int BALANCE,string FIRST_NAME,string LAST_NAME){
		id = ID;
		balance = BALANCE;
		first_name = FIRST_NAME;
		last_name = LAST_NAME;
	}
	Customer(const Customer& customer){
		id = customer.id;
		balance = customer.balance;
		first_name = customer.first_name;
		last_name = customer.last_name;
	}
	void status(){
		cout << first_name <<" "<<last_name<<" "<<balance<<endl;
	}
	void status_id(){
		cout << first_name <<" "<<last_name<<" "<<id<<" "<<balance<<endl;
	}

};

