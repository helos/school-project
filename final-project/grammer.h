#include <string>
#include <vector>
#include <deque>

using namespace std;

#ifndef __GRAMMER__
#define __GRAMMER__

class GrammerObject {
public:
	virtual bool isTerminal();
	string identifier;
};

class Rule {
public:
	Rule(deque<GrammerObject*>);
	deque<GrammerObject*> token;
};

class Terminal : public GrammerObject {
public:
	Terminal(string);

	virtual bool isTerminal();
};

class NonTerminal : public GrammerObject {
public:
	NonTerminal(string);
	vector<Rule*> rules;

	void addRule(Rule*);

	virtual bool isTerminal();
	
	bool hasEmptySet;

	struct FIRST{ // Declare FIRST struct p. 169 / 177
		bool changed;
		bool computed;
		bool hasEmptySet;
		vector<int> unSolved;
		vector<Terminal*> terminals;
		vector<NonTerminal*> nonTerminals;
	} first;

	void calculateFirst();

};

class Grammer {
public:
	Grammer(vector<Terminal*>, vector<NonTerminal*>);

	vector<Terminal*> terminals;
	vector<NonTerminal*> nonterminals;
};

Rule *empty;

void removeLeftRecursion();

#endif

