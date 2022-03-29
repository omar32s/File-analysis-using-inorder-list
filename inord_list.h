#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
#include <string>
using namespace std;


class inord_list
{
public:

	inord_list();  //construcor

	bool insert(string e, int word_n, int line_n); 
	bool first(string &e, int &word_n, int &line_n);
	bool Next(string &e, int &word_n, int &line_n);
	int distinct();
	string freq();
	int countcertain(string myword,int totalwordscount);
	bool startingwith(string myword,int totalwordscount);
	bool containing(string myword, int totalwordscount);
	bool search(string myword, int totalwordscount);

	~inord_list(); //deconstructor

private:

	struct Node;
	typedef Node* link;

	struct Node 
	{
		string elem;
		int word_number;
		int line_number;
		link next;
	};

	link head;
	link tail;
	link current;

};