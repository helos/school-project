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

		//For each rule in this nonterminal
		for(int j=0; j< current->rules.size(); j++) {

			if(current->rules[j] == empty) continue;

			//get rule and first token
			Rule *currentRule = current->rules[j];
			GrammerObject *firstToken = currentRule->token[0];

			//if token is a terminal that is where the rule should go
			if(firstToken->isTerminal()) {
				table[i][findTerminal(firstToken)] = currentRule;
				continue;
			}

			//if nonterminal must get out the first set
			set<Terminal*> *first = &((NonTerminal*)firstToken)->first.terminals;
			for(set<Terminal*>::iterator firsts = first->begin(); firsts != first->end(); firsts++) {
				if(table[i][findTerminal(*firsts)] != NULL) cout << "Double\n";
				table[i][findTerminal(*firsts)] = currentRule;
			}

			if(((NonTerminal*)firstToken)->first.hasEmptySet) {
				set<Terminal*> *follow = &((NonTerminal*)firstToken)->follow.terminals;
				for(set<Terminal*>::iterator follows = follow->begin(); follows != follow->end(); follows++) {
					if(table[i][findTerminal(*follows)] != NULL) cout << "Double\n";
					table[i][findTerminal(*follows)] = currentRule;
				}
				if(((NonTerminal*)firstToken)->follow.isStart) {
					if(table[i][t.size()-1] != NULL) cout << "Double\n";
					table[i][t.size()-1] = currentRule;
				}
			}
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

bool parseInput(ParsingTable* table) {
	vector<GrammerObject*> pstack;

	//start with start symbol on the stack
	pstack.push_back(start);



	while(pstack.size() > 0)
	{
		//get current symbol
		GrammerObject *symbol = pstack.back();

		Terminal *token = input.front();

		//If the current symbol is a terminal match it and remove it and the input
		if(symbol->isTerminal())
		{
			if(token == symbol)
			{
				input.pop_front();
				pstack.pop_back();
			}
			else
			{
				return false;
			}
		}
		else
		{
			//Get the correct expansion for the current symbol
			Rule *next = table->parse((NonTerminal*)symbol,token);

			if(next == NULL)
			{
				return false;
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

	return true;
}