#include <string>
#include <vector>

using namespace std;

#ifndef __GRAMMER__
#define __GRAMMER__

class GrammerObject {
public:
	virtual bool isTerminal();
};

class Rule {
public:
	Rule(vector<GrammerObject>);
	vector<GrammerObject> rule;
};

class Terminal : public GrammerObject {
public:
	Terminal(string);
	string terminal;

	virtual bool isTerminal();
};

class Production : public GrammerObject {
public:
	Production();
	vector<Rule> rules;

	void addRule(Rule);

	virtual bool isTerminal();
};

#endif