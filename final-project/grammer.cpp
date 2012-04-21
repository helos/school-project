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

Rule::Rule(vector<GrammerObject> thisRule) {
	rule = thisRule;
}

Terminal::Terminal(string terminal) {
	this->terminal = terminal;
}

NonTerminal::NonTerminal() {
	rules = vector<Rule>();
}


/* Add rule to list of rules */
void NonTerminal::addRule(Rule newRule) {
	rules.push_back(newRule);
}