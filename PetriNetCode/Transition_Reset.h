//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Reset.h - Reset Transition header file -- it is a 
// derived class from Transition_Abstract
//=======================================================================
#pragma once
#include "Transition_Abstract.h"
//=======================================================================

class Transition_Reset :
	public Transition_Abstract
{
public:

	// Specialised Constructor
	Transition_Reset(string TransitionName, unsigned int NumberIn, unsigned int NumberOut, unsigned int NumberInhibitorArcs, unsigned int NumberResetArcs, char DistributionCode, unsigned int NumberParameters, vector<double> Parameters);

	// Destructor
	~Transition_Reset();

	// Pure virtual functions from Transition Abstract
	void Transition_Resample();

	// Function to print out properties
	void Transition_Type_Properties();

private:

	// Distribution Variables
	char mDistributionCode;
	unsigned int mNumberParameters;
	vector<double>* mpParameters;

	

};

