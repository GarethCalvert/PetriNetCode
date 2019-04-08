// PetriNetCode.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

#include "Place.h"
#include "Transition.h"

#include "Transition_Abstract.h"
#include "Transition_Stochastic.h"
#include "Transition_Deterministic.h"

int main()
{
    std::cout << "PN Code - Gareth Calvert \n"; 

	Place* Place1;
	Place* Place2;
	Place1 = new Place("P1", 1);
	Place2 = new Place("P2", 0);

	Place1->Print_Place_Marking();
	Place2->Print_Place_Marking();

	Transition* Transition1;
	Transition1 = new Transition("T1", 1, 1, 0);

	Transition1->Set_Input_Place(Place1, 1);
	Transition1->Set_Output_Place(Place2, 1);

	Transition1->Fire_Transition();

	Place1->Print_Place_Marking();
	Place2->Print_Place_Marking();

	Transition1->Set_Stochastic_Parameters('W', 2, { 0.05,1.2 });

	Transition_Stochastic* T_Test;
	T_Test = new Transition_Stochastic("test", 1, 1, 1, 'E', 1, {1.67});
	Transition_Deterministic* T_Test_1;
	//T_Test_1 = new Transition_Deterministic();

	vector<Transition_Abstract* >* test_vector;
	test_vector = new vector<Transition_Abstract*>[2];

	test_vector->push_back(T_Test);
	//test_vector->push_back(T_Test_1);



	delete T_Test;


	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}