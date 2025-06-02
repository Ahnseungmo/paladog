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

	// ImGui 프레임 시작
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 씬 렌더링
	SCENE->Render();
	Environment::Get()->SetUIViewBuffer();
	SCENE->PostRender();

	// ImGui 렌더링
	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	// 씬의 GUI 렌더링
	SCENE->GUIRender();

	// ImGui 렌더링 완료
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	// ImGui 초기화
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // 키보드 네비게이션 활성화

	// 스타일 설정
	ImGui::StyleColorsDark();

	// Win32 초기화
	if (!ImGui_ImplWin32_Init(hWnd))
	{
		MessageBox(NULL, L"ImGui Win32 초기화 실패", L"에러", MB_OK);
		return;
	}

	// DirectX 11 초기화
	if (!ImGui_ImplDX11_Init(DEVICE, DC))
	{
		MessageBox(NULL, L"ImGui DirectX 11 초기화 실패", L"에러", MB_OK);
		return;
	}

	// 나머지 매니저 초기화
	Timer::Get();
	Input::Get();
	Device::Get();
	SceneManager::Get();
	Environment::Get();
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
