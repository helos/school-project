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

bool Production::isTerminal() {
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

Production::Production() {
	rules = vector<Rule>();
}


/* Add rule to list of rules */
void Production::addRule(Rule newRule) {
	rules.push_back(newRule);
}