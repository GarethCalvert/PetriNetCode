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
	std::ifstream read_file("InputFiles/LEF_DCT_Parameter_Input.txt");
	assert(read_file.is_open());


	int no_entries = 24;

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
	std::ifstream read_file1("InputFiles/LEF_Exp_Transitions_Input.txt");
	assert(read_file1.is_open());


	no_entries = 18;

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
	int NumberSimulations = 100000;
	int ConvergencePlaceIndex = 46; // P47 - 1 as index is zero based
	string Model_File_Name = "LEF";

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
	PN_Model->Change_Transition_Firing_Delay_Time(36, 10); // Fixed Loop Firing Time

	cout << "Simulating Strategy A - MGE-BU" << endl;

	// MGE-BU 
	PN_Model->Change_Transition_Parameters(0, Exp_Values[0]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[1]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[2]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[0]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[1]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[2]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[3]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_A_MGE_BU");

	cout << "Simulating Strategy A - MGE-BU T1M1C1" << endl;
	// MGE-BU T1M1C1
	PN_Model->Change_Transition_Parameters(0, Exp_Values[3]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[4]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[5]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[4]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[5]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[6]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[7]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_A_MGE_BU_T1M1C1");

	cout << "Simulating Strategy A - MGE-BU T2M2C3" << endl;
	// MGE-BU T2M2C3
	PN_Model->Change_Transition_Parameters(0, Exp_Values[6]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[7]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[8]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[8]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[9]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[10]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[11]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_A_MGE_BU_T2M2C3");

	cout << "Simulating Strategy A - MGI-BU" << endl;
	// MGI-BU 
	PN_Model->Change_Transition_Parameters(0, Exp_Values[9]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[10]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[11]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[12]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[13]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[14]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[15]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_A_MGI_BU");

	cout << "Simulating Strategy A - MGI-BU T1M1C1" << endl;
	// MGI-BU T1M1C1
	PN_Model->Change_Transition_Parameters(0, Exp_Values[12]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[13]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[14]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[16]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[17]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[18]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[19]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_A_MGI_BU_T1M1C1");

	cout << "Simulating Strategy A - MGI-BU T2M2C3" << endl;
	// MGI-BU T2M2C2
	PN_Model->Change_Transition_Parameters(0, Exp_Values[15]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[16]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[17]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[20]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[21]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[22]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[23]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_A_MGI_BU_T2M2C3");


	//====================================
	// Strategy B
	//====================================

	cout << "Simulating Strategy 4" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed
	PN_Model->Change_Place_Initial_Marking(39, 0); // Part of fixed paintwork renewal loop

	//---------------------------------------------------------------------------------------------------------------------------------------
	cout << "Simulating Strategy B - MGE-BU" << endl;

	// MGE-BU 
	PN_Model->Change_Transition_Parameters(0, Exp_Values[0]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[1]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[2]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[0]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[1]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[2]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[3]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_B_MGE_BU");

	cout << "Simulating Strategy B - MGE-BU T1M1C1" << endl;
	// MGE-BU T1M1C1
	PN_Model->Change_Transition_Parameters(0, Exp_Values[3]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[4]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[5]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[4]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[5]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[6]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[7]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_B_MGE_BU_T1M1C1");

	cout << "Simulating Strategy B - MGE-BU T2M2C3" << endl;
	// MGE-BU T2M2C3
	PN_Model->Change_Transition_Parameters(0, Exp_Values[6]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[7]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[8]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[8]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[9]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[10]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[11]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_B_MGE_BU_T2M2C3");

	cout << "Simulating Strategy B - MGI-BU" << endl;
	// MGI-BU 
	PN_Model->Change_Transition_Parameters(0, Exp_Values[9]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[10]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[11]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[12]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[13]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[14]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[15]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_B_MGI_BU");

	cout << "Simulating Strategy B - MGI-BU T1M1C1" << endl;
	// MGI-BU T1M1C1
	PN_Model->Change_Transition_Parameters(0, Exp_Values[12]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[13]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[14]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[16]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[17]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[18]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[19]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_B_MGI_BU_T1M1C1");

	cout << "Simulating Strategy B - MGI-BU T2M2C3" << endl;
	// MGI-BU T2M2C2
	PN_Model->Change_Transition_Parameters(0, Exp_Values[15]);
	PN_Model->Change_Transition_Parameters(1, Exp_Values[16]);
	PN_Model->Change_Transition_Parameters(2, Exp_Values[17]);
	PN_Model->Change_Transition_Parameters(3, DCT_Parameters[20]);
	PN_Model->Change_Transition_Parameters(4, DCT_Parameters[21]);
	PN_Model->Change_Transition_Parameters(5, DCT_Parameters[22]);
	PN_Model->Change_Transition_Parameters(6, DCT_Parameters[23]);
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_B_MGI_BU_T2M2C3");

	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();

	return 0;

}
