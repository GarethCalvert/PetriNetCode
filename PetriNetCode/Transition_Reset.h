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
	Transition_Reset();

	// Destructor
	~Transition_Reset();

	// Pure virtual functions from Transition Abstract
	void Transition_Resample();

	// Function to print out properties
	void Transition_Type_Properties();
};

