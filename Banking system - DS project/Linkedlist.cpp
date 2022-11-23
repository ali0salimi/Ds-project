#include <iostream>
#include <string>
#include <cstddef>
#include "Linkedlist.h"

using namespace std;



void Linkedlist::add(string _val){
	if (head==NULL){
		head = new LinkedlistNode(_val);
	}
	else{
		LinkedlistNode *curr = head;
		while(curr->next!=NULL){
			curr = curr->next;
			}
		curr->next = new LinkedlistNode(_val);
		size+=1;
		}
}

void Linkedlist::remove(string val){
	LinkedlistNode *curr = head;
	LinkedlistNode *prev = NULL;
	if(curr->val == val){
		head = head->next;
		return;
		delete curr;
	}
	while(curr->val != val and curr!=NULL){
		prev = curr;
		curr = curr->next;
	}
	if(curr==NULL){
		return; 
	}
	prev->next = curr->next;
	size-=1;
	delete curr;	
}

bool Linkedlist::found(string val){
	LinkedlistNode *curr = head;
	while(curr!=NULL){
		if(curr->val == val){
			return true;
		}
		curr=curr->next;
	}
	return false;	
}

string Linkedlist::content(){
	LinkedlistNode *curr = head;
	string temp="";
	while(curr!=NULL){
		temp+=curr->val+",";
		curr = curr->next;
	}
	return temp;
}

		
