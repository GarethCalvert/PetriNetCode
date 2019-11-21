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
	PN_Test = new Petri_Net_Custom("Comp_Net", 0, 200000);

	// Initial PN configuration print out
	PN_Test->Print_Header();
	PN_Test->Print_Token_Marking();
	PN_Test->Print_Transition_Properties();

	//PN_Test->Continuous_Simulation();
	//PN_Test->Print_Transition_Fire_Count();
	
	// Monte Carlo Simulation
	PN_Test->Continuous_Simulation_MC(20000);


	// Clearing objects from memory
	delete PN_Test;


	/*
	// Matrix Development
	//cin>>CC; cin>>RR; already done
	vector<vector<int> > matrix;
	int RR = 4;
	int CC = 4;

	for (int i = 0; i < RR; i++)
	{
		vector<int> myvector;
		for (int j = 0; j < CC; j++)
		{
			int tempVal = i*j;
			myvector.push_back(tempVal);
		}
		matrix.push_back(myvector);
	}

	cout << matrix.at(3).at(3) << endl;
	*/

	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}