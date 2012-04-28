#include "grammer.h"

void readInput(istream*);
void readGrammer();
void readGrammer(istream*);
void loadTerminals(string);
void loadNonTerminals(string);

Terminal* findTerminal(string);
NonTerminal* findNonTerminal(string);

void removeLeftRecursion();
void removeImmediateLeft(NonTerminal* a);

void loadRule(string);

#ifndef __SCANNER__
#define __SCANNER__

extern vector<Terminal*> terminals;
extern vector<NonTerminal*> nonterminals;
extern NonTerminal* start;
extern vector<Terminal*> input;

#endif