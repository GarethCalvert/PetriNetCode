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
#include "Transition_BN.h"
//=======================================================================

int main()
{
	//Petri_Net_Custom
	
	Petri_Net_Custom* PN_Test;
	PN_Test = new Petri_Net_Custom("Test_PN", 0, 50);

	PN_Test->Print_Header();
	PN_Test->Print_Token_Marking();
	PN_Test->Print_Transition_Properties();
	PN_Test->Continuous_Simulation();
	PN_Test->Print_Token_Marking();

	PN_Test->Continuous_Simulation_MC(100);
	/*PN_Test->Continuous_Simulation_MC(1000);
	PN_Test->Continuous_Simulation_MC(10000);
	PN_Test->Continuous_Simulation_MC(100000);
	*/

	
	string TransitionName = "TEST";
	unsigned int NumberIn = 2;
	unsigned NumberOut = 1;
	unsigned NumberInhibitorArcs = 0;
	unsigned int NumberCausalArcs = 0;
	unsigned int NumberMarkingPermutations = 0;
	vector<double> Parameters(3);
	for (int i = 0; i < 3; i++)
	{
		Parameters[i] = 1;
	}
	double Transition_Firing_Delay = 0;


	Transition_BN* T_BN_Test;
	T_BN_Test = new Transition_BN(TransitionName, NumberIn, NumberOut, NumberInhibitorArcs, NumberCausalArcs, NumberMarkingPermutations, Parameters, Transition_Firing_Delay);


	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}