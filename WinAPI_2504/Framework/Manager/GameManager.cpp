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

	// ImGui ������ ����
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// �� ������
	SCENE->Render();
	Environment::Get()->SetUIViewBuffer();
	SCENE->PostRender();

	// ImGui ������
	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	// ���� GUI ������
	SCENE->GUIRender();

	// ImGui ������ �Ϸ�
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	// ImGui �ʱ�ȭ
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Ű���� �׺���̼� Ȱ��ȭ

	// ��Ÿ�� ����
	ImGui::StyleColorsDark();

	// Win32 �ʱ�ȭ
	if (!ImGui_ImplWin32_Init(hWnd))
	{
		MessageBox(NULL, L"ImGui Win32 �ʱ�ȭ ����", L"����", MB_OK);
		return;
	}

	// DirectX 11 �ʱ�ȭ
	if (!ImGui_ImplDX11_Init(DEVICE, DC))
	{
		MessageBox(NULL, L"ImGui DirectX 11 �ʱ�ȭ ����", L"����", MB_OK);
		return;
	}

	// ������ �Ŵ��� �ʱ�ȭ
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
