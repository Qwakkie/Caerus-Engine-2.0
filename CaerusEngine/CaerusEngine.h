#pragma once
struct SDL_Window;

struct GameSettings
{
	int WindowWidth;
	int WindowHeight;
};

class CaerusEngine final
{
public:
	void Initialize();
	void LoadGame() const;
	void Cleanup();
	void Run();
	const GameSettings& GetGameSettings()const { return m_Settings; }
private:
	SDL_Window* m_Window{};
	const GameSettings m_Settings{ 640, 480 };
	bool m_IsInitialized{};
};