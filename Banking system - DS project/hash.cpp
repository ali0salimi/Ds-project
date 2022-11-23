#include "hash.h"
#include <fstream>
#include <bits/stdc++.h>

ofstream out;
ifstream in;

using namespace std;

unsigned long HashTable::DJB2hash(string str){
	unsigned long hash = 5381;
	unsigned int size = str.length();
	unsigned int i=0;
	for(i=0;i<size;i++){
		hash = ((hash << 5) + hash) + (str[i]);
	}
	return hash;

}

void HashTable::insert(string str){
	unsigned int idx= DJB2hash(str)%TABLE_SIZE;
	Table[idx].add(str);
}

void HashTable::remove(string str){
	unsigned int idx= DJB2hash(str)%TABLE_SIZE;
	Table[idx].remove(str);
}

bool HashTable::search(string str){
	unsigned int idx= DJB2hash(str)%TABLE_SIZE;
	return Table[idx].found(str);
}

void HashTable::saveTable(string TABLE_INFO_PATH){
	out.open(TABLE_INFO_PATH);
	out << tableInfo();
	out.close();
}

string HashTable::tableInfo(){
	string tableContent="";
	Linkedlist *temp = Table;
	for(int i=0;i<TABLE_SIZE;i++){
		tableContent+=temp[i].content();
	}
	return tableContent;
}

void HashTable::loadTable(string PATH_TO_SAVE){
	string hashInfo;
	in.open(PATH_TO_SAVE);
	string *tableInfo = new string[TABLE_SIZE];
	getline(in,hashInfo);
	if(hashInfo=="") return;
	stringstream ss(hashInfo);
	while(ss.good()){
		string substr;
		getline(ss,substr,',');
		insert(substr);
	}
}
