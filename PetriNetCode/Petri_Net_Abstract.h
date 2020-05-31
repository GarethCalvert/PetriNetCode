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
#include "Transition_DC.h"
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
#include <tuple>
#include <fstream>
using namespace std;
//=======================================================================
class Petri_Net_Abstract
{
public:

	//====================================
	// Functions read in input files
	//====================================
	vector<vector<int> > Read_Places_Details_Input();
	vector<vector<double> > Read_Transition_Details_Input();
	unsigned int** Read_Arcs_Input();
	
	//====================================
	// Functions to create PN structure
	//====================================
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
	void Print_Transition_Fire_Count();
	void Print_MC_Marking(int NumberSimulations);
	void Print_MC_Transition_Count(int NumberSimulations);
	void Print_Transition_Properties();

	//====================================
	// Simulation Functions
	//====================================
	void Continuous_Simulation();
	void Continuous_Simulation_Marking(double TimeInterval);
	void Continuous_Simulation_MC(int NumberSimulations);
	void Continuous_Simulation_Marking_MC(int NumberSimulations, double TimeInterval, string FileNameSuffix);
	void Continuous_Simulation_Marking_MC_Convergence(int NumberSimulations, double TimeInterval, int ConvergencePlaceIndex, string FileNameSuffix);
	void Test_Simulation();
	void Reset_PN();
	void Change_Initial_Marking(vector<unsigned int> NewInitialMarking);

	//====================================
	// Marking Functions
	//====================================
	void Update_Marking();
	void Update_Transition_Fire_Count();

	//====================================
	// Other I/O Functions
	//====================================
	void Save_Int_Vector_To_File(const std::string FileName, vector<unsigned int> Vector_To_Write);
	void Save_Double_Vector_To_File(const std::string FileName, vector<double> Vector_To_Write);
	void Save_Matrix_To_File(const std::string FileName, vector<vector<double>> Matrix_To_Write);
	vector<vector<double>> Convert_Matrix(vector<vector<unsigned int>> Matrix_To_Convert);

	//====================================
	// Accessor / Functions to alter Place/Transitions
	//====================================
	void Change_Place_Initial_Marking(unsigned int PlaceIndex, unsigned int NewMarking);
	void Change_Transition_Firing_Delay_Time(unsigned int TransitionIndex, double NewDelayTime);
	void Change_Transition_Parameters(unsigned int TransitionIndex, vector<double> ParametersVector);
	
protected:

	//====================================
	// PN Properties
	//====================================
	string mPetriNetName;
	int mNumberPlaces;
	int mNumberTransitions;

	//====================================
	// Time Properties
	//====================================
	double mInitialTime;
	double mFinalTime;
	double mCurrentGlobalTime = 0.0;

	//====================================
	// Vectors of the Places and Transitions
	//====================================
	vector<Place*>* mpPlaces;
	vector<Transition_Abstract*>* mpTransitions;

	//====================================
	// Vector for list of current enabled transitions
	//====================================
	vector<unsigned int> mEnabledTransitions;

	//====================================
	// Vector to store markings
	//====================================
	vector<unsigned int>* mpInitialMarking;
	vector<unsigned int>* mpCurrentMarking;
	vector<unsigned int>* mpTransitionFireCount;
	vector<double>* mpMC_Marking;
	vector<double>* mpMC_TransitionCount;
	vector<vector<unsigned int>> mTimeStepMarkings;
	vector<vector<unsigned int>> mTimeStepTransitionFireCounts;
	vector<vector<double>> mMC_TimeStepMarkings;
	vector<vector<double>> mMC_TimeStepTransitionFireCounts;

	//====================================
	// Continuous Simulation Status
	//====================================
	bool mContinueSimulation = true;

	//====================================
	// Int for firing correct transition
	//====================================
	unsigned int mNumberShortestEnable;
	unsigned int mShortestEnableIndex;
	vector<unsigned int> mAllShortestEnable;

	//====================================
	// Used to count how many simulations 
	// have occured using the same instance, 
	// aids file output names
	//====================================
	unsigned int mSimulationIteration;

};

