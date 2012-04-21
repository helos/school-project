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
	Rule(deque<GrammerObject>);
	deque<GrammerObject> token;
};

class Terminal : public GrammerObject {
public:
	Terminal(string);

	virtual bool isTerminal();
};

class NonTerminal : public GrammerObject {
public:
	NonTerminal(string);
	vector<Rule> rules;

	void addRule(Rule);

	virtual bool isTerminal();
};

#endif

void removeLeftRecursion();