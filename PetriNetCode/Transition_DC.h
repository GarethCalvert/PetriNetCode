//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_DC.h - Transition - Dynamic Conditionalheader file for class 
// providing an interface for all derived transition classes
//=======================================================================
#pragma once
#include "Transition_Abstract.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
class Transition_DC : public Transition_Abstract
{
public:
	// Specialised Constructor
	Transition_DC(string TransitionName, string PetriNetName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, unsigned int NumberCausalArcs, unsigned int NumberMarkingPermutations, double TimeStep);
	// Destructor
	~Transition_DC();

	// Virtual functions from Transition_Abstract that require a definition
	void Transition_Resample();
	void Transition_Fire();

	// Function to print out properties
	void Transition_Type_Properties();

private:

	// Private Variables
	unsigned int mNumberMarkingPermutations; // Number of permutations of defined markings
	double mTransitionTimeStep; // Timestep between firing attempts when transition becomes enabled
	vector<unsigned int>* mpCausalStateMarkings; // Vector to store the current markings of the causal arc places
	vector<vector<unsigned int>>* mpCausalStatePermutations; // Vector to store the different marking permutations for the causal arcs
	vector<double>* mpConditionalProbabilityValues;
	
	// Variables for the firing algorithm
	bool mFireTest;
	bool mMarkingDetermined;
	int mMarkingPermutationIndex;
	int index;
	double SampleProbability;
	double RandomSample;
	
};

