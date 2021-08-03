#include "MenuDownCommand.h"


#include "GameObject.h"
#include "MenuSelectCommand.h"
#include "TransformComponent.h"

MenuDownCommand::MenuDownCommand(MenuSelectCommand* pCommand, int maxModesAmount)
	: m_pSelectCommand(pCommand)
	,m_MaxGameModes(maxModesAmount)
{
}

void MenuDownCommand::Execute(GameObject* pActor)
{
	int selected{ m_pSelectCommand->GetSelected() };
	++selected;
	if (selected == m_MaxGameModes)
		selected = 0;
	m_pSelectCommand->SetSelected(selected);
	
	const float travelDistance{30.f};

	if(selected == 0)
	{
		pActor->GetTransform()->Translate({ 0, -travelDistance * static_cast<float>(m_MaxGameModes - 1), 0 });
		return;
	}

	pActor->GetTransform()->Translate({ 0, travelDistance, 0 });
}
