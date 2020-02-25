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
	int NumberSimulations = 200000;
	string Model_File_Name = "DBN_Test"; //"Whole_Model";
	
	//Petri_Net_Custom
	
	Petri_Net_Custom* PN_Model;
	PN_Model = new Petri_Net_Custom(Model_File_Name, InitialTime, FinalTime);

	// Initial PN configuration print out
	PN_Model->Print_Header();
	PN_Model->Print_Token_Marking();
	PN_Model->Print_Transition_Properties();

	// Monte Carlo Simulation
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations,0.02,"_MGE-DK");

	
	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}
