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

	bool hasEmptySet;

	struct FIRST{ // Declare FIRST struct p. 169 / 177
		bool changed;
		bool computed;
		bool hasEmptySet;
		set<int> unSolved;
		set<Terminal*> terminals;
		set<NonTerminal*> nonTerminals;
	} first;

	void calculateFirst();

};

class Grammer {
public:
	Grammer(vector<Terminal*>, vector<NonTerminal*>);

	vector<Terminal*> terminals;
	vector<NonTerminal*> nonterminals;
};

extern Rule *empty;

void removeLeftRecursion();


template <typename CharT, typename Traits>
basic_ostream<CharT, Traits>& operator<<(
	basic_ostream<CharT, Traits>& out, const GrammerObject& r)
	{  
		return out<< r.toString();
	}

template <typename CharT, typename Traits>
basic_ostream<CharT, Traits>& operator<<(
	basic_ostream<CharT, Traits>& out, const Rule& r)
	{  
		return out<< r.toString();
	}

template <typename CharT, typename Traits>
basic_ostream<CharT, Traits>& operator<<(
	basic_ostream<CharT, Traits>& out, const Terminal& r)
	{  
		return out<< r.toString();
	}

template <typename CharT, typename Traits>
basic_ostream<CharT, Traits>& operator<<(
	basic_ostream<CharT, Traits>& out, const NonTerminal& r)
	{  
		return out<< r.toString();
	}


//ostream& operator<<(ostream& out, const Rule r);
//ostream& operator<<(ostream& out, const NonTerminal r);

#endif

