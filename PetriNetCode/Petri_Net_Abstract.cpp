#include "pch.h"
#include "Petri_Net_Abstract.h"

//====================================
// Initialise Petri Net
//====================================
void Petri_Net_Abstract::Initialise()
{
	std::cout << mPetriNetName << " is Initialised." << std::endl;
	std::cout << "The initial marking of the PN is: " << std::endl;
	//PrintTokenMarking();
	PrintFooter();
}

//================================================
// Print Header
//================================================
void Petri_Net_Abstract::PrintHeader()
{
	cout << "=========================================" << endl
		<< "PN Code - Petri Net Modelling" << endl
		<< "Gareth Calvert - University of Nottingham" << endl
		<< "=========================================" << endl;
}

//================================================
// Print Footer
//================================================
void Petri_Net_Abstract::PrintFooter()
{
	std::cout << "=========================================" << std::endl;
}

//================================================
// Print Iteration
//================================================
void Petri_Net_Abstract::PrintIteration()
{
	Petri_Net_Abstract::PrintFooter();
	cout << "*** Simultation Iteration: " << mSimulationIteration << " ***" << std::endl;
	Petri_Net_Abstract::PrintFooter();
}
