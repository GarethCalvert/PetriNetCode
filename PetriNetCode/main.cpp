//=======================================================================
// Gareth Calvert - University of Nottingham
// main.cpp : This file contains the 'main' function. 
//=======================================================================
#include "pch.h"
#include <iostream>
#include <cassert>
#include <fstream>
//=======================================================================
#include "Petri_Net_Abstract.h"
#include "Petri_Net_Custom.h"
#include "Place.h"
#include "Transition_Abstract.h"
#include "Transition_Stochastic.h"
#include "Transition_Deterministic.h"
//=======================================================================
int main()
{
    std::cout << "PN Code - Gareth Calvert \n"; 

	//Petri_Net_Custom
	Petri_Net_Custom* PN_Test;
	PN_Test = new Petri_Net_Custom("Test Petri Net", 0, 100);

	PN_Test->Print_Token_Marking();
	
	
	/*
	// T1
	Transitions->at(0)->Set_Input_Arc(Places->at(0), 2);
	Transitions->at(0)->Set_Output_Arc(Places->at(1), 1);
	Transitions->at(0)->Set_Output_Arc(Places->at(5), 1);
	Transitions->at(0)->Set_Inhibitor_Arc(Places->at(5), 1);
	// T2
	Transitions->at(1)->Set_Input_Arc(Places->at(1), 1);
	Transitions->at(1)->Set_Output_Arc(Places->at(2), 1);
	// T3
	Transitions->at(2)->Set_Input_Arc(Places->at(2), 1);
	Transitions->at(2)->Set_Output_Arc(Places->at(3), 1);
	// T4
	Transitions->at(3)->Set_Input_Arc(Places->at(3), 1);
	Transitions->at(3)->Set_Output_Arc(Places->at(4), 1);



	// Mock Simulation
	Transitions->at(0)->Transition_Fire();
	Transitions->at(1)->Transition_Fire();


	for (unsigned int i = 0; i < NumberPlaces; i++)
	{
		Places->at(i)->Print_Place_Marking();
	}

	vector<vector<int> > Transition_Details;
	Transition_Details = Read_Transition_Details_Input();

	//============================================================
	
	// Delete 2D Array pointers

	// Delete vector pointers
	delete[] Places;
	delete[] Transitions;
	*/

	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}