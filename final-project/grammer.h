#include <string>
#include <vector>

using namespace std;

#ifndef __GRAMMER__
#define __GRAMMER__

class GrammerObject {
public:
	bool isTerminal();
};

class Terminal : public GrammerObject {
public:
	string terminal;
};

class Production : public GrammerObject {
public:
	vector<Rules> rules;
};

class Rules {
public:
	vector<GrammerObject> rule;
}

#endif