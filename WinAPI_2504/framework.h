﻿#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

#define CENTER_X (SCREEN_WIDTH >> 1)
#define CENTER_Y (SCREEN_HEIGHT >> 1)

#define CENTER Vector2(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f)

#define PI 3.141592f

#define DELTA Timer::Get()->GetElapsedTime()
#define SCENE SceneManager::Get()

#define DEVICE Device::Get()->GetDevice()
#define DC Device::Get()->GetDeviceContext()

#define CAM Environment::Get()->GetMainCamera()

#include <windows.h>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>
#include <vector>
#include <functional>
#include <algorithm>
#include <fstream>
#include <assert.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//ImGui
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#pragma comment(lib, "ImGui.lib")

//DirectXTex
#include <DirectXTex/DirectXTex.h>

#pragma comment(lib, "DirectXTex.lib")

using namespace std;
using namespace DirectX;

typedef XMFLOAT4 Float4;
typedef XMFLOAT3 Float3;
typedef XMFLOAT2 Float2;
typedef XMMATRIX Matrix;
typedef XMVECTOR Vector4;
typedef XMFLOAT4X4 Float4x4;


#include "Framework/Utilities/Utility.h"
#include "Framework/Utilities/Singleton.h"
#include "Framework/Utilities/Timer.h"
#include "Framework/Utilities/Input.h"
#include "Framework/Utilities/tinyxml2.h"

#include "Framework/Math/Vector2.h"
#include "Framework/Math/Transform.h"
#include "Framework/Math/GameMath.h"

#include "Framework/Device/Device.h"

#include "Framework/Shader/Shader.h"
#include "Framework/Shader/VertexShader.h"
#include "Framework/Shader/PixelShader.h"

#include "Framework/Buffer/VertexLayouts.h"
#include "Framework/Buffer/VertexBuffer.h"
#include "Framework/Buffer/IndexBuffer.h"
#include "Framework/Buffer/ConstBuffer.h"
#include "Framework/Buffer/GlobalBffer.h"

#include "Framework/Render/Texture.h"
#include "Framework/Render/Mesh.h"
#include "Framework/Render/Material.h"
#include "Framework/Render/Frame.h"
#include "Framework/Render/Clip.h"

#include "Framework/Environment/Camera.h"
#include "Framework/Environment/Environment.h"

#include "Objects/Basic/GameObject.h"
#include "Objects/Basic/Quad.h"

#include "Objects/Collider/Collider.h"
#include "Objects/Collider/CircleCollider.h"
#include "Objects/Collider/RectCollider.h"

#include "Objects/Manger/DataManager.h"
#include "Objects/Manger/EventManager.h"

#include "Objects/Shooting/Plane.h"
#include "Objects/Shooting/Bullet.h"

#include "Objects/Flappy/Bird.h"
#include "Objects/Character/Chest.h"
#include "Objects/Character/Cookie.h"

#include "Objects/Paladog/BasicUnit/UnitStat.h"
#include "Objects/Paladog/BasicUnit/HealthBar.h"
#include "Objects/Paladog/BasicUnit/CharacterAnimation.h"
#include "Objects/Paladog/BasicUnit/Character.h"

#include "Objects/Paladog/Ally/Ally_Knight.h"
#include "Objects/Paladog/Ally/Allow.h"
#include "Objects/Paladog/Ally/Ally_Archer.h"
#include "Objects/Paladog/Ally/Ally_Lancer.h"
#include "Objects/Paladog/Ally/Ally_Tanker.h"
#include "Objects/Paladog/Ally/Ally_Elite.h"
#include "Objects/Paladog/Ally/Ally_Boxer.h"
#include "Objects/Paladog/Ally/Bomb.h"
#include "Objects/Paladog/Ally/Ally_Bomber.h"

#include "Objects/Paladog/Enemy/Enemy_Frankenstein.h"
#include "Objects/Paladog/Enemy/Enemy_LadySkeleton.h"
#include "Objects/Paladog/Enemy/Enemy_Witch.h"
#include "Objects/Paladog/Enemy/Enemy_Zombie.h"
#include "Objects/Paladog/Enemy/Enemy_Boss.h"
#include "Objects/Paladog/Enemy/Enemy_Castle.h"
#include "Objects/Paladog/Enemy/Enemy_IronMan.h"
#include "Objects/Paladog/Enemy/Enemy_Warrior.h"

#include "Objects/Paladog/Manager/EnemyManager.h"
#include "Objects/Paladog/Manager/AllyManager.h"

#include "Objects/Paladog/Player/Punch.h"
#include "Objects/Paladog/Player/Paladog.h"


#include "Scenes/Scene.h"
#include "Framework/Manager/SceneManager.h"
#include "Framework/Manager/GameManager.h"

#include "Objects/UI/GaugeBar.h"
#include "Objects/UI/Button.h"
#include "Objects/UI/CoolTimeButton.h"
#include "Objects/UI/Panel.h"
#include "Objects/UI/Background.h"

#include "Objects/UI/TextBox.h"
#include "Objects/UI/SpawnBar.h"
#include "Objects/UI/UnitPanel.h"
#include "Objects/UI/UnitDataPanel.h"




extern HWND hWnd;
extern Vector2 mousePos;