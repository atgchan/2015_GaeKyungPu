#include "pch.h"
#include "Phase_Pasteur.h"

Phase_Pasteur::Phase_Pasteur()
{
	_PhaseInfo = PHASE_PASTEUR;
}


Phase_Pasteur::~Phase_Pasteur()
{
}

void Phase_Pasteur::Tick()
{
	_NextPhaseInfo = PHASE_HARVEST;
	GM->getCurrentPlayerData()->setFood(0);
	GM->ChangePlayer();
}
