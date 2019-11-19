//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Abstract.h - Abstract Transition header file for class 
// providing an interface for all derived transition classes
//=======================================================================
#include <vector>
#include <cmath>
#include <string>
#include <iostream>
#include <random>
#include <cassert>
#include "Place.h"
using namespace std;
//=======================================================================
#pragma once

class Transition_Abstract
{
	public:
		// Pure Virtual functions that are required for derived classes
		virtual void Transition_Resample() = 0;
		virtual void Transition_Type_Properties() = 0;

		// Virtual functions that are defined but can be overridden by derived classes
		virtual void Transition_Fire();
		virtual void Transition_Enabled_Check(double GlobalTime);

		// Public functions common to all derived transition classes
		void Set_Input_Arcs_Vector(vector<Place*> InputPlaces, vector<unsigned int> InputWeights);
		void Set_Output_Arcs_Vector(vector<Place*> OutputPlaces, vector<unsigned int> OutputWeights);
		void Set_Inhibitor_Arcs_Vector(vector<Place*> InhibitorPlaces, vector<unsigned int> InihibitorWeights);
		void Set_Input_Arc(Place* InputPlace, unsigned int InputWeight);
		void Set_Output_Arc(Place* OutputPlace, unsigned int OutputWeight);
		void Set_Inhibitor_Arc(Place* InhibitorPlace, unsigned int InhibitorWeight);
		
		bool Get_Enabled_Status();
		double Get_Uniform_Distributed_Random_Number();

		// Accessor Functions
		string Get_Transition_Name();
		unsigned int Get_Number_Input_Arcs();
		unsigned int Get_Number_Output_Arcs();
		unsigned int Get_Number_Inhibitor_Arcs();
		unsigned int Get_Number_Reset_Arcs();
		unsigned int Get_Number_Causal_Arcs();
		double Get_Remaining_Delay();

		// Print function
		void Print_Transition_Properties();
		

	protected:
		// Transition member variables
		string mTransitionName;
		unsigned int mTransitionCode;
		unsigned int mNumberInputArcs;
		unsigned int mNumberOutputArcs;
		unsigned int mNumberInhibitorArcs;
		unsigned int mNumberResetArcs = 0;
		unsigned int mNumberCausalArcs = 0;
		vector<Place*>* mpInputPlaces;
		vector<Place*>* mpOutputPlaces;
		vector<Place*>* mpInhibitorPlaces;
		vector<unsigned int>* mpInputWeights;
		vector<unsigned int>* mpOutputWeights;
		vector<unsigned int>* mpInhibitorWeights;

		// Timing variables
		double mCumulativeTime;
		double mRemainingDelay;
		double mEnabledTime;
		double mTransitionDelay;
		bool mTransitionEnabled;
		bool mTransitionInhibited;

		// std::random_device is a uniformly-distributed integer random number generator that produces non-deterministic random numbers.
		std::random_device rd;
};