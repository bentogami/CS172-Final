#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

#ifndef RECIPE_H
#define RECIPE_H


class Ingredient
{
private:
	string name;	
	//Amount of all ingredients
	static int amount;

public:	
	Ingredient(string n) 	{
		name = n;
	}

	string getName() { return name; }
	int getAmount() { return amount; }
	void increaseAmount() { amount++; }
};


class Recipe
{
private:
	string name;
	vector<Ingredient> ingredients;
	string instructions;
	static int numRecipes;

public:
	Recipe(string n) {
		name = n;
		
		//Populates ingredients
		bool e = false;
		int ingNum = 1;		
		cout << "Enter the ingredients.\nEnter \"end\" when done.\n";		
		while (!e) {
			cout << "Ingredient #" << ingNum << ": ";
			string ing;
			cin.clear();
			cin >> ing;
			if (ing == "end") {
				e = true;
				continue;
			}
			Ingredient newIng(ing);
			ingredients.push_back(newIng);
			ingNum++;
		}
		numRecipes++;

		//Adds a page for this new recipe
		addPage();
	}
	

	string getName() { return name; }
	int size() { return ingredients.size(); }
	void addPage();
};

#endif