//=======================================================================
// Gareth Calvert - University of Nottingham
// Transition_Stochastic.cpp - Stochastic Transition class, inherits 
// functions from the Transition_Abstract class
//=======================================================================
#include "pch.h"
#include "Transition_DC.h"
using namespace std;
//=======================================================================


//=======================================================================
// Specialised Constructor
//=======================================================================
Transition_DC::Transition_DC(string TransitionName, string PetriNetName, unsigned int NumberIn, unsigned NumberOut, unsigned NumberInhibitorArcs, unsigned int NumberCausalArcs, unsigned int NumberMarkingPermutations, double TimeStep)
{
	// Transition Properties
	mTransitionName = TransitionName;
	mNumberInputArcs = NumberIn;
	mNumberOutputArcs = NumberOut;
	mNumberInhibitorArcs = NumberInhibitorArcs;
	mNumberCausalArcs = NumberCausalArcs;
	mNumberMarkingPermutations = NumberMarkingPermutations;
	mTransitionTimeStep = TimeStep;
	mTransitionDelay = mTransitionTimeStep;
	mNumberTransitionFires = 0;
	mTransitionCode = 4; // Code is 4 for DC transitions

	// Initalising Arrays 
	mpInputPlaces = new vector<Place*>[mNumberInputArcs];
	mpOutputPlaces = new vector<Place*>[mNumberOutputArcs];
	mpInhibitorPlaces = new vector<Place*>[mNumberInhibitorArcs];
	mpCausalPlaces = new vector<Place*>[mNumberCausalArcs];
	mpInputWeights = new vector<unsigned int>[mNumberInputArcs];
	mpOutputWeights = new vector<unsigned int>[mNumberOutputArcs];
	mpInhibitorWeights = new vector<unsigned int>[mNumberInhibitorArcs];


	// Causal Arcs Markings and probability values
	mpCausalStateMarkings = new vector<unsigned int>[mNumberCausalArcs];
	mpConditionalProbabilityValues = new vector<double>[mNumberMarkingPermutations];
	mpCausalStatePermutations = new vector<vector<unsigned int>>(mNumberMarkingPermutations, vector<unsigned int>(mNumberCausalArcs, 1));

	// Initialise vector and matrix to store input file contents

	//vector<double> tempParameters;
	//tempParameters.clear();
	//cout << Transition_Details[i][8] << endl;
	for (int k = 0; k < mNumberMarkingPermutations; k++)
	{
		mpConditionalProbabilityValues->push_back(0.0);
		//tempParameters.push_back(0);
	}

	for (int k = 0; k < mNumberCausalArcs; k++)
	{
		mpCausalStateMarkings->push_back(0.0);
		//tempParameters.push_back(0);
	}

	//vector<unsigned int> tempVector;
	//tempVector.clear();
	// Number of Causal Arcs
	//for (int k = 0; k < mNumberCausalArcs; k++)
	{
		//tempVector.push_back(0);
	}

	//vector<vector<unsigned int>> tempMatrixMarking;
	//tempMatrixMarking.clear();

	// Number of Markings
	//for (int l = 0; l < mNumberMarkingPermutations; l++)
	{
		//mpCausalStatePermutations->at(l).at(1) = 1;//.push_back(tempVector);
		//tempMatrixMarking.push_back(tempVector);
	}

	//=================================
	// Read in DC Transition Input File
	//=================================
	// Opening the file
	std::ifstream myfile; // Define Input Stream
	myfile.open("InputFiles/" + PetriNetName + "_" + mTransitionName + ".txt"); // Open file
	assert(myfile.is_open()); // Check file is open

	string line;
	vector<string> InputString;
	while (getline(myfile, line))
	{
		InputString.push_back(line);
	}

	myfile.close(); // Close File

	int Size_InputString = InputString.size();

	assert(Size_InputString == mNumberMarkingPermutations +1); // Assert that the size of input string vector is the number of markings plus one

	int Vector_Index = 0;
	int n, index;
			

	// First n rows are the markings
	for (int i = 0; i < mNumberMarkingPermutations; i++)
	{

		// First Row is Input Arc Places
		stringstream stream;
		stream = stringstream(InputString.at(i));
		index = 0;
		while (stream >> n)
		{
			mpCausalStatePermutations->at(i).at(index) = n;
			//tempMatrixMarking[i][index] = n;
			index++;
		}
	}

	// Last row is the parameter for each marking
	stringstream stream;
	stream = stringstream(InputString.at(mNumberMarkingPermutations));
	index = 0;
	double m;
	while (stream >> m)
	{
		mpConditionalProbabilityValues->at(index) = m;
		//tempParameters[index] = m;
		index++;
	}

	mFireTest = false;
}

