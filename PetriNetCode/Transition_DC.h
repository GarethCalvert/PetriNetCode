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

	// Public Functions specific to Transition_BN
	

private:

	// Distribution Variables
	unsigned int mNumberMarkingPermutations;
	double mTransitionTimeStep;
	vector<unsigned int>* mpCausalStateMarkings;
	vector<vector<unsigned int>>* mpCausalStatePermutations;
	vector<double>* mpConditionalProbabilityValues;

	vector<vector<unsigned int>> CausalStatePermutations;
	vector<double> ConditionalProbabilityValues;
	
	bool mFireTest;
	
};

