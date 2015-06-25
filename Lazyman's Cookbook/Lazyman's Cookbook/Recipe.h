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
	//Amount of this ingredient
	int amt = 0;
	//Amount of all ingredients
	static int amount;

public:	
	Ingredient(string n) 	{
		name = n;		
		amt++;
		amount++;
	}

	string getName() { return name; }
	int getAmt() { return amt; }
	int getAmount() { return amount; }
	void increaseAmount() { amount++; amt++; }
};


class Recipe
{
private:
	string name;
	vector<Ingredient> ingredients;
	string instructions;
	static int numRecipes;

public:
	Recipe(string n, vector<Ingredient> i) {
		name = n;
		ingredients = i;
		fstream manip;
		manip.open("MasterList.txt", ios::app);	
		manip << n << " <" << n << ".txt>" << endl;
		manip.close();
		numRecipes++;
	}
	string getName() { return name; }
	int size() { return ingredients.size(); }
};

#endif