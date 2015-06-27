#include "Recipe.h"
#include <fstream>
#include <iostream>
using namespace std;

void Recipe::addPage() 
{	
	//creates a new file named after the recipe
	ofstream F;
	string filename = name + ".txt";
	F.open(filename);

	//copies ingredients to file
	F << name << endl;
	F << "Ingredients" << endl;
	for (size_t j = 0; j < ingredients.size(); j++)
		F << ingredients[j].getName() << endl;

	//Writes instructions to file according to user.
	F << "Instructions" << endl;
	int stepnum = 1;
	bool e = false;
	cout << "Enter the cooking instructions.\nEnter \"end\" when done.\n";
	cin.ignore();
	while (!e) {
		cout << stepnum << ". ";
		string line;
		getline(cin, line);
		if (line == "end") {
			e = true;
			continue;
		}
		F << line << endl;
		stepnum++;
	}

	F.close();	
}