//=======================================================================
// Destructor
//=======================================================================
Transition_DC::~Transition_DC()
{
	delete[] mpInputPlaces;
	delete[] mpOutputPlaces;
	delete[] mpInhibitorPlaces;
	delete[] mpInputWeights;
	delete[] mpOutputWeights;
	delete[] mpInhibitorWeights;

}

//=======================================================================
// Function samples a new time from the specified distribution for the 
// transition
//=======================================================================
void Transition_DC::Transition_Resample()
{
	mTransitionEnabled = false;
	mTransitionEnabled = false;
	mCumulativeTime = 0.0; // Reset cumulative time
	mRemainingDelay = mTransitionDelay;
	mCumulativeTime = 0.0; // Reset cumulative time
	mRemainingDelay = mTransitionDelay;
}

//=======================================================================
// Function samples a new time from the specified distribution for the 
// transition
//=======================================================================
void Transition_DC::Transition_Fire()
{
	// Reset Fire Test
	mFireTest = false;

	// Check what the markings of the causal arcs are
	for (int i = 0; i < mNumberCausalArcs; i++)
	{
		mpCausalStateMarkings->at(i) = mpCausalPlaces->at(i)->Get_Place_Marking();
	}

	bool MarkingDetermined = false;
	int index = 0;
	int MarkingPermutationIndex = 0;
	double SampleProbability;
	double RandomSample;


	// Determining the marking of the causal places
	while (MarkingDetermined == false && index < mNumberMarkingPermutations)
	{
		if (*mpCausalStateMarkings == mpCausalStatePermutations->at(index))
		{
			MarkingPermutationIndex = index;
			MarkingDetermined = true;
		}

		index++;
	}

	if (MarkingDetermined == false)
	{
		cout << "\n Marking not determined for causal places, check to see if sufficient marking permutations are being included.";
	}

	// Determine the correct probability to use given the causal markings
	SampleProbability = mpConditionalProbabilityValues->at(MarkingPermutationIndex);

	// Sample a random number to determine whether the transition should fire in this time step
	RandomSample = Get_Uniform_Distributed_Random_Number();
	if (RandomSample > SampleProbability)
	{
		mFireTest = true;
	}
	else
	{
		mTransitionEnabled = false;
		mCumulativeTime = 0.0; // Reset cumulative time
		mRemainingDelay = mTransitionDelay;
	}

	// If the sampled probability results in a positive result, fire the transition as normal
	if (mFireTest == true)
	{
		//cout << "Transition Fire" <<  endl;
		// Remove Tokens from Input Places
			for (unsigned int i = 0; i < mNumberInputArcs; i++)
			{
				mpInputPlaces->at(i)->Remove_Tokens(mpInputWeights->at(i));
			}

			// Add Tokens to Output Places
			for (unsigned int i = 0; i < mNumberOutputArcs; i++)
			{
				mpOutputPlaces->at(i)->Add_Tokens(mpOutputWeights->at(i));
			}

			mTransitionEnabled = false;
			mCumulativeTime = 0.0; // Reset cumulative time
			mRemainingDelay = mTransitionDelay;
			mNumberTransitionFires++;
	}

}

//=======================================================================
// Function included here, so that each unique transition type can print
// transition properties out
//=======================================================================
void Transition_DC::Transition_Type_Properties()
{
	cout << "Dynamic Conditional Transition" << endl;
	cout << "Transition Time Step: " + to_string(mTransitionTimeStep) << endl;

	cout << "Causal Arcs: ";

	string temp;
	for (unsigned int i = 0; i < mNumberCausalArcs; i++)
	{
		temp = mpCausalPlaces->at(i)->Get_Place_Name() + " ";
		cout << temp;
	}

	cout << endl;


}