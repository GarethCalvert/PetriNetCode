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
//=======================================================================

int main()
{
	//Petri_Net_Custom
	Petri_Net_Custom* PN_Test;
	PN_Test = new Petri_Net_Custom("Test Petri Net", 0, 100);

	PN_Test->Print_Header();
	PN_Test->Print_Token_Marking();
	PN_Test->Print_Transition_Properties();
	PN_Test->Continuous_Simulation();
	PN_Test->Print_Token_Marking();

	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}