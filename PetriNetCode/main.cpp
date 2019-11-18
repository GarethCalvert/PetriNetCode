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
	//PN_Test = new Petri_Net_Custom("Test_PN1", 0, 100);
	PN_Test = new Petri_Net_Custom("Comp_Net_Counters", 0, 200000);
	//PN_Test = new Petri_Net_Custom("Test_Det", 0, 45);


	PN_Test->Print_Header();
	PN_Test->Print_Token_Marking();
	PN_Test->Print_Transition_Properties();
	//PN_Test->Continuous_Simulation();
	//PN_Test->Print_Token_Marking();
	
	PN_Test->Continuous_Simulation_MC(20000);

	/*
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
	*/

	/*
	vector<double> TestRandom;
	int NumberRuns = 100000;

		// std::random_device is a uniformly-distributed integer random number generator that produces non-deterministic random numbers.
		std::random_device rd;

		// A Mersenne Twister pseudo-random generator of 32-bit numbers with a state size of 19937 bits.
		std::mt19937_64 gen(rd());



	for (int i = 0; i < NumberRuns; i++)
	{
		

		std::uniform_real_distribution<> d(0.0, 1.0);

		TestRandom.push_back(d(gen));

	}

	double Test_Mean = 0;

	for (int i = 0; i < NumberRuns; i++)
	{
		Test_Mean += TestRandom.at(i);

	}

	Test_Mean = Test_Mean / NumberRuns;

	cout << Test_Mean << endl;

	double Test_Var;

	Test_Var = 0;

	for (int i = 0; i < NumberRuns; i++)
	{
		Test_Var += pow(TestRandom.at(i)-Test_Mean, 2);
	}

	Test_Var = Test_Var / NumberRuns;

	cout << Test_Var << endl;

	double Test_SD;

	Test_SD = pow(Test_Var, 0.5);

	cout << Test_SD << endl;
*/
	
	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}