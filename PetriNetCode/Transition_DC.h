#pragma once
#include "Transition_Abstract.h"
class Transition_DC : public Transition_Abstract
{
public:
public:
	// Specialised Constructor
	Transition_DC(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, unsigned int NumberCausalArcs, unsigned int NumberMarkingPermutations, vector<double> Parameters, vector<vector<unsigned int>> MarkingMatrix);
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
	vector<unsigned int>* mpCausalStateMarkings;
	vector<vector<unsigned int>>* mpCausalStatePermutations;
	vector<double>* mpConditionalProbabilityValues;
	
	bool mFireTest;
	
};

