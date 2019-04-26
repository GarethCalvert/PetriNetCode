//=======================================================================
// Gareth Calvert - University of Nottingham
// Petri_Net_Abstract.h - Abstract Petri net class for deriving PNs
//=======================================================================
#pragma once
#include "Place.h"
#include "Transition_Abstract.h"
#include "Transition_Stochastic.h"
#include "Transition_Deterministic.h"
#include "Transition_Reset.h"
//=======================================================================
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <sstream>
#include <string>
#include <cassert>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;
//=======================================================================
class Petri_Net_Abstract
{
public:

	vector<vector<int> > Read_Places_Details_Input();
	vector<vector<double> > Read_Transition_Details_Input();
	unsigned int** Read_Arcs_Input();
	
	void Create_Places_Vector();
	void Create_Transitions_Vector();
	void Assign_Arcs();

	//====================================
	// Functions to print to console
	//====================================
	void Print_Header();
	void Print_Footer();
	void Print_Iteration();
	void Print_Token_Marking();
	void Print_MC_Marking();
	void Print_Transition_Properties();

	//====================================
	// Simulation Functions
	//====================================
	void Continuous_Simulation();
	void Continuous_Simulation_Marking();
	void Continuous_Simulation_MC(int NumberSimulations);
	void Continuous_Simulation_Marking_MC(int NumberSimulations);
	void Test_Simulation();
	void Reset_PN();
	void Change_Initial_Marking(vector<unsigned int> NewInitialMarking);

	//====================================
	// Marking Functions
	//====================================
	void Update_Marking();
	//void RecordTokenMarking();
	//void SaveTokenMarking();

	//====================================
	// Other I/O Functions
	//====================================
	//void SaveMatrix(Matrix SaveMatrix, const std::string FileName, const int rows, const int cols, const std::string SavingDescription);
	//void ReadTransitionTimes(Vector* mSaveTransitionTimes, int rows);
	//void ReadInputVector(std::string InputFileName, std::vector<double>* SaveVector, int InputDimension);

protected:

	// PN Properties
	string mPetriNetName;
	int mNumberPlaces;
	int mNumberTransitions;

	// Time Properties
	double mInitialTime;
	double mFinalTime;
	double mCurrentGlobalTime = 0.0;

	// Vectors of the Place and Transition pointers
	vector<Place*>* mpPlaces;
	vector<Transition_Abstract*>* mpTransitions;

	// Vector for list of current enabled transitions
	vector<unsigned int> mEnabledTransitions;

	// Vector to store markings
	vector<unsigned int>* mpInitialMarking;
	vector<unsigned int>* mpCurrentMarking;
	vector<double>* mpMC_Marking;

	// Boolean to note Continuous Simulation Status
	bool mContinueSimulation = true;

	// Int for firing correct transition
	unsigned int mNumberShortestEnable;
	unsigned int mShortestEnableIndex;
	vector<unsigned int> mAllShortestEnable;

	// Used to count how many simulations have occured using the same instance, aids file output names
	unsigned int mSimulationIteration;

};

