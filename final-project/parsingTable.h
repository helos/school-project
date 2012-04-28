#include <string>
#include <vector>
#include <deque>
#include "grammer.h"

using namespace std;

#ifndef __PARSING__
#define __PARSING__

class ParsingTable {
private:
	vector<NonTerminal*> nt;
	vector<Terminal*> t;

	void createTables();

	int findTerminal(GrammerObject *);
	int findNonTerminal(GrammerObject *);
public:
	Rule ***table;
	
	ParsingTable(vector<NonTerminal*>,vector<Terminal*>);

	//Get next rule. NULL indicates a problem
	Rule *parse(NonTerminal*,Terminal*);
};


#endif