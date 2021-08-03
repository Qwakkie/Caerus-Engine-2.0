#include "MenuUpCommand.h"


#include "GameObject.h"
#include "MenuSelectCommand.h"
#include "TransformComponent.h"

MenuUpCommand::MenuUpCommand(MenuSelectCommand* pCommand, int maxModes)
	:m_pSelectCommand(pCommand)
	,m_MaxGameModes(maxModes)
{
}

void MenuUpCommand::Execute(GameObject* pActor)
{
	int selected{ m_pSelectCommand->GetSelected() };
	--selected;
	if (selected < 0)
		selected = m_MaxGameModes - 1;
	m_pSelectCommand->SetSelected(selected);

	const float travelDistance{ 30.f };

	if (selected == m_MaxGameModes - 1)
	{
		pActor->GetTransform()->Translate({ 0, travelDistance * static_cast<float>(m_MaxGameModes - 1), 0 });
		return;
	}

	pActor->GetTransform()->Translate({ 0, -travelDistance, 0 });
}
