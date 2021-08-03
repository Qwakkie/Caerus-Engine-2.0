#pragma once

class GameModeLoader
{
public:
	void LoadGamemode(int gamemode);
	void LoadStartMenu();
private:
	void LoadSingleplayer();
	void LoadMultiplayer();
	void LoadVersus();
};

