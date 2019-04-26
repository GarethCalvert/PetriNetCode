//=======================================================================
// Gareth Calvert - University of Nottingham
// Petri_Net_Custom.cpp : Allows access to the Abstract PN Class. 
// Can be used to read in a PN structure from file.
//=======================================================================
#include "pch.h"
#include "Petri_Net_Custom.h"
//=======================================================================


//=======================================================================
// Specialised Constructor
//=======================================================================
Petri_Net_Custom::Petri_Net_Custom(std::string PetriNetName, double InitialTime, double FinalTime)
{
	mPetriNetName = PetriNetName;
	mInitialTime = InitialTime;
	mFinalTime = FinalTime;
	Create_Places_Vector();
	Create_Transitions_Vector();
	Assign_Arcs();

	mpInitialMarking = new vector<unsigned int>[mNumberPlaces];
	mpCurrentMarking = new vector<unsigned int>[mNumberPlaces];
	mpMC_Marking = new vector<double>[mNumberPlaces];

	Update_Marking();

	*mpInitialMarking = *mpCurrentMarking;
}

//=======================================================================
// Destructor
//=======================================================================
Petri_Net_Custom::~Petri_Net_Custom()
{

}
