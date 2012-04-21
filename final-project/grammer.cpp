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

Rule::Rule(deque<GrammerObject> thisRule) {
	token = thisRule;
}

Terminal::Terminal(string terminal) {
	this->identifier = terminal;
}

NonTerminal::NonTerminal(string identifier) {
	rules = vector<Rule>();
	this->identifier = identifier;
}


/* Add rule to list of rules */
void NonTerminal::addRule(Rule newRule) {
	rules.push_back(newRule);
}