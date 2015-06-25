#include "Recipe.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

//Initializing static values
int Ingredient::amount = 0;
int Recipe::numRecipes = 0;

//Functions used in menus
int answer(int options);
int mainMenu();
void addPage(Recipe r);

void manageIng();
	void checkIng();
	void addIng(string name);
	void destroyIng();
	void incIngAmt(Ingredient i);

void manageRec();
	void checkRec();
	void addRec(string name);
	void destroyRec();

Recipe fileRecipe(string name);

//Main function
int main()
{	
	//Initializing Ingredient and Recipe Vectors.
	vector<Ingredient> i;
	vector<Recipe> r;

	//Checking to see if a MasterList file is already there
	ofstream test;
	test.open("MasterList.txt");
	test.close();
	fstream f;
	f.open("MasterList.txt", ios::in | ios::out);
	bool foundRec = false, foundIng = false;
	while (!f) {
		string curr;
		f >> curr;
		if (curr == "Recipes") {
			foundRec = true;

			/*Updating the recipe's vector
			int pos = f.tellp();
			bool endRec = false;
			while (!endRec && !f) {
				f >> curr;
				//Flag to stop reading in when it finds "Ingredients"
				if (curr == "Ingredients") {
					endRec = true;
					continue;
				}

				//creating a new recipe from file and adding to vector
				Recipe R = fileRecipe(curr);
				r.push_back(R);
			}*/

		}
		else if (curr == "Ingredients") {
			foundIng = true;

			/*Updating the ingredient's vector*/

		}
	}
	//Initializing MasterList if there wasn't one already.
	if (!foundRec)
		f << "Recipes\n";
	if (!foundIng)
		f << "Ingredients\n";
	f.close();	

	//Actual UI code starts here.
	cout << "Welcome to the Lazyman's Cookbook!\n";

	bool exit = false;
	do {
		int ans = mainMenu();

		switch (ans) 
		{
		case 1:
			manageIng();
			break;
		case 2:
			manageRec();
			break;
		case 3:
			exit = true;
			break;			
		}
	} while (exit == false);

	return 0;
}

//Answer function, for selecting from options
int answer(int options) 
{	
	string prompt = "Please select an option: ";
	int ans;
	cin >> ans;
	bool answerFound = false;
	while (!answerFound) {
		if (cin.fail() || ans > options || ans < 1) {
			cout << "This is an invalid selection. Try again.\n";
			cin.clear();
			cin.ignore(10000, '\n');
			cout << prompt;
			cin >> ans;
		}
		else {
			answerFound = true;
		}

	}
	return ans;
}

//Main menu
int mainMenu() 
{
	string prompt = "Please select an option:\n";
	cout << prompt << endl;
	cout << "1. Manage Ingredients\n2. Manage Recipes\n3. Exit\n\n";
	int ans = answer(3);
	cout << endl;
	return ans;
}


//Manage Ingredients menu
void manageIng()
{
	cout << "Manage Ingredients:\n\n";
	string prompt = "Please select an option:\n";
	bool back = false;
	
	do {
		cout << prompt << endl;
		cout << "1. Check ingredients\n2. Add new ingredients\n3. Dispose of ingredients\n4. Return to main menu\n\n";
		int ans = answer(4);
		cout << endl;
		switch (ans)
		{
		case 1:
			checkIng();
			break;
		case 2: {
			cout << "Enter the name of the ingredient you'd like to add: ";
			string ingName;
			cin >> ingName;
			addIng(ingName);
			break;
		}
		case 3: 
			destroyIng();
			break;		
		case 4:
			back = true;
		}
	} while (!back);
}

//Manage ingredients functions
void checkIng()
{
	ifstream fin;
	fin.open("MasterList.txt");

	cout << "The ingredients you have are:\n";

	while (!fin) {
		string curr;
		fin >> curr;
		if (curr == "Ingredients") {
			do {
				fin >> curr;
				cout << curr << endl;
			} while (!fin);
		}
	}
	fin.close();
	cout << endl;
}

//What happens when you add an ingredient
void addIng(string name)
{
	fstream fout;
	fout.open("MasterList.txt", ios::in | ios::out);
	
	bool foundIng = false;
	string f;
	while (getline(fout, f)) {
		if (f == "Ingredients") {
			long int pos = fout.tellp();
			while (!fout) {
				fout >> f;
				if (f == name) {
					incIngAmt(name);
					foundIng = true;
				}
			}
			if (!foundIng) {
				Ingredient i(name);
				//
				fout << endl << name;
			}
		}
	}

	fout.close();
}

void destroyIng()
{
	fstream f;
	f.open("MasterList.txt", ios::in | ios::out);
	//remove ingredients from master list
	f.close();
}


//Manage Recipe and its functions
void manageRec()
{
	cout << "Manage Recipes:\n\n";
	string prompt = "Please select an option:\n";
	bool back = false;

	do {
		cout << prompt << endl;
		cout << "1. Check recipes\n2. Add new recipe\n3. Remove recipe\n4. Return to main menu\n\n";
		int ans = answer(4);
		cout << endl;

		switch (ans)
		{
		case 1:
			checkRec();
			break;
		case 2: {
			cout << "Enter a name for your new recipe: ";
			string recName;
			cin >> recName;
			addRec(recName);
			break;
		}
		case 3:

			break;
		case 4:
			back = true;
			break;
		}
	} while (!back);
}

void checkRec()
{

}

void addRec(string name)
{
	bool exists = false;
	ifstream f;
	f.open("MasterList.txt");
	string curr;
	while (getline(f, curr)) {
		if (curr == "Recipes") {
			bool endRec = false;
			while (!endRec && !f) {
				
			}
		}
	}
}

void destroyRec()
{

}



//adding a page for a new recipe function
void addPage(Recipe r) 
{	
	ofstream manip;
	if (!manip) {
		cout << "addPage failed.\n";
	}
	string filename = r.getName() + ".txt";
	manip.open(filename);
	manip << r.getName() << endl;
	manip.close();
}

void incIngAmt(Ingredient i) {
	i.increaseAmount();
}

Recipe fileRecipe(string name)
{
	vector<Ingredient> i;
	ifstream F;
	string filename = name + ".txt";
	F.open(filename);
	string curr;
	while (!F) {
		F >> curr;
		if (curr == "Ingredients") {
			bool endIng = false;
			while (!F && !endIng) {
				F >> curr;
				if (curr == "Instructions") {
					endIng = true;
					continue;
				}
				Ingredient j(curr);
				i.push_back(j);
			}
		}
	}
	F.close();
	Recipe r(name, i);
	return r;
}