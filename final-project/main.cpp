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

	removeLeftRecursion();

	printf("Finished");
	getchar();
	return 0;
}