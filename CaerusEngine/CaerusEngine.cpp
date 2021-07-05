#include "CaerusPCH.h"
#include "CaerusEngine.h"
#include <chrono>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

using namespace std;
using namespace std::chrono;

void CaerusEngine::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		m_Settings.WindowWidth,
		m_Settings.WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	m_IsInitialized = true;
	Renderer::GetInstance().Init(m_Window);
	ResourceManager::GetInstance().Init();
}

/**
 * Code constructing the scene world starts here
 */
void CaerusEngine::LoadGame() const
{
	if (!m_IsInitialized)
		throw std::runtime_error(std::string("Engine has not been initialized yet"));
}

void CaerusEngine::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void CaerusEngine::Run()
{
	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = high_resolution_clock::now();

		while (doContinue)  // NOLINT(bugprone-infinite-loop)
		{
			const auto currentTime = high_resolution_clock::now();
			const float deltaTime = duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();
		}
	}

	Cleanup();
}
