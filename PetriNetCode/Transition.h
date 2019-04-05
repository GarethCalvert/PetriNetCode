#include <string>
#include <iostream>
#include <cassert>
#include <vector>

#include "Place.h" 

using namespace std;
#pragma once
class Transition
{
public:
	// Constructor 
	Transition(string TransitionName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs);

	// Destructor
	~Transition();

	// Public Function
	void Set_Input_Place(Place *InPlace, unsigned int InWeight);
	void Set_Output_Place(Place *OutPlace, unsigned int OutWeight);
	void Set_Stochastic_Parameters(char DistributionCode, unsigned int NumberParameters, vector<double> Parameters);
	void Sample_Transition_Delay();
	void Transition_Enabled_Check(double GlobalTime);
	void Fire_Transition();

	// Accessor Functions
	string Get_Transition_Name();
	double Get_Remaining_Firing_Delay();
	bool Get_Enabled_Status();

private:
	string mTransitionName;
	unsigned int mNumberInputPlaces;
	unsigned int mNumberOutputPlaces;
	unsigned int mNumberInhibitorArcs;
	vector<Place*>* mpInputPlaces;
	vector<Place*>* mpOutputPlaces;
	vector<unsigned int>* mpInputWeights;
	vector<unsigned int>* mpOutputWeights;
	vector<Place*>* mpInhibitorPlaces;
	vector<unsigned int>* mpInhibitorWeights;

	// Distribution Variables
	char mDistributionCode;
	unsigned int mNumberParameters;
	vector<double>* mpParameters;

	// Timing Variables
	double mTransitionDelay;
	double mCumulativeTime;
	double mRemainingDelay;
	double mEnabledTime;

	bool mTransitionEnabled;
	bool mTransitionInhibited;

};

