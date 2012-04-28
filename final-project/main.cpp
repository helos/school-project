#include "main.h"

using namespace std;

int main(int argc, char* argv[]) {

	if(argc < 3) {
		cout << "ERROR: expect 2 arguments, the Grammer file and the input file\n";
		return 1;
	}

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

	cout << endl << "Compute the Firsts" << endl;
	computeFirsts();
	printFirsts();
	
	cout << endl << "Compute the Follows" << endl;
	computeFollows();
	printFollows();

	cout << endl << "Parsing Table" << endl;

	ParsingTable table(nonterminals, terminals);
	table.print();

	ifstream inputFile(argv[2], ifstream::in);

	parseThis(&table,&inputFile);

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


void computeFirsts(){
	for(int i = 0; i < nonterminals.size(); i++){
		nonterminals[i]->calculateFirst();
	}
}

void printFirsts(){
	cout << endl 
		 << "=================================" << endl
		 << "FIRST SETS:" << endl
		 << "-------------------"<< endl;
	for(int i = 0; i < nonterminals.size(); i++){
		cout << nonterminals[i]->printFirst() << endl;
	}
	cout << "=================================" << endl;	
}


void computeFollows(){
	for(int i = 0; i < nonterminals.size(); i++){
		nonterminals[i]->calculateFollow();
	}
	start->follow.isStart = true;
}

void printFollows(){
	cout << endl 
		 << "=================================" << endl
		 << "FOLLOW SETS:" << endl
		 << "-------------------"<< endl;
	for(int i = 0; i < nonterminals.size(); i++){
		cout << nonterminals[i]->printFollow() << endl;
	}
	cout << "=================================" << endl;	
}