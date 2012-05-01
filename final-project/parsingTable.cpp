#include "parsingTable.h"
#include <iostream>
#include <fstream>

ParsingTable::ParsingTable(vector<NonTerminal*> nonterminals, vector<Terminal*> terminals) {
	nt = nonterminals;
	t = terminals;

	t.push_back(new Terminal("$"));

	//dynamically allocate 2D table
	table = new Rule **[nt.size()];
	for(int i=0; i<nt.size(); i++)
		table[i] = new Rule *[t.size()];

	//initalize to empty
	for(int i=0; i<nt.size(); i++)
		for(int j=0; j<t.size(); j++)
			table[i][j] = NULL;

	createTables();
}

void ParsingTable::createTables() {
	for(int i=0; i<nt.size(); i++) {
		
		NonTerminal *current = nt[i];

		Rule *emptyRule = NULL;

		//For each rule in this nonterminal
		for(int j=0; j< current->rules.size(); j++) {
			
			Rule *currentRule = current->rules[j];

			if(current->rules[j]->token.size() == 0) continue;

			//get first token
			GrammerObject *firstToken = currentRule->token[0];

			//if token is a terminal that is where the rule should go
			if(firstToken->isTerminal()) {
				table[i][findTerminal(firstToken)] = currentRule;
				continue;
			}

			//if nonterminal must get out the first set
			set<Terminal*> *first = &((NonTerminal*)firstToken)->first.terminals;
			for(set<Terminal*>::iterator firsts = first->begin(); firsts != first->end(); firsts++) {
				table[i][findTerminal(*firsts)] = currentRule;
			}

			if(((NonTerminal*)firstToken)->first.hasEmptySet) {
				emptyRule = currentRule;
			}
		}

		if(emptyRule != NULL) {
			set<Terminal*> *follow = &current->follow.terminals;
			for(set<Terminal*>::iterator f = follow->begin(); f != follow->end(); f++)
				table[i][findTerminal(*f)] = emptyRule;
		}
	}
}



int ParsingTable::findTerminal(GrammerObject* terminal) {
	if(!terminal->isTerminal()) {
		cout << "Could not recognize terminal " << terminal->identifier << endl;
		return -1;
	}

	for(int i=0; i<t.size(); i++) {
		if(t[i] == terminal)
			return i;
	}

	cout << "Could not recognize terminal " << terminal->identifier << endl;
	return -1;
}

int ParsingTable::findNonTerminal(GrammerObject* nonterminal) {
	if(nonterminal->isTerminal()) {
		cout << "Could not recognize nonterminal " << nonterminal->identifier << endl;
		return -1;
	}

	for(int i=0; i<nt.size(); i++) {
		if(nt[i] == nonterminal)
			return i;
	}

	cout << "Could not recognize nonterminal " << nonterminal->identifier << endl;
	return -1;
}

Rule *ParsingTable::parse(NonTerminal *state, Terminal *match) {
	return table[findNonTerminal(state)][findTerminal(match)];
}

void ParsingTable::print() {

	ofstream outFile("ParseTable.txt", ifstream::out);

	outFile << "\t\t";
	for(vector<Terminal*>::iterator i=t.begin(); i!=t.end(); i++)
		outFile << "\t| " << (*i)->identifier;
	outFile << endl;
	for(int i=0; i<nt.size(); i++) {
		outFile << (nt[i])->identifier << "\t";

		for(int j=0; j<t.size(); j++) {
			outFile << "\t| ";
			if(table[i][j] == NULL)
				outFile << "\t\t\t";
			else
				outFile << table[i][j]->toString();
		}

		outFile << "\n";
	}

	outFile.close();

	system("ParseTable.txt");
}

void dump(vector<GrammerObject*>,Terminal*);

bool parseInput(ParsingTable* table) {
	vector<GrammerObject*> pstack;

	//start with start symbol on the stack
	pstack.push_back(start);

	vector<Terminal*>::iterator inputToken = input.begin();

	while(pstack.size() > 0 && inputToken != input.end())
	{
		//get current symbol
		GrammerObject *symbol = pstack.back();

		Terminal *token = *inputToken;

		//If the current symbol is a terminal match it and remove it and the input
		if(symbol->isTerminal())
		{
			if(token == symbol)
			{
				inputToken++;
				pstack.pop_back();
			}
			else
			{
				dump(pstack, token);
				return false;
			}
		}
		else
		{
			//Get the correct expansion for the current symbol
			Rule *next = table->parse((NonTerminal*)symbol,token);

			if(next == NULL)
			{
				if( ((NonTerminal*)symbol)->hasEmptySet) {
					pstack.pop_back();
					continue;
				} else {
					dump(pstack, token);
					return false;
				}
			}
			else
			{
				//Remove the old symbol and replace it with the new rule
				pstack.pop_back();
				for(deque<GrammerObject*>::reverse_iterator i = next->token.rbegin(); i != next->token.rend(); ++i)
				{
					pstack.push_back(*i);
				}
			}
		}
	}

	if(pstack.size() > 0) {
		dump(pstack, *inputToken);
		return false;
	}

	return true;
}

void dump(vector<GrammerObject*> stack,Terminal* token) {
	cout << "Input: " << token->identifier << endl;
	cout << "Stack:\n";
	for(vector<GrammerObject*>::reverse_iterator i = stack.rbegin(); i != stack.rend(); i++)
		cout << '\t' << (*i)->identifier << endl;
}