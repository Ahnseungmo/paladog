#include "Framework.h"
#include <string>
#include <codecvt>
#include <locale>
#include <imgui.h>

TextBox::TextBox(Vector2 pos, Vector2 size, wstring text)
    : pos(pos), size(size), text(text)
{
    WStringToCharArray();
}

TextBox::~TextBox()
{
}

void TextBox::Render()
{
    if (!ImGui::GetCurrentContext())
        return;

    static int windowId = 0;
    std::string windowName = "TextBox_" + std::to_string(windowId++);

    // 윈도우 위치와 크기 설정
    ImGui::SetNextWindowPos(ImVec2(pos.x, pos.y));
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
        // 입력 텍스트 위젯
        ImGui::PushItemWidth(size.x - 20);
        
        // 텍스트 영역의 크기를 윈도우 크기에 맞게 조정
        ImVec2 textSize = ImVec2(size.x - 20, size.y - 10);
        
        // 입력 텍스트
        if (ImGui::InputText("##TextBoxInput", textBuffer, sizeof(textBuffer), 
            ImGuiInputTextFlags_EnterReturnsTrue | 
            ImGuiInputTextFlags_AutoSelectAll))
        {
            CharArrayToWString();
        }

        // 미리보기 텍스트 (자동 줄바꿈)
        ImGui::TextWrapped("%s", textBuffer);
        
        ImGui::PopItemWidth();
    }
    ImGui::End();
    
    ImGui::PopStyleColor(2);  // 스타일 색상 복원
    ImGui::PopStyleVar(2);    // 스타일 변수 복원
}

void TextBox::WStringToCharArray()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    std::string temp = conv.to_bytes(text);
    strncpy_s(textBuffer, temp.c_str(), sizeof(textBuffer));
    textBuffer[sizeof(textBuffer) - 1] = '\0';
}

void TextBox::CharArrayToWString()
{
    std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
    text = conv.from_bytes(textBuffer);
}
