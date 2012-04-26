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
	if(newRule == empty) {
		hasEmptySet = true;
		first.hasEmptySet = true;
	}
	first.computed = false; // flag first set as unsolved
}

void NonTerminal::calculateFirst(){

	//check to see if it is solved
	if(first.computed == true) return;

	//do the initial passover
	for( int i = 0; i < rules.size(); i++){
		if(rules[i]->token.size() == 0){
			first.hasEmptySet = true;
		}else if (rules[i]->token[0]->isTerminal()){
			//add terminals to the first list
			first.terminals.insert((Terminal*)(rules[i]->token[0]));
		}else{
			//keep track of unsolved line numbers
			first.unSolved.insert(i);
		}
	}

	//check to see if it is already solved
	if(first.unSolved.size() == 0){
		first.computed = true;
		return;
	}

	//add all possible nonTerminals
	for(int i = 0; i < first.unSolved.size(); i++){
		for(int j = 0; j < rules[i]->token.size(); j++){
			first.nonTerminals.insert((NonTerminal*)rules[i]->token[j]);
			if(((NonTerminal*)rules[i]->token[j])->hasEmptySet){
				
			}else{j = rules[i]->token.size();}
		}
	}

	//solve the possible nonTerminals and add the terminals from them
	set<NonTerminal*>::iterator it;
	for(it = first.nonTerminals.begin(); it != first.nonTerminals.end(); it++ ){
		
		if(*it != this) //make sure that it is not calling it's self
			(*it)->calculateFirst();

		set<Terminal*>::iterator it2;
		for(it2 = (*it)->first.terminals.begin(); it2 != (*it)->first.terminals.end(); it2++){
			first.terminals.insert(*it2);
		}
	}


	//double check if it has an empty set
	for(int i = 0; i < first.unSolved.size(); i++){
		for(int j = 0; j < rules[i]->token.size(); j++){
			if(((NonTerminal*)rules[i]->token[j])->first.hasEmptySet){
				
			}else{j = rules[i]->token.size();}
			first.hasEmptySet = true;
		}
	}

	first.computed = true;
	first.changed = false;
}
