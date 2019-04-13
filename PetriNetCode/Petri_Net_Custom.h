//=======================================================================
// Gareth Calvert - University of Nottingham
// Petri_Net_Custom.cpp : Allows access to the Abstract PN Class. 
// Can be used to read in a PN structure from file.
//=======================================================================
#pragma once
#include "Petri_Net_Abstract.h"
//=======================================================================

class Petri_Net_Custom :
	public Petri_Net_Abstract
{
public:
	Petri_Net_Custom(std::string PetriNetName, double InitialTime, double FinalTime);
	~Petri_Net_Custom();
};

