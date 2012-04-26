#include <iostream>
#include <fstream>

#include "grammer.h"
#include "scanner.h"

using namespace std;

int main(int argc, char* argv[]) {

	cout << "Opening " << argv[1] << endl;
	ifstream grammerFile(argv[1], ifstream::in);
	cout << "Opened  " << argv[1] << endl;
	
	readGrammer(&grammerFile);

	cout << "Terminals: " << endl; 
	for(int i = 0; i < terminals.size(); i++)
		cout<< terminals[i]->toString() << "\t";
	cout << endl;

	cout << "NonTerminals: " << endl; 
	for(int i = 0; i < nonterminals.size(); i++)
		cout<< nonterminals[i]->toString() << endl;

	printf("hello world");
	getchar();
	return 0;
}