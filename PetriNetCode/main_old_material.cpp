#include "pch.h"

/*
	// DBN - PN Convergence

	// Simulation Parameters
	double InitialTime = 0.0;
	double FinalTime = 25.0;
	double TimeStep = 0.02;// 1.0 / 52.0;
	int NumberSimulations = 500000;
	string Model_File_Name = "DBN_Test"; //"Whole_Model";

	//Petri_Net_Custom

	Petri_Net_Custom* PN_Model;
	PN_Model = new Petri_Net_Custom(Model_File_Name, InitialTime, FinalTime);

	// Initial PN configuration print out
	PN_Model->Print_Header();
	PN_Model->Print_Token_Marking();
	PN_Model->Print_Transition_Properties();

	// Monte Carlo Simulation
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations,0.02,"_MGE-DK-BU-2019");
	*/

//--------------------------------------------------------------------------------------------------------------
// Paper 3 - Code

/*
	// Simulation Parameters
	double InitialTime = 0.0;
	double FinalTime = 35.0;
	double TimeStep = 0.02;// 1.0 / 52.0;
	int NumberSimulations = 100000;
	int ConvergencePlaceIndex = 46; // P47 - 1 as index is zero based
	string Model_File_Name = "RESS_MGE"; // "Frontiers"; //"Whole_Model";

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
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 1); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 1); // Repair [P,C,B] when [B2] revealed

	PN_Model->Change_Place_Initial_Marking(39, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_0");

	//====================================
	// Strategy 1
	//====================================

	cout << "Simulating Strategy 1" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(39, 1); // Part of fixed paintwork renewal loop
	PN_Model->Change_Transition_Firing_Delay_Time(36, 5); // Fixed Loop Firing Time

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_1");

	//====================================
	// Strategy 2
	//====================================

	cout << "Simulating Strategy 2" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(39, 1); // Part of fixed paintwork renewal loop
	PN_Model->Change_Transition_Firing_Delay_Time(36, 10); // Fixed Loop Firing Time

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_2");

	//====================================
	// Strategy 3
	//====================================

	cout << "Simulating Strategy 3" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(39, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_3");

	//====================================
	// Strategy 4
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


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC_Convergence(NumberSimulations, TimeStep, ConvergencePlaceIndex, "_Strategy_4");
	*/
	//---------------------------------------------------------------------------------------------------------------------------------------




// ESREL Model Simulations

/*
// Simulation Parameters
	double InitialTime = 0.0;
	double FinalTime = 50.0;
	double TimeStep = 0.02;// 1.0 / 52.0;
	int NumberSimulations = 100000;
	string Model_File_Name = "ESREL_PT"; //"Whole_Model";

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
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 1); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 1); // Repair [P,C,B] when [B2] revealed

	PN_Model->Change_Place_Initial_Marking(39, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_0");

	//====================================
	// Strategy 1
	//====================================

	cout << "Simulating Strategy 1" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(39, 1); // Part of fixed paintwork renewal loop
	PN_Model->Change_Transition_Firing_Delay_Time(36, 5); // Fixed Loop Firing Time

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_1");

	//====================================
	// Strategy 2
	//====================================

	cout << "Simulating Strategy 2" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(39, 1); // Part of fixed paintwork renewal loop
	PN_Model->Change_Transition_Firing_Delay_Time(36, 10); // Fixed Loop Firing Time

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_2");

	//====================================
	// Strategy 3
	//====================================

	cout << "Simulating Strategy 3" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 0); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 0); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(39, 0); // Part of fixed paintwork renewal loop

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_3");



	//====================================
	// Strategy 4
	//====================================

	cout << "Simulating Strategy 4" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 0); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(39, 0); // Part of fixed paintwork renewal loop

	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_4");


	//====================================
	// Strategy 5
	//====================================

	cout << "Simulating Strategy 5" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 0); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(39, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_5");

	//====================================
	// Strategy 6
	//====================================

	cout << "Simulating Strategy 6" << endl;

	// Setting up initial token to enable disable particular intervention types
	PN_Model->Change_Place_Initial_Marking(22, 1); // Repair [P] when [P2,P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(23, 1); // Repair [P] when [P3,P4] revealed
	PN_Model->Change_Place_Initial_Marking(24, 1); // Repair [P] when [P4] revealed
	PN_Model->Change_Place_Initial_Marking(25, 1); // Repair [C] when [C3,C4] revealed
	PN_Model->Change_Place_Initial_Marking(26, 0); // Repair [P,C] when [C4] revealed
	PN_Model->Change_Place_Initial_Marking(27, 0); // Repair [P,C,B] when [B2] revealed


	PN_Model->Change_Place_Initial_Marking(39, 0); // Part of fixed paintwork renewal loop


	// Monte Carlo Similation - Marking
	PN_Model->Continuous_Simulation_Marking_MC(NumberSimulations, TimeStep, "_Strategy_6");


	//================================================
	// Code requiring user input to end program
	//================================================
	std::cout << std::endl << "Press any key to terminate the program..." << std::endl;
	std::cin.get();


*/