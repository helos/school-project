#include <iostream>
#include <fstream>

#include "grammer.h"
#include "scanner.h"

using namespace std;

int main(int argc, char* argv[]) {

	ifstream grammerFile(argv[1], ifstream::in);
	
	readGrammer(&grammerFile);

	removeLeftRecursion();

	printf("Finished");
	getchar();
	return 0;
}