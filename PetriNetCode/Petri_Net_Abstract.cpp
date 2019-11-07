//=======================================================================
// Gareth Calvert - University of Nottingham
// Petri_Net_Abstract.cpp - Abstract Petri net class for deriving PNs
//=======================================================================
#include "pch.h"
#include "Petri_Net_Abstract.h"
//=======================================================================

//================================================
// Print Header
//================================================
void Petri_Net_Abstract::Print_Header()
{
	cout << "=========================================" << endl
		<< "PN Code - Petri Net Modelling" << endl
		<< "Gareth Calvert - University of Nottingham" << endl
		<< "=========================================" << endl;
}

//================================================
// Print Footer
//================================================
void Petri_Net_Abstract::Print_Footer()
{
	std::cout << "=========================================" << std::endl;
}

//================================================
// Print Iteration
//================================================
void Petri_Net_Abstract::Print_Iteration()
{
	Petri_Net_Abstract::Print_Footer();
	cout << "*** Simultation Iteration: " << mSimulationIteration << " ***" << std::endl;
	Petri_Net_Abstract::Print_Footer();
}

//================================================
// Print Transition Properties
//================================================
void Petri_Net_Abstract::Print_Transition_Properties()
{
	for (unsigned int i = 0; i < mNumberTransitions; i++)
	{
		mpTransitions->at(i)->Print_Transition_Properties();
	}

	Print_Footer();
}

//================================================
// Print Token Marking
//================================================
void Petri_Net_Abstract::Print_Token_Marking()
{
	cout << "The current marking of " << mPetriNetName << " is: " << endl;
	for (unsigned int i = 0; i < mNumberPlaces; i++)
	{
		mpPlaces->at(i)->Print_Place_Marking();
	}

	Print_Footer();
}

//================================================
// Print Token Probabilties from MC Marking
//================================================
void Petri_Net_Abstract::Print_MC_Marking()
{
	cout << "The expected markings after an MC Simulation of " << mPetriNetName << " are: " << endl;
	for (unsigned int i = 0; i < mNumberPlaces; i++)
	{
		cout << mpPlaces->at(i)->Get_Place_Name() << ": " << mpMC_Marking->at(i) << endl;
	}

	Print_Footer();
}

//================================================
// Update Token Marking
//================================================
void Petri_Net_Abstract::Update_Marking()
{
	mpCurrentMarking->clear();
	for (unsigned int i = 0; i < mNumberPlaces; i++)
	{
		mpCurrentMarking->push_back(mpPlaces->at(i)->Get_Place_Marking());
	} 
}

//=======================================================================
// Function read in Places Details Input File, returns a 2d vector 
// containing the Places properties.
//=======================================================================
vector<vector<int> > Petri_Net_Abstract::Read_Places_Details_Input()
{
	// Opening the file
	std::ifstream read_file("InputFiles/Places_Details_" + mPetriNetName +".txt");
	assert(read_file.is_open());

	// Determine length of the file
	double dummy_var1, dummy_var2;
	int no_entries = 0;
	while (!read_file.eof())
	{
		read_file >> dummy_var1 >> dummy_var2; 
		no_entries++;
	}

	//no_entries--; // Correcting to the appropriate value

	mNumberPlaces = no_entries;

	// Rewind to the beginning 
	read_file.clear();
	read_file.seekg(std::ios::beg);

	// Allocating memory for vector
	vector<int> Initial(2, 0);
	vector<vector<int> > Place_Details(no_entries, Initial);

	// Input data from the file
	for (int i = 0; i < no_entries; i++)
	{
		read_file >> Place_Details[i][0] >> Place_Details[i][1];
	}

	read_file.close();

	return Place_Details;

}

