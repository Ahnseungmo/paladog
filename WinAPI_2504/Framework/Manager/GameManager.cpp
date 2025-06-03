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
#include "Scenes/GameEndingScene.h"

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

	SCENE->AddScene("GameOver", new GameEndingScene(L"Resources/Textures/GameOver_BackGround.png"));
	SCENE->AddScene("GameClear", new GameEndingScene(L"Resources/Textures/GameClear_BackGround.png"));

	SCENE->ChangeScene("Battle");


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

	// ImGui 초기화
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 화면 그리기
	SCENE->Render();
	Environment::Get()->SetUIViewBuffer();
	SCENE->PostRender();

	// ImGui 렌더링
	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	// 게임 GUI 그리기
	SCENE->GUIRender();

	// ImGui 렌더링 종료
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
		MessageBox(NULL, L"ImGui Win32 초기화 실패", L"오류", MB_OK);
		return;
	}

	// DirectX 11 초기화
	if (!ImGui_ImplDX11_Init(DEVICE, DC))
	{
		MessageBox(NULL, L"ImGui DirectX 11 초기화 실패", L"오류", MB_OK);
		return;
	}

	// TextBox 폰트 초기화
	TextBox::InitializeFonts();

	// 싱글톤 초기화
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
