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
	hasEmptySet = false;
	
	first.changed = false;
	first.computed = false;
	first.hasEmptySet = false;

	
	follow.computed = false;
	follow.isStart = false;
}

Grammer::Grammer(vector<Terminal*> terminals, vector<NonTerminal*> nonterminals) {
	this->terminals = terminals;
	this->nonterminals = nonterminals;
}

/**********************
 * Print Statements
 **********************/
string GrammerObject::toString(){
	return identifier;
}

string GrammerObject::toString(int i){
	return toString();
}

string Rule::toString(){
	string out = "[ ";
	for(int i = 0; i < token.size(); i++){
		if(i>0) out += " ";
		out += token[i]->identifier;
	}
	out += " ]";
	if(token.size() == 0) out = "[ (EMPTY) ]";
	return out;
}

string NonTerminal::toString(){
	string out = identifier + " => { ";
	for(int i = 0; i < rules.size(); i++){
		if(i>0) out += " | ";
		out += rules[i]->toString();
	}
	if(rules.size() == 0) out += "(EMPTY)";
	out += " }";
	return out;
}

string NonTerminal::toString(int i){
	string out = identifier + " => { ";
	out += rules[i]->toString();
	out += " }";
	return out;
}

string Terminal::toString(){
	return identifier;
}

string NonTerminal::printFirst(){
	string out = "First( " + identifier + " ) = { ";
	set<Terminal*>::iterator it;
	for(it = first.terminals.begin(); it != first.terminals.end(); it++ ){
		if(it != first.terminals.begin()) out += ", ";
		out += (*it)->identifier;
	}
	if(first.hasEmptySet) out += ", (EMPTY)";
	out += " }";
	return out;
}

string NonTerminal::printFollow(){
	string out = "Follow( " + identifier + " ) = { ";
	set<Terminal*>::iterator it;
	for(it = follow.terminals.begin(); it != follow.terminals.end(); it++ ){
		if(it != follow.terminals.begin()) out += ", ";
		out += (*it)->identifier;
	}
	if(follow.isStart) out += ", $";
	out += " }";
	return out;
}




/**********************
 * Methods
 **********************/


/* Add rule to list of rules */
void NonTerminal::addRule(Rule *newRule) {
	rules.push_back(newRule);
	if(newRule == empty) {
		hasEmptySet = true;
		first.hasEmptySet = true;
	}
	first.computed = false; // flag first set as unsolved
}


/**********************
 * Calculate First
 **********************/

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
			first.unSolved.push_back(i);
		}
	}

	//check to see if it is already solved
	if(first.unSolved.size() == 0){
		first.computed = true;
		return;
	}

	//add all possible nonTerminals
	for(int i = 0; i < first.unSolved.size(); i++){
		for(int j = 0; j < rules[first.unSolved[i]]->token.size(); j++){
			first.nonTerminals.insert((NonTerminal*)rules[first.unSolved[i]]->token[j]);
			if(((NonTerminal*)rules[first.unSolved[i]]->token[j])->hasEmptySet){
				
			}else{j = rules[first.unSolved[i]]->token.size();}
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
		for(int j = 0; j < rules[first.unSolved[i]]->token.size(); j++){
			if(((NonTerminal*)rules[first.unSolved[i]]->token[j])->first.hasEmptySet){
				if(j+1 == rules[first.unSolved[i]]->token.size())
					first.hasEmptySet = true;
			}else{
				j = rules[first.unSolved[i]]->token.size();
			}
		}
	}
	
	first.computed = true;
	first.changed = false;
}

void NonTerminal::calculateFollow(){

	//check to see if it is solved
	if(follow.computed == true) return;
	
	for(int i=0; i < rules.size(); i++){
		for(int j=0; j+1 < rules[i]->token.size(); j++){
			if(rules[i]->token[j+1]->isTerminal()){
				
			}else{
				set<Terminal*>::iterator it3;
				for(it3 = ((NonTerminal*)rules[i]->token[j+1])->first.terminals.begin(); it3 != ((NonTerminal*)rules[i]->token[j+1])->first.terminals.end(); it3++ ){
					follow.terminals.insert(*it3);
				}
			}
		}
	}

	follow.computed = true;
}
