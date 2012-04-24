#include "grammer.h"


/*********************************
 * Return if object is a terminal
 *********************************/

bool GrammerObject::isTerminal() {
	return false;
}

bool Terminal::isTerminal() {
	return true;
}

bool NonTerminal::isTerminal() {
	return false;
}

/**********************
 * Constructors
 **********************/

Rule::Rule(deque<GrammerObject*> thisRule) {
	token = thisRule;
}

Terminal::Terminal(string terminal) {
	this->identifier = terminal;
}

NonTerminal::NonTerminal(string identifier) {
	rules = vector<Rule*>();
	this->identifier = identifier;

	first.changed = false;
	first.computed = false;
}

Grammer::Grammer(vector<Terminal*> terminals, vector<NonTerminal*> nonterminals) {
	this->terminals = terminals;
	this->nonterminals = nonterminals;
}


/* Add rule to list of rules */
void NonTerminal::addRule(Rule *newRule) {
	rules.push_back(newRule);
	first.computed = false; // flag first set as unsolved
}

void NonTerminal::calculateFirst(){

	//do the initial passover
	for( int i = 0; i < rules.size(); i++){
		if(rules[i]->token[0]){
		
		}else if (rules[i]->token[0]->isTerminal()){
			//add terminals to the first list
			first.terminals.push_back((Terminal*)(rules[i]->token[0]));
		}else{
			//keep track of unsolved line numbers
			first.unSolved.push_back(i);
		}
	}

	//
	if(first.unSolved.size() == 0){
		first.computed = true;
		return;
	}
}
