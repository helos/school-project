#include "grammer.h"

void readGrammer();
void loadTerminals(string);
void loadNonTerminals(string);

Terminal* findTerminal(string);
NonTerminal* findNonTerminal(string);

void loadRule(string);

#ifndef __SCANNER__
#define __SCANNER__

extern vector<Terminal*> terminals;
extern vector<NonTerminal*> nonterminals;
extern NonTerminal* start;

#endif