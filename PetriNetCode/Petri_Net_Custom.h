#pragma once
#include "Petri_Net_Abstract.h"

class Petri_Net_Custom :
	public Petri_Net_Abstract
{
public:
	Petri_Net_Custom(std::string PetriNetName, int NumberPlaces, int NumberTransitions,
		std::vector<Place*>* Places, std::vector<Transition_Abstract*>* Transitions, double InitialTime,
		double FinalTime);
	~Petri_Net_Custom();
};

