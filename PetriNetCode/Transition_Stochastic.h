#pragma once
#include "Transition_Abstract.h"
class Transition_Stochastic :
	public Transition_Abstract
{
public:
	// Specialised Constructor
	Transition_Stochastic(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, char DistributionCode, unsigned int NumberParameters, vector<double> Parameters);

	// Destructor
	~Transition_Stochastic();

	// Virtual functions from Transition_Abstract that require a definition
	void Transition_Fire();
	void Transition_Resample();
	void Transition_Enabled_Check();

	// Public Functions specific to Transition_Stochastic
	void Set_Distribution_Parameters(char DistributionCode, unsigned int NumberParameters, vector<double> Parameters);

private:
	// Timing variables
	double mCumulativeTime;
	double mRemainingDelay;
	double mEnabledTime;

	// Distribution Variables
	char mDistributionCode;
	unsigned int mNumberParameters;
	vector<double>* mpParameters;
};

