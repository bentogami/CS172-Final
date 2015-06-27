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
bool Exists(string thing);

void manageIng();
	void checkIng();
	void addIng(string name);
	void destroyIng(string name);

void manageRec();
	void checkRec();
	void addRec(string name);
	void destroyRec(string name);

//Initializing Ingredient Vector.
vector<Ingredient> i;

//Main function
int main()
{	
	fstream f;
	f.open("MasterList.txt", ios::in | ios::out);

	//Checking to see if the MasterList is there
	while (!f.is_open()) {
		f.close();

		//If it isn't, make an empty one
		ofstream create;
		create.open("MasterList.txt");
		create.close();
		
		//reopen the file for editing with f
		f.open("MasterList.txt");
	}

	bool foundRec = false, foundIng = false;
	while (!f.eof()) {
		string curr;
		f >> curr;
		if (curr == "Recipes" || (!foundIng && foundRec)) {
			if (curr == "Recipes")
				foundRec = true;
			
		}
		if (curr == "Ingredients" || foundIng) {
			if (curr == "Ingredients")
				foundIng = true;
			else {
				//Initializing ingredients vector from file
				Ingredient newIng(curr);
				i.push_back(newIng);
			}
		}
	}
	f.clear();
	//Initializing MasterList if there wasn't one already.
	if (!foundRec)
		f << "Recipes\n";
	f.clear();
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
		cout << "1. Check ingredients\n2. Add new ingredient\n3. Dispose of ingredient\n4. Return to main menu\n\n";
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
			cin.ignore();
			cin >> ingName;
			addIng(ingName);
			break;
		}
		case 3:  {
			cout << "Enter the name of the ingredient you want disposed of: ";
			string ingName;
			cin.ignore();
			cin >> ingName;
			destroyIng(ingName);
			break;
		}
		case 4:
			back = true;
		}
	} while (!back);
}

//Manage ingredients functions
void checkIng()
{
	cout << "The ingredients you have are:\n";
	ifstream fin;
	fin.open("MasterList.txt");	

	if (!fin.is_open() || !fin.good()){
		std::cout << "Failed to open file!\n";
		return;
	}
	bool ingFlag = false;
	string curr;
	do {
		curr.clear();
		getline(fin, curr);
		if (ingFlag)
			cout << curr << endl;
		if (curr == "Ingredients")
			ingFlag = true;		
	} while (!fin.eof());
	fin.close();
}

//What happens when you add an ingredient
void addIng(string name)
{
	fstream fout;
	fout.open("MasterList.txt", ios::in | ios::out);
	
	if (!fout.is_open() || !fout.good()) {
		std::cout << "Failed to open file!\n";
		return;
	}

	bool foundIng = false;
	string f;
	while (getline(fout, f)) {		
		if (f.find(name) != string::npos) {
			foundIng = true;
			cout << "You already have that ingredient!\n\n";
		}
	}

	fout.clear();
	if (!foundIng) {
		Ingredient j(name);
		i.push_back(j);
		fout << name << endl;
		j.increaseAmount();
	}

	fout.close();
}

void destroyIng(string name)
{
	if (Exists(name)) {
		fstream f;
		f.open("MasterList.txt", ios::in | ios::out);

		//Create temporary file
		ofstream temp;
		temp.open("Temp.txt");

		//Copy the master list to this temp without that certain ingredient
		string curr;
		while (getline(f, curr)) {
			if (curr == name) {}
			else
				temp << curr << endl;
		}
		temp.close();
		f.close();

		//empty out MasterList
		temp.open("MasterList.txt");
		f.open("Temp.txt");

		//copy the temp file to the masterlist
		curr.clear();
		while (getline(f, curr))
			temp << curr << endl;

		temp.close();
		f.close();

		//For removing stuff from ingredients vector
		vector<Ingredient> temporary;
		for (size_t j = 0; j < i.size(); j++) {
			if (i[j].getName() != name)
				temporary.push_back(i[j]);
		}
		i.clear();
		for (size_t j = 0; j < temporary.size(); j++)
			i.push_back(temporary[j]);
		//temporary will be deleted when this function ends.


		//Delete that temp file
		remove("Temp.txt");

		cout << name << " removed.\n";
	}
	else
		cout << name << " could not be found.\n";
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Manage Recipe and its functions
void manageRec()
{
	cout << "Manage Recipes:\n\n";
	string prompt = "Please select an option:\n";
	bool back = false;

	do {
		cout << prompt << endl;
		cout << "1. List recipes\n2. Add new recipe\n3. Remove recipe\n4. Return to main menu\n\n";
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
			cin.ignore();
			cin >> recName;
			addRec(recName);
			break;
		}
		case 3: {
			cout << "Enter recipe you would like to remove: ";
			string recName;
			cin >> recName;
			destroyRec(recName);
			break;
		}
		default:
			back = true;
			break;
		}
	} while (!back);
}

void checkRec()
{
	//look through the Master list and print the recipes.
	ifstream fin("MasterList.txt");
	cout << "The recipes recorded are:\n";
	cin.clear();
	string curr;
	bool recs = false;
	while (getline(fin, curr)) {		
		if (curr == "Ingredients")
			recs = false;
		if (recs)
			cout << curr << endl;
		if (curr == "Recipes")
			recs = true;
	}
	fin.close();
	cout << endl;
}

void addRec(string name)
{
	if (!Exists(name)) {
		//Puts the recipe in the MasterList file
		ofstream temp("Temp.txt");
		ifstream fin("MasterList.txt");

		//copy over master list and add recipe name
		string curr;
		while (getline(fin, curr)) {			
			temp << curr << endl;
			if (curr == "Recipes") {
				temp << name << endl;
			}
		}

		temp.close();
		fin.close();
		temp.open("MasterList.txt");
		fin.open("Temp.txt");

		//copy temp back to master list
		curr.clear();
		while (getline(fin, curr))
			temp << curr << endl;

		temp.close();
		fin.close();

		//delete temp file
		remove("Temp.txt");

		//Creates a new recipe with that name.
		Recipe r(name);
	}
	else
		cout << "That recipe already exists.\n";
}

void destroyRec(string name)
{
	if (Exists(name)) {
		string filename = name + ".txt";
		remove(filename.c_str());

		ofstream fout("temp.txt");
		ifstream fin("MasterList.txt");
		string curr;
		while (getline(fin, curr)) {
			if (curr == name) {}
			else
				fout << curr << endl;
		}

		fout.close();
		fin.close();
		fout.open("MasterList.txt");
		fin.open("temp.txt");

		curr.clear();
		while (getline(fin, curr))
			fout << curr << endl;

		fout.close();
		fin.close();

		remove("temp.txt");

		cout << name << " removed.\n";
	}
	else
		cout << "There's no recipe named " << name << endl;
}

bool Exists(string thing) 
{
	bool e = false;
	ifstream test;
	test.open("MasterList.txt");
	string curr;
	while (getline(test, curr)) {
		if (curr == thing)
			e = true;
	}
	test.close();
	return e;
}