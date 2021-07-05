#include "CaerusPCH.h"
#include "CommandProvider.h"

#include "Command.h"

CommandProvider::~CommandProvider()
{
	for(auto* pCommand:m_pCommands)
	{
		delete pCommand;
	}
}
