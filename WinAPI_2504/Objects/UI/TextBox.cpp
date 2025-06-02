#include "Framework.h"
#include <string>
#include <codecvt>
#include <locale>
#include <imgui.h>

// 정적 멤버 초기화
map<string, ImFont*> TextBox::fontMap;
bool TextBox::fontsInitialized = false;

TextBox::TextBox(Vector2 pos, Vector2 size, const char* text)
    : pos(pos), size(size)
{
    SetLocalPosition(pos);
    strncpy_s(textBuffer, text, sizeof(textBuffer) - 1);
}

TextBox::~TextBox()
{
}

void TextBox::InitializeFonts()
{
    if (fontsInitialized) return;

    ImGuiIO& io = ImGui::GetIO();
    
    // 기본 폰트 추가
    fontMap["Default"] = io.Fonts->AddFontDefault();
    
    // 나눔바른고딕 폰트 추가
    fontMap["Resources/Fonts/NanumBarunGothic.ttf"] = io.Fonts->AddFontFromFileTTF("Resources/Fonts/NanumBarunGothic.ttf", 20.0f);
    fontMap["C:/Windows/Fonts/malgun.ttf"] = io.Fonts->AddFontFromFileTTF("C:/Windows/Fonts/malgun.ttf", 20.0f);
    
    // 폰트 아틀라스 빌드
    io.Fonts->Build();
    
    // DirectX 텍스처 업데이트
    if (DEVICE && DC)
    {
        ImGui_ImplDX11_InvalidateDeviceObjects();
        ImGui_ImplDX11_CreateDeviceObjects();
    }
    
    fontsInitialized = true;
}

void TextBox::ReleaseFonts()
{
    fontMap.clear();
    fontsInitialized = false;
}

void TextBox::Render()
{
    if (!ImGui::GetCurrentContext())
        return;

    // this 포인터의 주소값을 문자열로 변환하여 윈도우 이름 생성
    std::string windowName = "TextBox_" + std::to_string(reinterpret_cast<uintptr_t>(this));

    // 부모의 위치를 포함한 최종 위치 계산
    Vector2 finalPos = GetGlobalPosition();
    
    // 좌표계 변환 (게임 좌표계 -> ImGui 좌표계)
    // y좌표를 반전시켜 ImGui 좌표계로 변환
    ImVec2 imguiPos(finalPos.x, SCREEN_HEIGHT - finalPos.y);

    // 윈도우 위치와 크기 설정
    ImGui::SetNextWindowPos(imguiPos);
    ImGui::SetNextWindowSize(ImVec2(size.x, size.y));
    
    // 윈도우 플래그 설정
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | 
                                  ImGuiWindowFlags_NoResize | 
                                  ImGuiWindowFlags_NoMove |
                                  ImGuiWindowFlags_NoBackground;
    
    // 윈도우 생성
    bool open = true;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
    
    // 텍스트 박스 배경 투명하게 설정
    ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0, 0, 0, 0));
    ImGui::PushStyleColor(ImGuiCol_TextSelectedBg, ImVec4(0.2f, 0.2f, 0.2f, 0.3f));
    
    if (ImGui::Begin(windowName.c_str(), &open, window_flags))
    {
        // 폰트 설정
        auto it = fontMap.find(fontName);
        if (it != fontMap.end()) {
            ImGui::PushFont(it->second);
        }
        
        // 입력 텍스트 위젯
        ImGui::PushItemWidth(size.x - 20);
        
        // 텍스트 영역의 크기를 윈도우 크기에 맞게 조정
        ImVec2 textSize = ImVec2(size.x - 20, size.y - 10);
        
        // 미리보기 텍스트 (자동 줄바꿈)
        ImGui::TextWrapped("%s", textBuffer);
        
        ImGui::PopItemWidth();
        
        // 폰트 복원
        if (it != fontMap.end()) {
            ImGui::PopFont();
        }
    }
    ImGui::End();
    
    ImGui::PopStyleColor(2);  // 스타일 색상 복원
    ImGui::PopStyleVar(2);    // 스타일 변수 복원
}
