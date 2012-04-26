#include "main.h"

using namespace std;

int main(int argc, char* argv[]) {

	ifstream grammerFile(argv[1], ifstream::in);
	
	readGrammer(&grammerFile);

	cout << endl << "Read The Grammer" << endl;
	printTheGrammer();

	removeLeftRecursion();
	
	cout << endl << "Removed Left Recursion" << endl;
	printTheGrammer();

	removeLeftFactoring();
	
	cout << endl << "Removed Left Factoring" << endl;
	printTheGrammer();

	printf("Finished");
	getchar();
	return 0;
}


void printTheGrammer(){
	cout << endl 
		 << "=================================" << endl
		 << "CURRENT GRAMMER:" << endl
		 << "-------------------"<< endl 
		 << "Terminals: "; 
	for(int i = 0; i < terminals.size(); i++){
		if(i%5==0) cout << endl << "\t";
		cout<< terminals[i]->toString() << "\t";
	}
	cout << endl << endl
		 << "-------------------"<< endl 
		 << "NonTerminals: " << endl 
		 << "-------------------"<< endl << endl; 
	for(int i = 0; i < nonterminals.size(); i++)
		for(int j=0; j<nonterminals[i]->rules.size(); j++)
			cout<< nonterminals[i]->toString(j) << endl;
	cout << "=================================" << endl;	

}