#include "Framework.h"

//#include "Scenes/TutorialScene.h"
#include "Scenes/ShootingScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/TextureScene.h"
#include "Scenes/AnimationScene.h"
#include "Scenes/LobbyScene.h"
#include "Scenes/IntroScene.h"
#include "Scenes/UnitScene.h"
#include "Scenes/GotchaScene.h"
#include "Scenes/BattleScene.h"
GameManager::GameManager()
{
	Create();
		
	//SCENE->AddScene("Game", new TutorialScene());	
	//SCENE->AddScene("Game", new ShootingScene());
	//SCENE->AddScene("Game", new CollisionScene());
	//SCENE->AddScene("Game", new AnimationScene());
	//SCENE->AddScene("Intro", new IntroScene());
	//SCENE->AddScene("Lobby", new LobbyScene());


	SCENE->AddScene("Intro", new IntroScene());
	SCENE->AddScene("Lobby", new LobbyScene());
	SCENE->AddScene("Unit", new UnitScene());
	SCENE->AddScene("Gotcha", new GotchaScene());

	SCENE->AddScene("Battle", new BattleScene());

	SCENE->ChangeScene("Intro");
}

GameManager::~GameManager()
{
	Release();
}

void GameManager::Update()
{
	Timer::Get()->Update();
	Input::Get()->Update();

	Environment::Get()->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void GameManager::Render()
{
	Device::Get()->Clear();	

	SCENE->Render();

	Environment::Get()->SetUIViewBuffer();
	SCENE->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	SCENE->GUIRender();	

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Timer::Get();
	Input::Get();

	Device::Get();

	SceneManager::Get();

	Environment::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Release()
{
	Timer::Delete();
	Input::Delete();

	Device::Delete();
	Shader::Delete();
	Texture::Delete();

	SceneManager::Delete();

	Environment::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}
