#include "main.h"

using namespace std;

int main(int argc, char* argv[]) {

	ifstream grammerFile(argv[1], ifstream::in);
	
	readGrammer(&grammerFile);

	printTheGrammer();

	removeLeftRecursion();

	printTheGrammer();

	printf("Finished");
	getchar();
	return 0;
}


void printTheGrammer(){
	cout << "Terminals: "; 
	for(int i = 0; i < terminals.size(); i++){
		if(i%5==0) cout << endl << "\t";
		cout<< terminals[i]->toString() << "\t";
	}
	cout << endl << endl;

	cout << "NonTerminals: " << endl; 
	for(int i = 0; i < nonterminals.size(); i++)
		for(int j=0; j<nonterminals[i]->rules.size(); j++)
			cout<< nonterminals[i]->toString(j) << endl;
	cout << "Terminals: "; 
	for(int i = 0; i < terminals.size(); i++){
		if(i%5==0) cout << endl << "\t";
		cout<< terminals[i]->toString() << "\t";
	}
	cout << endl << endl;

	cout << "NonTerminals: " << endl; 
	for(int i = 0; i < nonterminals.size(); i++)
		for(int j=0; j<nonterminals[i]->rules.size(); j++)
			cout<< nonterminals[i]->toString(j) << endl;
		

}