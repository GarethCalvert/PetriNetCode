#pragma once
#include "Transition_Abstract.h"
#include "Transition_Stochastic.h"
#include "Transition_Deterministic.h"

struct Net;

void Net_Design(unsigned int Number_Stochastic, unsigned int Number_Deterministic, unsigned int Number_Reset);