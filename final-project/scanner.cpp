#include <iostream>
#include <string>
#include <assert.h>
#include <iterator>

#include "scanner.h"

using namespace std;

vector<Terminal*> terminals;
vector<NonTerminal*> nonterminals;
NonTerminal *start = NULL;

/* Reads in the Grammer and stores it in terminals
 * and nonterminals with the start nonterminal 
 * in start */
void readGrammer() {

	string line;

	//load terminals from line
	getline(cin,line);
	loadTerminals(line);

	//load nonterminals from line
	getline(cin,line);
	loadNonTerminals(line);

	//get start symbol
	getline(cin,line);
	size_t space = line.find(' ');
	start = findNonTerminal(line.substr(space));

	assert(start != NULL);

	getline(cin,line);//%rules

	getline(cin,line);
	while( line.size() > 0) {

		//load rule
		loadRule(line);

		getline(cin,line);
	}
}

/* Read terminals from a line and create them */
void loadTerminals(string line) {
	size_t loc = line.find(' ');
	size_t next = line.find(' ',loc);
	
	while(loc < line.size()) {
		terminals.push_back(new Terminal(line.substr(loc, next-loc)));
		loc = next;
		next = line.find(' ', loc);
	}
}

/* Read nonterminals from a line and create them */
void loadNonTerminals(string line) {
	size_t loc = line.find(' ');
	size_t next = line.find(' ',loc);
	
	while(loc < line.size()) {
		nonterminals.push_back(new NonTerminal(line.substr(loc, next-loc)));
		loc = next;
		next = line.find(' ', loc);
	}
}

/* finds a created terminal */
Terminal* findTerminal(string identifier) {
	int len = terminals.size();
	for( int i=0; i<len; i++) {
		if(terminals[i]->identifier.compare(identifier) == 0)
			return terminals[i];
	}

	return NULL;
}

/* finds a created nonterminal */
NonTerminal* findNonTerminal(string identifier) {
	int len = nonterminals.size();
	for( int i=0; i<len; i++) {
		if(nonterminals[i]->identifier.compare(identifier) == 0)
			return nonterminals[i];
	}

	return NULL;
}

void loadRule(string line) {



}

void removeLeftRecursion() {
	//For each non terminal
	for(int i=0; i<nonterminals.size(); i++) {
		NonTerminal* ai = nonterminals[i];

		//for each non terminal processed before this one
		for(int j=0; j<i ; i++) {
			NonTerminal* aj = nonterminals[j];
			
			//check to see if any rules start with this earlier nonterminal
			for(int k = 0; k < ai->rules.size(); k++) {
				Rule rule = *ai->rules[k];

				//if found must replace with all rules of aj
				if(rule.token[0] == aj) {
					//remove aj from from of rule list see page 160
					rule.token.pop_front();

					//for all rules of aj
					for(int l=0; l<aj->rules.size(); l++) {
						deque<GrammerObject*> ajrule = aj->rules[l]->token;
						//create new rule starting with the ai rule and 
						//ending with aj's lth rule
						deque<GrammerObject*> newRule;

						//push the aj rule then the ai rule without aj
						for(deque<GrammerObject*>::iterator iter = ajrule.begin(); iter != ajrule.end(); iter++)
							newRule.push_back(*iter);
						for(deque<GrammerObject*>::iterator iter = rule.token.begin(); iter != rule.token.end(); iter++)
							newRule.push_back(*iter);

						//Add new rule
						ai->addRule(new Rule(newRule));
					}

					//remove this adjusted rule and adjust k
					ai->rules.erase(ai->rules.begin()+k);
					k--;
				}
			}
		}
		removeImmediateLeft(ai);
	}
}

void removeImmediateLeft(NonTerminal* a) {
	for(int i = 0; i < a->rules.size(); i++) {
		GrammerObject *first = a->rules[i]->token[0];
		if(a == first) {
			
		}
	}
}