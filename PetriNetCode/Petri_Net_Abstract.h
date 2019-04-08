//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Stochastic.h - Abstract Petri net class for deriving PNs
//=======================================================================
#pragma once
#include "Place.h"
#include "Transition_Abstract.h"
#include "Transition_Stochastic.h"
#include "Transition_Deterministic.h"
//=======================================================================
#include <iostream>
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
	// Default Initialise function
	void Initialise();

	//====================================
	// Functions to print to console
	//====================================
	void PrintHeader();
	void PrintFooter();
	void PrintIteration();

	//====================================
	// Simulation Functions
	//====================================
	//void ContinuousSimulation();

	//====================================
	// Marking Functions
	//====================================
	//void PrintTokenMarking();
	//void RecordTokenMarking();
	//void SaveTokenMarking();

	//====================================
	// Other I/O Functions
	//====================================
	//void SaveMatrix(Matrix SaveMatrix, const std::string FileName, const int rows, const int cols, const std::string SavingDescription);
	//void ReadTransitionTimes(Vector* mSaveTransitionTimes, int rows);
	//void ReadInputVector(std::string InputFileName, std::vector<double>* SaveVector, int InputDimension);

	//====================================
	// Random Number Generation
	//====================================
	

	// Returns a random number between 0 & 1, with a uniform distribution
	//double GetUniformDistributedRandomNumber();

	// Random Number functions
	//void GenerateRandomNumbers(Vector RandomVector);
	//void SaveRandomNumbersToFile(Vector RandomVector);
	//void PrintRandomNumbers(Vector RandomVector);
	//void SetRandomFileName(std::string NewRandomFileName);

protected:

	// PN Properties
	string mPetriNetName;
	double mNumberPlaces;
	double mNumberTransitions;

	// Time Properties
	double mInitialTime;
	double mFinalTime;
	double mCurrentGlobalTime = 0;

	// Vectors of the Place and Transition pointers
	vector<Place*>* mpPlaces;
	vector<Transition_Abstract*>* mpTransitions;

	// Vector for list of current enabled transitions
	vector<Transition_Abstract*>* mpEnabledTransitions;

	// Vector to store markings
	vector<unsigned int>* mpInitialMarking;
	vector<unsigned int>* mpCurrentMarking;

	// Boolean to note Continuous Simulation Status
	bool mContinueSimulation = true;

	// Int for firing correct transition
	unsigned int mShortestEnableIndex;

	// Used to count how many simulations have occured using the same instance, aids file output names
	unsigned int mSimulationIteration;

};

