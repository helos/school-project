#include <iostream>
#include <string>

using namespace std;

void readGrammer() {

	string line;
	getline(cin,line);

	//TODO line holds tokens

	getline(cin,line);

	//TODO line hold non terminals

	getline(cin,line);

	//TODO like holds start non terminal

	getline(cin,line);//%rules

	getline(cin,line);
	while( line.size() > 0) {

		//TODO load rule

		getline(cin,line);
	}
}
