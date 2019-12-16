//=======================================================================
// Gareth Calvert - University of Nottingham
// main.cpp : This file contains the 'main' function. 
//=======================================================================
#include "pch.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
using namespace std;
//=======================================================================
#include "Petri_Net_Abstract.h"
#include "Petri_Net_Custom.h"
#include "Place.h"
#include "Transition_Abstract.h"
#include "Transition_Stochastic.h"
#include "Transition_Deterministic.h"
#include "Transition_DC.h"
//=======================================================================

int main()
{
	// Simulation Parameters
	double InitialTime = 0.0;
	double FinalTime = 25.0;
	double TimeStep = 0.02;// 1.0 / 52.0;
	int NumberSimulations = 100000;
	string Model_File_Name = "Whole_Model";
	
	//Petri_Net_Custom
	
	Petri_Net_Custom* PN_Model;
	PN_Model = new Petri_Net_Custom(Model_File_Name, InitialTime, FinalTime);

	// Initial PN configuration print out
	PN_Model->Print_Header();
	PN_Model->Print_Token_Marking();
	PN_Model->Print_Transition_Properties();

	// Monte Carlo Simulation
	//PN_Model->Continuous_Simulation_MC(NumberSimulations);

	//====================================
	// Strategy 0 - Do Nothing
	//====================================

	cout << "Simulating Strategy 0 - Do Nothing" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(32, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(33, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(34, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(35, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(36, 1); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(37, 1); // Repair [P,C,B] when [B2] revealed

	PN_Model->Change_Place_Initial_Marking(48, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(49, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(50, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_0");

	//====================================
	// Strategy 1 
	//====================================

	cout << "Simulating Strategy 1" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(32, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(33, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(34, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(35, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(36, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(37, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(48, 1); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(49, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(50, 0); // Part of fixed paintwork renewal loop

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_1");

	//====================================
	// Strategy 2
	//====================================

	cout << "Simulating Strategy 2" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(32, 0); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(33, 0); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(34, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(35, 0); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(36, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(37, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(48, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(49, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(50, 0); // Part of fixed paintwork renewal loop

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_2");



	//====================================
	// Strategy 3
	//====================================

	cout << "Simulating Strategy 3" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(32, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(33, 0); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(34, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(35, 0); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(36, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(37, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(48, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(49, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(50, 0); // Part of fixed paintwork renewal loop

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_3");


	//====================================
	// Strategy 4
	//====================================

	cout << "Simulating Strategy 4" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(32, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(33, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(34, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(35, 0); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(36, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(37, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(48, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(49, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(50, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_4");

	//====================================
	// Strategy 5
	//====================================

	cout << "Simulating Strategy 5" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(32, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(33, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(34, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(35, 0); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(36, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(37, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(48, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(49, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(50, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_5");

	//====================================
	// Strategy 6
	//====================================

	cout << "Simulating Strategy 6" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(32, 0); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(33, 0); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(34, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(35, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(36, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(37, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(48, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(49, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(50, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_6");

	//====================================
	// Strategy 7
	//====================================

	cout << "Simulating Strategy 7" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(32, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(33, 0); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(34, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(35, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(36, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(37, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(48, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(49, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(50, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_7");

	//====================================
	// Strategy 8
	//====================================

	cout << "Simulating Strategy 8" << endl;

	
	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(32, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(33, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(34, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(35, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(36, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(37, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(48, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(49, 0); // Part of fixed paintwork renewal loop
	PN_Model->Change_Place_Initial_Marking(50, 0); // Part of fixed paintwork renewal loop

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_8");


	// Clearing objects from memory
	delete PN_Model;

	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}
