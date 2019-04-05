//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Abstract.cpp - Abstract Transition file for providing an 
// an interface for all derived transition classes
//=======================================================================
#include "pch.h"
#include "Transition_Abstract.h"
//=======================================================================


//=======================================================================
// Set vector containing all the input places for the transition
//=======================================================================
void Transition_Abstract::Set_Input_Place_Vector(std::vector<Place*> InputPlaces, std::vector<unsigned int> InputWeights)
{
	*mpInputPlaces = InputPlaces;
	*mpInputWeights = InputWeights;
}

//=======================================================================
// Set vector containing all the output places for the transition
//=======================================================================
void Transition_Abstract::Set_Output_Place_Vector(std::vector<Place*> OutputPlaces, std::vector<unsigned int> OutputWeights)
{
	*mpOutputPlaces = OutputPlaces;
	*mpOutputWeights = OutputWeights;
}

//=======================================================================
// Set vector containing all the inhibitor arc, places for the transition
//=======================================================================
void Transition_Abstract::Set_Inhibitor_Arcs_Vector(vector<Place*> InhibitorPlaces, vector<unsigned int> InihibitorWeights)
{
	*mpInhibitorPlaces = InhibitorPlaces;
	*mpInhibitorWeights = InihibitorWeights;
}

//=======================================================================
// Add an input place to the input place vector for the transition
//=======================================================================
void Transition_Abstract::Set_Input_Place(Place *InputPlace, unsigned int InputWeight)
{
	mpInputPlaces->push_back(&*InputPlace);
	mpInputWeights->push_back(InputWeight);
}

//=======================================================================
// Add an ouput place to the input place vector for the transition
//=======================================================================
void Transition_Abstract::Set_Output_Place(Place *OutputPlace, unsigned int OutputWeight)
{
	mpOutputPlaces->push_back(&*OutputPlace);
	mpOutputWeights->push_back(OutputWeight);
}

//=======================================================================
// Add an inhibitor place to the input place vector for the transition
//=======================================================================
void Transition_Abstract::Set_Inhibitor_Arc(Place *InhibitorPlace, unsigned int InhibitorWeight)
{
	mpInhibitorPlaces->push_back(&*InhibitorPlace);
	mpInhibitorWeights->push_back(InhibitorWeight);
}

//=======================================================================
// Return Transition Name as a string
//=======================================================================
string Transition_Abstract::Get_Transition_Name()
{
	return mTransitionName;
}

//=======================================================================
// Returns boolean of the enabled status of the transition 
//=======================================================================
bool Transition_Abstract::Get_Enabled_Status()
{
	return mTransitionEnabled;
}