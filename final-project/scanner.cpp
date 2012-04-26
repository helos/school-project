#include <string>
#include <assert.h>
#include <iterator>
#include <iostream>

#include "scanner.h"

using namespace std;

vector<Terminal*> terminals;
vector<NonTerminal*> nonterminals;
NonTerminal *start = NULL;

extern Rule *empty = new Rule(deque<GrammerObject*>());

/* Reads in the Grammer and stores it in terminals
 * and nonterminals with the start nonterminal 
 * in start */
void readGrammer(istream *in) {

	string line;

	//load terminals from line
	getline(*in,line);
	loadTerminals(line);


	//load nonterminals from line
	getline(*in,line);
	loadNonTerminals(line);

	//get start symbol
	getline(*in,line);
	size_t space = line.find(' ')+1;
	start = findNonTerminal(line.substr(space));

	assert(start != NULL);

	getline(*in,line);//%rules

	getline(*in,line);
	while( line.size() > 0) {

		//load rule
		loadRule(line);

		getline(*in,line);
	}
}

/* Read terminals from a line and create them */
void loadTerminals(string line) {
	size_t loc = line.find(' ') +1;
	size_t next = line.find(' ',loc);
	
	while(next < line.size()) {
		terminals.push_back(new Terminal(line.substr(loc, next-loc)));
		loc = next +1;
		next = line.find(' ', loc);
	}
}

/* Read nonterminals from a line and create them */
void loadNonTerminals(string line) {
	size_t loc = line.find(' ') +1;
	size_t next = line.find(' ',loc);
	
	while(next < line.size()) {
		nonterminals.push_back(new NonTerminal(line.substr(loc, next-loc)));
		loc = next +1;
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

//Reads list of rules for a non terminal
void loadRule(string line) {

	string name = line.substr(0, line.find(' '));
	NonTerminal *nonterminal = findNonTerminal(name);

	if(nonterminal == NULL) {
		cout << "No NonTerminal of name " << name;
	}

	//Get start and end of first rule
	size_t start = line.find_first_not_of(' ',line.find(' ',line.find(' ')));
	size_t end = line.find_first_of('|');

	string rule = line.substr(start, end-start);
	while(rule.size() > 0) {

		//will store the rule
		deque<GrammerObject*> *ruleList = new deque<GrammerObject*>(0);

		//get first token
		size_t tokenStart = 0;
		size_t tokenEnd = rule.find(' ');
		string token = rule.substr(0, tokenEnd);

		//for all tokens
		while(token.size() > 0) {
			
			//Get the object corresponding to the token
			GrammerObject *next = NULL;
			if(token[0] == '<') { //is a NonTerminal
				next = findNonTerminal(token);
			} else { //Should be a Terminal otherwise
				next = findTerminal(token);
			}

			//Sanity Check, next should be a terminal or nonterminal
			if(next == NULL) {
				cout << "ERROR: " << token << " not found in rule " << rule << "\n";
			}

			//Add GrammerObject to end of rule
			ruleList->push_back(next);

			//Get the next token
			tokenStart = tokenEnd +1;
			tokenEnd = rule.find(' ', tokenStart);
			token = rule.substr(tokenStart, tokenEnd - tokenStart);
		}

		//Add constructed rule to nonterminal
		nonterminal->addRule(new Rule(*ruleList));

		//get the next rule
		start = end + 2;
		end = line.find('|',start);
		rule = line.substr(start, end-start -1); //do not include trailing space
	}
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
	NonTerminal* aPrime = new NonTerminal(a->identifier + " ' ");

	for(int i = 0; i < a->rules.size(); i++) {
		GrammerObject* first = a->rules[i]->token[0];
		if(a == first) {
			Rule* rulePrime = a->rules[i];
			rulePrime->token.pop_front();
			aPrime->addRule(rulePrime);
			nonterminals.push_back(aPrime);
			rulePrime->token.push_back(aPrime);

			aPrime->addRule(new Rule(deque<GrammerObject*>(0)));

			a->rules.erase(a->rules.begin() + i);
			i--;
		}
	}

	for(vector<Rule*>::iterator i = a->rules.begin(); i != a->rules.end(); i++) {
		(*i)->token.push_back(aPrime);
	}
	
}

void removeLeftFactoring(NonTerminal* a){

	//Temporary holder for all rules with same values
	deque<Rule*> listRules;

	//Value for all tokens that are the same
	deque<GrammerObject*> alpha;

	//For all rules
	for(int i = 0; i < a->rules.size(); i++){
		//Clear the rules to test for the next iteration
		listRules.clear();

		//Clear the value of alpha for the next iteration
		alpha.clear();

		listRules.push_back(a->rules[i]);

		//Gather all rules with the same start as rule i
		for(int j = i+1; a->rules.size(); j++){
			
			//Test to see if begining of rule j matches rule i
			if(a->rules[i]->token[0] == a->rules[j]->token[0]){

				//remember j
				listRules.push_back(a->rules[j]);

				//remove j and decrement because of vacancy
				a->rules.erase(a->rules.begin()+j);
				j--;
			}
		}

		//only stay in iteration if rules matched rule i
		if(listRules.size() <= 1) continue;

		//gather 
		while(true) {
			bool same = true;
			GrammerObject* compareTo = listRules[0]->token[0];

			//same is true iff all tokens = compareTo
			for(int l = 0; listRules.size(); l++){
				same = same && listRules[l]->token.size() > 0 &&compareTo == listRules[l]->token[0];
			}

			//If not all tokens were the same break
			if(!same) break;

			//add first token to alpha
			alpha.push_back(listRules[0]->token[0]);

			//erase first token from rules
			for(int l = 0; listRules.size(); l++){
				listRules[l]->token.pop_front();
			}
		}

		//Create new nonterminal and add these rules to it
		NonTerminal *newNT = new NonTerminal(a->identifier+"'");
		for(int l = 0; listRules.size(); l++){
			newNT->addRule(listRules[l]);
		}

		nonterminals.push_back(newNT);

		alpha.push_back(newNT);
		a->addRule(new Rule(alpha));
	}
}