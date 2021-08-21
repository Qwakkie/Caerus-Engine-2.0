#pragma once

class GameModeLoader
{
public:
	static void LoadGamemode(int gamemode);
	static void LoadStartMenu();
	static void LoadGameOver();
private:
	static void LoadSingleplayer();
	static void LoadMultiplayer();
	static void LoadVersus();
};

