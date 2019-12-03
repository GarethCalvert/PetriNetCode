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
	double TimeStep = 1.0/52.0;
	int NumberSimulations = 100000;

	//Petri_Net_Custom
	Petri_Net_Custom* PN_Test;
	PN_Test = new Petri_Net_Custom("DC_Insp_Metal_Det_Ind", InitialTime, FinalTime);

	// Initial PN configuration print out
	PN_Test->Print_Header();
	PN_Test->Print_Token_Marking();
	PN_Test->Print_Transition_Properties();

	//PN_Test->Continuous_Simulation();
	//PN_Test->Print_Token_Marking();

	// Monte Carlo Simulation
	//PN_Test->Continuous_Simulation_MC(NumberSimulations);

	// Monte Carlo Similation - Marking
	PN_Test->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep);

	// Clearing objects from memory
	delete PN_Test;

	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}
