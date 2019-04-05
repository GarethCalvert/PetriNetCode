#include <vector>
#include <cmath>
#include <iostream>
#include <cassert>
#include "Place.h"

using namespace std;

#pragma once

class Transition_Abstract
{
	public:
		// Virtual functions that are required for derived classes
		virtual void Transition_Fire() = 0;
		virtual void Transition_Resample() = 0;
		virtual void Transition_Enabled_Check() = 0;

		// Public functions common to all derived transition classes
		void Set_Input_Place_Vector(vector<Place*> InputPlaces, vector<unsigned int> InputWeights);
		void Set_Output_Place_Vector(vector<Place*> OutputPlaces, vector<unsigned int> OutputWeights);
		void Set_Inhibitor_Arcs_Vector(vector<Place*> InhibitorPlaces, vector<unsigned int> InihibitorWeights);
		void Set_Input_Place(Place* InputPlace, unsigned int InputWeight);
		void Set_Output_Place(Place* OutputPlace, unsigned int OutputWeight);
		void Set_Inhibitor_Arc(Place* InhibitorPlace, unsigned int InhibitorWeight);
		string Get_Transition_Name();
		bool Get_Enabled_Status();
		


	protected:
		// Transition member variables
		string mTransitionName;
		unsigned int mNumberInputPlaces;
		unsigned int mNumberOutputPlaces;
		unsigned int mNumberInhibitorArcs;
		vector<Place*>* mpInputPlaces;
		vector<Place*>* mpOutputPlaces;
		vector<Place*>* mpInhibitorPlaces;
		vector<unsigned int>* mpInputWeights;
		vector<unsigned int>* mpOutputWeights;
		vector<unsigned int>* mpInhibitorWeights;

		double mTransitionDelay;
		bool mTransitionEnabled;
		bool mTransitionInhibited;
};