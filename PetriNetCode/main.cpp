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
	int NumberSimulations = 30000;
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
	// Strategy 3
	//====================================

	cout << "Simulating Strategy 3" << endl;

	// Setting up transition delay times for the different Strategies
	PN_Model->mpTransitions->at(22)->Change_Fixed_Transition_Delay(0.5); // T23 - Repair paintwork when P2 revealed
	PN_Model->mpTransitions->at(21)->Change_Fixed_Transition_Delay(1); // T22 - Repair paintwork when P3 revealed
	PN_Model->mpTransitions->at(20)->Change_Fixed_Transition_Delay(1); // T21 - Repair paintwork when P4 revealed
	PN_Model->mpTransitions->at(25)->Change_Fixed_Transition_Delay(99); // T26 - Repair corrosion when C3 revealed
	PN_Model->mpTransitions->at(26)->Change_Fixed_Transition_Delay(99); // T27 - Repair corrosion when C4 revealed
	PN_Model->mpTransitions->at(28)->Change_Fixed_Transition_Delay(99); // T29 // Repair corrosion when B2 revealed

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_3");


	//====================================
	// Strategy 4
	//====================================

	cout << "Simulating Strategy 4" << endl;

	// Setting up transition delay times for the different Strategies
	PN_Model->mpTransitions->at(22)->Change_Fixed_Transition_Delay(99); // T23 - Repair paintwork when P2 revealed
	PN_Model->mpTransitions->at(21)->Change_Fixed_Transition_Delay(1); // T22 - Repair paintwork when P3 revealed
	PN_Model->mpTransitions->at(20)->Change_Fixed_Transition_Delay(1); // T21 - Repair paintwork when P4 revealed
	PN_Model->mpTransitions->at(25)->Change_Fixed_Transition_Delay(99); // T26 - Repair corrosion when C3 revealed
	PN_Model->mpTransitions->at(26)->Change_Fixed_Transition_Delay(99); // T27 - Repair corrosion when C4 revealed
	PN_Model->mpTransitions->at(28)->Change_Fixed_Transition_Delay(99); // T29 // Repair corrosion when B2 revealed

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_4");

	//====================================
	// Strategy 5
	//====================================

	cout << "Simulating Strategy 5" << endl;

	// Setting up transition delay times for the different Strategies
	PN_Model->mpTransitions->at(22)->Change_Fixed_Transition_Delay(99); // T23 - Repair paintwork when P2 revealed
	PN_Model->mpTransitions->at(21)->Change_Fixed_Transition_Delay(99); // T22 - Repair paintwork when P3 revealed
	PN_Model->mpTransitions->at(20)->Change_Fixed_Transition_Delay(1); // T21 - Repair paintwork when P4 revealed
	PN_Model->mpTransitions->at(25)->Change_Fixed_Transition_Delay(99); // T26 - Repair corrosion when C3 revealed
	PN_Model->mpTransitions->at(26)->Change_Fixed_Transition_Delay(99); // T27 - Repair corrosion when C4 revealed
	PN_Model->mpTransitions->at(28)->Change_Fixed_Transition_Delay(99); // T29 // Repair corrosion when B2 revealed

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_5");

	//====================================
	// Strategy 6
	//====================================

	cout << "Simulating Strategy 6" << endl;

	// Setting up transition delay times for the different Strategies
	PN_Model->mpTransitions->at(22)->Change_Fixed_Transition_Delay(0.5); // T23 - Repair paintwork when P2 revealed
	PN_Model->mpTransitions->at(21)->Change_Fixed_Transition_Delay(1); // T22 - Repair paintwork when P3 revealed
	PN_Model->mpTransitions->at(20)->Change_Fixed_Transition_Delay(1); // T21 - Repair paintwork when P4 revealed
	PN_Model->mpTransitions->at(25)->Change_Fixed_Transition_Delay(1); // T26 - Repair corrosion when C3 revealed
	PN_Model->mpTransitions->at(26)->Change_Fixed_Transition_Delay(1); // T27 - Repair corrosion when C4 revealed
	PN_Model->mpTransitions->at(28)->Change_Fixed_Transition_Delay(1); // T29 // Repair corrosion when B2 revealed

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_6");

	//====================================
	// Strategy 7
	//====================================

	cout << "Simulating Strategy 7" << endl;

	// Setting up transition delay times for the different Strategies
	PN_Model->mpTransitions->at(22)->Change_Fixed_Transition_Delay(99); // T23 - Repair paintwork when P2 revealed
	PN_Model->mpTransitions->at(21)->Change_Fixed_Transition_Delay(1); // T22 - Repair paintwork when P3 revealed
	PN_Model->mpTransitions->at(20)->Change_Fixed_Transition_Delay(1); // T21 - Repair paintwork when P4 revealed
	PN_Model->mpTransitions->at(25)->Change_Fixed_Transition_Delay(1); // T26 - Repair corrosion when C3 revealed
	PN_Model->mpTransitions->at(26)->Change_Fixed_Transition_Delay(1); // T27 - Repair corrosion when C4 revealed
	PN_Model->mpTransitions->at(28)->Change_Fixed_Transition_Delay(1); // T29 // Repair corrosion when B2 revealed

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_7");

	//====================================
	// Strategy 8
	//====================================

	cout << "Simulating Strategy 8" << endl;

	// Setting up transition delay times for the different Strategies
	PN_Model->mpTransitions->at(22)->Change_Fixed_Transition_Delay(99); // T23 - Repair paintwork when P2 revealed
	PN_Model->mpTransitions->at(21)->Change_Fixed_Transition_Delay(99); // T22 - Repair paintwork when P3 revealed
	PN_Model->mpTransitions->at(20)->Change_Fixed_Transition_Delay(1); // T21 - Repair paintwork when P4 revealed
	PN_Model->mpTransitions->at(25)->Change_Fixed_Transition_Delay(1); // T26 - Repair corrosion when C3 revealed
	PN_Model->mpTransitions->at(26)->Change_Fixed_Transition_Delay(1); // T27 - Repair corrosion when C4 revealed
	PN_Model->mpTransitions->at(28)->Change_Fixed_Transition_Delay(1); // T29 // Repair corrosion when B2 revealed

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