//=======================================================================
// Function read in Transitions Details Input File, returns a 2d vector 
// containing the transition properties.
//=======================================================================
vector<vector<double> > Petri_Net_Abstract::Read_Transition_Details_Input()
{
	//============================================================
	// Opening the file
	std::ifstream read_file("InputFiles/Transitions_Global_Details_" + mPetriNetName + ".txt");
	assert(read_file.is_open());

	// Determine length of the file
	double dummy_var1, dummy_var2, dummy_var3, dummy_var4, dummy_var5, dummy_var6, dummy_var7, dummy_var8, dummy_var9, dummy_var10, dummy_var11;
	int no_entries = 0;
	while (!read_file.eof())
	{
		read_file >> dummy_var1 >> dummy_var2 >> dummy_var3 >> dummy_var4 >> dummy_var5 >> dummy_var6 >> dummy_var7 >> dummy_var8 >> dummy_var9 >> dummy_var10 >> dummy_var11;
		no_entries++;
	}

	no_entries--; // Correcting to the appropriate value

	// Rewind to the beginning 
	read_file.clear();
	read_file.seekg(std::ios::beg);

	// Allocating memory for vector
	vector<double> Initial(11, 0);
	vector<vector<double> > Transition_Details(no_entries, Initial);

	// Input data from the file
	for (int i = 0; i < no_entries; i++)
	{
		read_file >> Transition_Details[i][0] >> Transition_Details[i][1] >> Transition_Details[i][2] >> Transition_Details[i][3] >> Transition_Details[i][4] >> Transition_Details[i][5] >> Transition_Details[i][6] >> Transition_Details[i][7] >> Transition_Details[i][8] >> Transition_Details[i][9] >> Transition_Details[i][10];
	}

	read_file.close();

	return Transition_Details;
}

//=======================================================================
// Function read in Transitions Details Input File, returns a 2d vector 
// containing the transition properties.
//=======================================================================
unsigned int** Petri_Net_Abstract::Read_Arcs_Input()
{
	//============================================================
	// Opening the file
	std::ifstream myfile; // Define Input Stream
	myfile.open("InputFiles/Arcs_Details_" + mPetriNetName + ".txt"); // Open file
	assert(myfile.is_open()); // Check file is open

	// Allocating memory for vector
	vector<int> Initial(5, 0); //***** I think this is included to cap the number of arcs. Need to confirm****
	vector<vector<int> > Arc_Details1(mNumberTransitions, Initial);

	string line;
	vector<string> InputString;
	while (getline(myfile, line))
	{
		InputString.push_back(line);
	}

	myfile.close(); // Close File
	
	int Size_InputString = InputString.size();

	assert(Size_InputString == mNumberTransitions*6);

	unsigned int** Arc_Details = new unsigned int* [mNumberTransitions*6];

	unsigned int Vector_Index = 0;
	int n, index;


	for (int i = 0; i < mNumberTransitions; i++)
	{
		
		Arc_Details[Vector_Index] = new unsigned int[int(mpTransitions->at(i)->Get_Number_Input_Arcs())+1];
		Arc_Details[Vector_Index+1] = new unsigned int[int(mpTransitions->at(i)->Get_Number_Input_Arcs())+1];
		Arc_Details[Vector_Index+2] = new unsigned int[int(mpTransitions->at(i)->Get_Number_Output_Arcs())+1];
		Arc_Details[Vector_Index+3] = new unsigned int[int(mpTransitions->at(i)->Get_Number_Output_Arcs())+1];
		Arc_Details[Vector_Index+4] = new unsigned int[int(mpTransitions->at(i)->Get_Number_Output_Arcs())+1];
		Arc_Details[Vector_Index+5] = new unsigned int[int(mpTransitions->at(i)->Get_Number_Output_Arcs())+1];
		
	
		// First Row is Input Arc Places
		stringstream stream;
		stream = stringstream(InputString.at(Vector_Index));
		index = 0;
		while (stream >> n) 
		{
			//cout << n << endl;
			Arc_Details[Vector_Index][index] = n;
			index++;
		}
		
		// Second Row is Input Arc Weights
		//stringstream* stream;
		stream = stringstream(InputString.at(Vector_Index+1));
		index = 0;
		int n;
		while (stream >> n)
		{
			Arc_Details[Vector_Index+1][index] = n;
			index++;
		}
		
		// Third Row is Output Arc Places
		stream = stringstream(InputString.at(Vector_Index+2));
		index = 0;
		while (stream >> n)
		{
			Arc_Details[Vector_Index+2][index] = n;
			index++;
		}

		// Fourth Row is Output Arc Weights
		stream = stringstream(InputString.at(Vector_Index+3));
		index = 0;
		while (stream >> n)
		{
			Arc_Details[Vector_Index+3][index] = n;
			index++;
		}

		// Fifth Row is Inhibitor Arc Places
		stream = stringstream(InputString.at(Vector_Index+4));
		index = 0;
		while (stream >> n)
		{
			Arc_Details[Vector_Index+4][index] = n;
			index++;
		}

		// Sixth Row is Inhibitor Arc Weights
		stream = stringstream(InputString.at(Vector_Index+5));
		index = 0;
		while (stream >> n)
		{
			Arc_Details[Vector_Index+5][index] = n;
			index++;
		}

		Vector_Index = Vector_Index + 6;
	
	}
	return Arc_Details;
}

