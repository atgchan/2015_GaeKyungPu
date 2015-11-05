#include "pch.h"
#include "Phase_Pasteur.h"

Phase_Pasteur::Phase_Pasteur()
{
}


Phase_Pasteur::~Phase_Pasteur()
{
}

void Phase_Pasteur::Tick()
{
	nextPhase = PHASE_HARVEST;
	GM->ChangePlayer();
}
