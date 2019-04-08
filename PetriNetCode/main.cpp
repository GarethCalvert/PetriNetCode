//=======================================================================
// Gareth Calvert - University of Nottingham
// main.cpp : This file contains the 'main' function. 
//=======================================================================
#include "pch.h"
#include <iostream>
//=======================================================================
#include "Petri_Net_Abstract.h"
#include "Place.h"
#include "Transition_Abstract.h"
#include "Transition_Stochastic.h"
#include "Transition_Deterministic.h"
#include "Functions.h"
//=======================================================================
int main()
{
    std::cout << "PN Code - Gareth Calvert \n"; 

	Place* Place1;
	Place* Place2;
	Place1 = new Place("P1", 1);
	Place2 = new Place("P2", 0);

	Place1->Print_Place_Marking();
	Place2->Print_Place_Marking();

	Transition_Deterministic* Transition1;
	Transition1 = new Transition_Deterministic("T1", 1, 1, 0, 0);

	Transition1->Set_Input_Place(Place1, 1);
	Transition1->Set_Output_Place(Place2, 1);

	Transition1->Transition_Fire();

	Place1->Print_Place_Marking();
	Place2->Print_Place_Marking();


	Transition_Stochastic* T_Test;
	T_Test = new Transition_Stochastic("test", 1, 1, 1, 'E', 1, {1.67});
	//Transition_Deterministic* T_Test_1;
	//T_Test_1 = new Transition_Deterministic();

	vector<Transition_Abstract* >* test_vector;
	test_vector = new vector<Transition_Abstract*>[2];

	test_vector->push_back(T_Test);
	test_vector->push_back(new Transition_Stochastic("test", 1, 1, 1, 'E', 1, { 1.67 }));

	delete T_Test;

	Net_Design(5,2,0);


	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}