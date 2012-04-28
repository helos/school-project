#include <iostream>
#include <fstream>

#include "grammer.h"
#include "scanner.h"
#include "parsingTable.h"

using namespace std;

#ifndef __MAIN__
#define __MAIN__

void printTheGrammer();
void computeFirsts();
void printFirsts();
void computeFollows();
void printFollows();
void printLanguage();

#endif