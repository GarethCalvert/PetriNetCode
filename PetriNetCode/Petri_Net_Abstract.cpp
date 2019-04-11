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

//================================================
// Print Token Marking
//================================================
void Petri_Net_Abstract::Print_Token_Marking()
{
	for (unsigned int i = 0; i < 6; i++)
	{
		mpPlaces->at(i)->Print_Place_Marking();
	}
}

//=======================================================================
// Function read in Places Details Input File, returns a 2d vector 
// containing the Places properties.
//=======================================================================
vector<vector<int> > Petri_Net_Abstract::Read_Places_Details_Input()
{
	vector<int> Initial(5, 0);
	// This is just an example to get things to work
	vector<vector<int> > Place_Details(11, Initial);

	return Place_Details;

}

//=======================================================================
// Function read in Transitions Details Input File, returns a 2d vector 
// containing the transition properties.
//=======================================================================
vector<vector<int> > Petri_Net_Abstract::Read_Transition_Details_Input()
{
	//============================================================
	// Opening the file
	std::ifstream read_file("Transitions_Global_Details.txt");
	assert(read_file.is_open());

	// Determine length of the file
	double dummy_var1, dummy_var2, dummy_var3, dummy_var4, dummy_var5;
	int no_entries = 0;
	while (!read_file.eof())
	{
		read_file >> dummy_var1 >> dummy_var2 >> dummy_var3 >> dummy_var4 >> dummy_var5;
		no_entries++;
	}

	no_entries--; // Correcting to the appropriate value

	// Rewind to the beginning 
	read_file.clear();
	read_file.seekg(std::ios::beg);

	// Allocating memory for vector
	vector<int> Initial(5, 0);
	vector<vector<int> > Transition_Details(no_entries, Initial);

	// Input data from the file
	for (int i = 0; i < no_entries; i++)
	{
		read_file >> Transition_Details[i][0] >> Transition_Details[i][1] >> Transition_Details[i][2] >> Transition_Details[i][3] >> Transition_Details[i][4];
	}

	read_file.close();

	return Transition_Details;
}

//=======================================================================
// Function read in Transitions Details Input File, returns a 2d vector 
// containing the transition properties.
//=======================================================================
vector<vector<int> > Petri_Net_Abstract::Read_Arcs_Input()
{
	//============================================================
	// Opening the file
	std::ifstream myfile; // Define Input Stream
	myfile.open("Arcs_Details.txt"); // Open file
	assert(myfile.is_open()); // Check file is open

	// Allocating memory for vector
	vector<int> Initial(5, 0);
	vector<vector<int> > Arc_Details(mNumberTransitions, Initial);

	// Input data from the file
	for (int i = 0; i < mNumberTransitions*6; i++)
	{
		//read_file >> Transition_Details[i][0] >> Transition_Details[i][1] >> Transition_Details[i][2] >> Transition_Details[i][3] >> Transition_Details[i][4];
	}

	//read_file.close();

	return Arc_Details;
}

//=======================================================================
// Function to populate the Places vector
//=======================================================================
void Petri_Net_Abstract::Create_Places_Vector()
{
	//-------------------------------------------------
	// This is a temp solution, in future Read_Places_Details_Input will do this automatically
	mNumberPlaces = 6;

	mpInitialMarking = new vector<unsigned int>[mNumberPlaces];

	mpInitialMarking->push_back(5);
	mpInitialMarking->push_back(0);
	mpInitialMarking->push_back(0);
	mpInitialMarking->push_back(0);
	mpInitialMarking->push_back(0);
	mpInitialMarking->push_back(0);
	//-------------------------------------------------

	mpPlaces = new vector<Place*>[mNumberPlaces];

	for (unsigned int i = 0; i < mNumberPlaces; i++)
	{
		mpPlaces->push_back(new Place("P" + to_string(i + 1), mpInitialMarking->at(i)));
	}
}

//=======================================================================
// Function to populate the Places vector
//=======================================================================
void Petri_Net_Abstract::Create_Transitions_Vector()
{
	// Reading in transition details 
	vector<vector<int> > Transition_Details;
	Transition_Details = Read_Transition_Details_Input();

	mNumberTransitions = Transition_Details.size();

	mpTransitions = new vector<Transition_Abstract*>[mNumberTransitions];

	for (unsigned i = 0; i < mNumberTransitions; i++)
	{
		// If it is a deterministic transition
		if (Transition_Details[i][1] == 1)
		{
			double tempTime;
			tempTime = 0.0; // Used until the input read function has been developed
			mpTransitions->push_back(new Transition_Deterministic("T" + to_string(i + 1), Transition_Details[i][2], Transition_Details[i][3], Transition_Details[i][4], tempTime));
		}
		// If it is a stochastic transition
		else if (Transition_Details[i][1] == 2)
		{
			double tempNumPar, tempParaVal;
			tempNumPar = 1;
			tempParaVal = 1.67;
			int tempDistribution = 1;

			char tempDistributionCode;
			if (tempDistribution == 1)
			{
				tempDistributionCode = 'E';
			}
			else if (tempDistribution == 2)
			{
				tempDistributionCode = 'W';
			}


			mpTransitions->push_back(new Transition_Stochastic("T" + to_string(i + 1), Transition_Details[i][2], Transition_Details[i][3], Transition_Details[i][4], tempDistributionCode, tempNumPar, { tempParaVal}));
		}
		// If it is a reset transition
		else if (Transition_Details[i][1] == 3)
		{
			mpTransitions->push_back(new Transition_Reset());
		}
		else
		{
			cout << "ERROR: The distribution code entered did not correspond to a Transition class" << endl;
		}
	}
}

//=======================================================================
// Function to assign arcs to the transitions
//=======================================================================
void Petri_Net_Abstract::Assign_Arcs()
{

}