//=======================================================================
// Function to populate the Places vector
//=======================================================================
void Petri_Net_Abstract::Create_Places_Vector()
{
	//-------------------------------------------------
	vector<vector<int> > temp_Places_Details;
	temp_Places_Details = Read_Places_Details_Input();

	mpInitialMarking = new vector<unsigned int>[mNumberPlaces];

	for (unsigned int i = 0; i < mNumberPlaces; i++)
	{
		mpInitialMarking->push_back(temp_Places_Details[i][1]);
	}
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
	vector<vector<double> > Transition_Details;
	Transition_Details = Read_Transition_Details_Input();

	mNumberTransitions = Transition_Details.size();

	mpTransitions = new vector<Transition_Abstract*>[mNumberTransitions];

	for (unsigned i = 0; i < mNumberTransitions; i++)
	{
		// If it is a deterministic transition
		if (Transition_Details[i][1] == 1)
		{
			assert(Transition_Details[i][10]>=0.0);
			mpTransitions->push_back(new Transition_Deterministic("T" + to_string(i + 1), Transition_Details[i][2], Transition_Details[i][3], Transition_Details[i][4], Transition_Details[i][10]));
		}
		// If it is a stochastic transition
		else if (Transition_Details[i][1] == 2)
		{
			double tempNumPar; vector<double> tempParameters[3];
			
			if (Transition_Details[i][6] == 1)
			{
				tempNumPar = 1;
				tempParameters->push_back(Transition_Details[i][7]);
			}
			else if (Transition_Details[i][6] == 2)
			{
				tempNumPar = 2;
				tempParameters->push_back(Transition_Details[i][7]);
				tempParameters->push_back(Transition_Details[i][8]);
			}

			else if (Transition_Details[i][6] == 3)
			{
				tempNumPar = 3;
				tempParameters->push_back(Transition_Details[i][7]);
				tempParameters->push_back(Transition_Details[i][8]);
				tempParameters->push_back(Transition_Details[i][9]);
			}
			else
			{
				cout << "ERROR: Number of Parameters does correspond to one, two or three" << endl;
				tempNumPar = 999;
			}

			char tempDistributionCode;
			if (Transition_Details[i][5] == 1)
			{
				tempDistributionCode = 'E';
			}
			else if (Transition_Details[i][5] == 2)
			{
				tempDistributionCode = 'W';
			}
			else
			{
				cout << "ERROR: Input Distribution Code is not configured in code" << endl;
			}


			mpTransitions->push_back(new Transition_Stochastic("T" + to_string(i + 1), Transition_Details[i][2], Transition_Details[i][3], Transition_Details[i][4], tempDistributionCode, tempNumPar, *tempParameters));

			//delete[] tempParameters;
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
	// Reading in transition details 
	unsigned int** Arc_Details;
	Arc_Details = Read_Arcs_Input();

	//cout << Arc_Details[0][1] << endl;

	int inputIndex, inputWeightIndex, outputIndex, outputWeightIndex, inhibIndex, inhibWeightsIndex;

	// Loop to go through each transition and assign the appropriate arcs
	for (unsigned int i = 0; i<mNumberTransitions; i++)
	{
		inputIndex = ((i*6)+ 1)-1; 
		inputWeightIndex = ((i*6)+ 2)-1;
		outputIndex = ((i*6)+3)-1;
		outputWeightIndex = ((i*6)+4)-1;
		inhibIndex = ((i*6)+5)-1;
		inhibWeightsIndex = ((i*6)+6)-1;

		// Setting input arcs
		for (unsigned int a = 0; a<mpTransitions->at(i)->Get_Number_Input_Arcs(); a++)
		{
			mpTransitions->at(i)->Set_Input_Arc(mpPlaces->at(Arc_Details[inputIndex][a+1]-1), Arc_Details[inputWeightIndex][a+1]);
		}

		// Setting output arcs
		for (unsigned int a = 0; a<mpTransitions->at(i)->Get_Number_Output_Arcs(); a++)
		{
			mpTransitions->at(i)->Set_Output_Arc(mpPlaces->at(Arc_Details[outputIndex][a+1]-1), Arc_Details[outputWeightIndex][a + 1]);
		}

		// Setting inhibitor arcs
		for (unsigned int a = 0; a<mpTransitions->at(i)->Get_Number_Inhibitor_Arcs(); a++)
		{
			mpTransitions->at(i)->Set_Inhibitor_Arc(mpPlaces->at(Arc_Details[inhibIndex][a+1]-1), Arc_Details[inhibWeightsIndex][a+1]);
		}

	}

}

//=======================================================================
// Function to conduct once execution of a continuous simulation
//=======================================================================
void Petri_Net_Abstract::Continuous_Simulation()
{
	// Setting up simulation
	mContinueSimulation = true;
	mCurrentGlobalTime = mInitialTime;
	mEnabledTransitions.clear();
	int NumEnabled;
	bool temp;

	// While loop to break out of
	while (mContinueSimulation == true)
	{
		// Clear vector of enabled transitions for next iteration
		mEnabledTransitions.clear();
		NumEnabled = 0;

		// Check for enabled transitions
		for (int i = 0; i < mNumberTransitions; i++)
		{
			mpTransitions->at(i)->Transition_Enabled_Check(mCurrentGlobalTime);
			temp = mpTransitions->at(i)->Get_Enabled_Status();
			
			if (temp == true)
			{
				mEnabledTransitions.push_back(i);
				NumEnabled++;
			}
		}
	
		// If nothing is enabled, then net is stationary
		if (NumEnabled == 0)
		{
			mContinueSimulation = false;
			Update_Marking();
		}
			
		// If time has elapsed to final time, terminate simualtion
		if (mCurrentGlobalTime >= mFinalTime)
		{
			mContinueSimulation = false;
			Update_Marking();
		}

		// Determining Enabled Transition with Shortest Remaining Firing Delay
		// If tied, transition with lowest index is selected
		// Boolean Check, to save unnecessary computations
		if (mContinueSimulation == true)
		{
			mNumberShortestEnable = 1;
			mShortestEnableIndex = 0;
			mAllShortestEnable.push_back(mEnabledTransitions.at(0));
			// For loop to sort enabled transitions by firing time
			for (int i = 1; i< NumEnabled; i++)
			{
				// Checking if the firing has the shorter firing time than current shortest
				if (mpTransitions->at(mEnabledTransitions.at(mShortestEnableIndex))->Get_Remaining_Delay() > mpTransitions->at(mEnabledTransitions.at(i))->Get_Remaining_Delay())
				{
					mShortestEnableIndex = i;
					mNumberShortestEnable = 1;
					mAllShortestEnable.clear();
					mAllShortestEnable.push_back(mEnabledTransitions.at(mShortestEnableIndex));
				}
					
				// Checking if the firing has the same firing time as shortest
				if (mpTransitions->at(mEnabledTransitions.at(mShortestEnableIndex))->Get_Remaining_Delay() == mpTransitions->at(mEnabledTransitions.at(i))->Get_Remaining_Delay() && mShortestEnableIndex != i)
				{
					cout << "Note: Transition Firing Tie Break" << endl;
					//cout << mpTransitions->at(mEnabledTransitions.at(mShortestEnableIndex))->Get_Transition_Name() << endl;
					mNumberShortestEnable++;
					mAllShortestEnable.push_back(mEnabledTransitions.at(mShortestEnableIndex));
				}
			}
		}
			
		if (mContinueSimulation == true)
		{
			// Check that shortest firing time doesn't occur after final time of simulation
			if (mpTransitions->at(mEnabledTransitions.at(mShortestEnableIndex))->Get_Remaining_Delay() + mCurrentGlobalTime > mFinalTime)
			{
				//If it does, stop simulating
				mContinueSimulation = false;
				mCurrentGlobalTime = mFinalTime;
				Update_Marking();
			}
		}

		if (mContinueSimulation == true)
		{
			// Fire the enabled transition with the shortest firing delay first. 
			// If there are multiple enabled with the same shortest time.
			// The first fires then the remaining are re-checked and then also fired.
			
			// Update Global Time
			mCurrentGlobalTime = mCurrentGlobalTime + mpTransitions->at(mEnabledTransitions.at(0))->Get_Remaining_Delay();
			mpTransitions->at(mEnabledTransitions.at(mAllShortestEnable.at(0)))->Transition_Fire();

			if (mNumberShortestEnable > 1)
			{
				for (int i = 1; i < mNumberShortestEnable; i++)
				{
					mpTransitions->at(mEnabledTransitions.at(mAllShortestEnable.at(i)))->Transition_Enabled_Check(mCurrentGlobalTime);
					temp = mpTransitions->at(mEnabledTransitions.at(mAllShortestEnable.at(i)))->Get_Enabled_Status();

					if (temp == true)
					{
						mpTransitions->at(mEnabledTransitions.at(mAllShortestEnable.at(i)))->Transition_Fire();
					}
				}
			}
			
		//Update Current Marking
		Update_Marking();

		// Clear vector of enabled transitions for next iteration
		mEnabledTransitions.clear();
		}
	}
}

//=======================================================================
// Continuous Simualtion with a marking record and predefined intervals
//=======================================================================
void Petri_Net_Abstract::Continuous_Simulation_Marking()
{

}

//=======================================================================
// Monte Carlo Continuous Simulation
//=======================================================================
void Petri_Net_Abstract::Continuous_Simulation_MC(int NumberSimulations)
{
	mpMC_Marking->clear();

	for (int j = 0; j < mNumberPlaces; j++)
	{
		mpMC_Marking->push_back(0.0);
	}

	for (int i = 0; i < NumberSimulations; i++)
	{
		
		Reset_PN();
		Continuous_Simulation();

		

		for (int j = 0; j < mNumberPlaces; j++)
		{
			mpMC_Marking->at(j) = mpMC_Marking->at(j) + mpCurrentMarking->at(j);
		}

	}

	for (int j = 0; j < mNumberPlaces; j++)
	{
		mpMC_Marking->at(j) = mpMC_Marking->at(j)/NumberSimulations;
	}

	Print_MC_Marking();

}

//=======================================================================
// Monte Carlo Continuous Simulation, with a marking record at predefined
// time intervals
//=======================================================================
void Petri_Net_Abstract::Continuous_Simulation_Marking_MC(int NumberSimulations)
{

}

//=======================================================================
// Function to evaluate fragments of code, for the purposes of debugging
//=======================================================================
void Petri_Net_Abstract::Test_Simulation()
{

}

//=======================================================================
// Reset PN - Resets Places to Initial Marking and Resamples Transition 
// firing delays.
//=======================================================================
void Petri_Net_Abstract::Reset_PN()
{
	// Reset Places to Initial Marking
	for (unsigned int i = 0; i < mNumberPlaces; i++)
	{
		mpPlaces->at(i)->Reset_To_Initial_Marking();
	}

	// Resample firing times in transitions
	for (unsigned int i = 0; i < mNumberTransitions; i++)
	{
		mpTransitions->at(i)->Transition_Resample();
	}

}

//=======================================================================
// Reset PN - Resets Places to Initial Marking and Resamples Transition 
// firing delays.
//=======================================================================
void Petri_Net_Abstract::Change_Initial_Marking(vector<unsigned int> NewInitialMarking)
{
	// Checking that the Marking vector corresponds to the number of places in the net
	int temp = NewInitialMarking.size();
	assert(temp = mNumberPlaces);

	// Copying over new initial marking to class
	*mpInitialMarking = NewInitialMarking;

	// Updating the initial marking of each place
	for (unsigned int i = 0; i < mNumberPlaces; i++)
	{
		mpPlaces->at(i)->Change_Initial_Marking(mpInitialMarking->at(i));
	}
}