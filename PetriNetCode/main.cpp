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
	//==================================================================================
	// Opening the file
	std::ifstream read_file("InputFiles/LCA_All_Cohorts_DCT_Parameter_Input.txt");
	assert(read_file.is_open());

	int no_entries = 104;

	// Rewind to the beginning 
	read_file.clear();
	read_file.seekg(std::ios::beg);

	// Allocating memory for vector
	vector<double> Initial(5, 0);
	vector<vector<double> > DCT_Parameters(no_entries, Initial);

	// Input data from the file
	for (int i = 0; i < no_entries; i++)
	{
		read_file >> DCT_Parameters[i][0] >> DCT_Parameters[i][1] >> DCT_Parameters[i][2] >> DCT_Parameters[i][3] >> DCT_Parameters[i][4];
	}

	read_file.close();


	//==================================================================================
	// Opening the file
	std::ifstream read_file1("InputFiles/LCA_All_Cohorts_Exp_Transitions_Input.txt");
	assert(read_file1.is_open());


	no_entries = 78;

	// Rewind to the beginning 
	read_file1.clear();
	read_file1.seekg(std::ios::beg);

	// Allocating memory for vector
	vector<double> Initial1(1, 0);
	vector<vector<double> > Exp_Values(no_entries, Initial1);

	// Input data from the file
	for (int i = 0; i < no_entries; i++)
	{
		read_file1 >> Exp_Values[i][0];
	}

	read_file1.close();

	//==================================================================================
	// Simulation Parameters
	double InitialTime = 0.0;
	double FinalTime = 35.0;
	double TimeStep = 0.02;// 1.0 / 52.0;
	int NumberSimulations = 5000;
	int ConvergencePlaceIndex = 46; // P47 - 1 as index is zero based
	string Model_File_Name = "LCA_All_Cohorts";

	//Petri_Net_Custom

	Petri_Net_Custom* PN_Model;
	PN_Model = new Petri_Net_Custom(Model_File_Name, InitialTime, FinalTime);

	// Initial PN configuration print out
	PN_Model->Print_Header();
	PN_Model->Print_Token_Marking();
	PN_Model->Print_Transition_Properties();

	//====================================
	// Strategy A
	//====================================
	
	// Setting up initial token to enable disable particular intervention types
	
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed
	PN_Model->Change_Place_Initial_Marking(39, 1); // Part of fixed paintwork renewal loop
	PN_Model->Change_Transition_Firing_Delay_Time(36, 5); // Fixed Loop Firing Time

	int expIndex = 0;
	int dctIndex = 0;
	string str;

	for (int i = 0; i < 26; i++)
	{
		PN_Model->Change_Transition_Parameters(0, Exp_Values[expIndex]);
		PN_Model->Change_Transition_Parameters(1, Exp_Values[expIndex + 1]);
		PN_Model->Change_Transition_Parameters(2, Exp_Values[expIndex + 2]);
		PN_Model->Change_Transition_Parameters(3, DCT_Parameters[dctIndex]);
		PN_Model->Change_Transition_Parameters(4, DCT_Parameters[dctIndex + 1]);
		PN_Model->Change_Transition_Parameters(5, DCT_Parameters[dctIndex + 2]);
		PN_Model->Change_Transition_Parameters(6, DCT_Parameters[dctIndex + 3]);
		str = "_Strategy_A_GlobalID_" + to_string(i + 1);
		cout << str << endl;
		PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, str);
		expIndex = expIndex + 3;
		dctIndex = dctIndex + 4;
	}
	

	//====================================
	// Strategy B
	//====================================

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed
	PN_Model->Change_Place_Initial_Marking(39, 1); // Part of fixed paintwork renewal loop
	PN_Model->Change_Transition_Firing_Delay_Time(36, 10); // Fixed Loop Firing Time

	expIndex = 0;
	dctIndex = 0;

	for (int i = 0; i < 26; i++)
	{
		PN_Model->Change_Transition_Parameters(0, Exp_Values[expIndex]);
		PN_Model->Change_Transition_Parameters(1, Exp_Values[expIndex + 1]);
		PN_Model->Change_Transition_Parameters(2, Exp_Values[expIndex + 2]);
		PN_Model->Change_Transition_Parameters(3, DCT_Parameters[dctIndex]);
		PN_Model->Change_Transition_Parameters(4, DCT_Parameters[dctIndex + 1]);
		PN_Model->Change_Transition_Parameters(5, DCT_Parameters[dctIndex + 2]);
		PN_Model->Change_Transition_Parameters(6, DCT_Parameters[dctIndex + 3]);
		str = "_Strategy_B_GlobalID_" + to_string(i + 1);
		cout << str << endl;
		PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, str);
		expIndex = expIndex + 3;
		dctIndex = dctIndex + 4;
	}

	//====================================
	// Strategy C
	//====================================

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed
	PN_Model->Change_Place_Initial_Marking(39, 0); // Part of fixed paintwork renewal loop



	expIndex = 0;
	dctIndex = 0;

	for (int i = 0; i < 26; i++)
	{
	PN_Model->Change_Transition_Parameters(0, Exp_Values[expIndex]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[expIndex+1]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[expIndex+2]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[dctIndex]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[dctIndex+1]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[dctIndex+2]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[dctIndex+3]);
	str = "_Strategy_C_GlobalID_" + to_string(i+1);
	cout << str << endl;
 	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, str);
	expIndex = expIndex + 3;
	dctIndex = dctIndex + 4;
	}

	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}
