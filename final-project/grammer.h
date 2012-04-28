#include <string>
#include <vector>
#include <deque>
#include <set>

using namespace std;

#ifndef __GRAMMER__
#define __GRAMMER__


class GrammerObject {
public:
	virtual bool isTerminal();
	string identifier;
	virtual string toString();
	virtual string toString(int);
};

class Rule {
public:
	Rule(deque<GrammerObject*>);
	deque<GrammerObject*> token;
	string toString();
};

class Terminal : public GrammerObject {
public:
	Terminal(string);

	virtual bool isTerminal();
	virtual string toString();

};

class NonTerminal : public GrammerObject {
public:
	NonTerminal(string);
	vector<Rule*> rules;

	void addRule(Rule*);

	virtual bool isTerminal();
	
	virtual string toString();
	virtual string toString(int);

	bool hasEmptySet;

	struct FIRST{ // Declare FIRST struct p. 169 / 177
		bool changed;
		bool computed;
		bool hasEmptySet;
		vector<int> unSolved;
		set<Terminal*> terminals;
		set<NonTerminal*> nonTerminals;
	} first;
	
	void calculateFirst();
	string printFirst();

};

class Grammer {
public:
	Grammer(vector<Terminal*>, vector<NonTerminal*>);

	vector<Terminal*> terminals;
	vector<NonTerminal*> nonterminals;
};

extern Rule *empty;

void removeLeftRecursion();
void removeLeftFactoring();

#endif

