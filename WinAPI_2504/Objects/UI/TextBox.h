#pragma once
#include <map>

class TextBox : public Transform{
public:
	TextBox(Vector2 pos, Vector2 size, const char* text);  // UTF-8 문자열을 위한 생성자
	~TextBox();

	static void InitializeFonts();  // 폰트 초기화 함수
	static void ReleaseFonts();     // 폰트 해제 함수

	void Render();
	void SetText(const char* text) { strncpy_s(textBuffer, text, sizeof(textBuffer) - 1); }
	void SetFontSize(int size) { 
		fontSize = size; 
		// 폰트 크기가 변경되면 폰트를 다시 로드
		if (fontName != "Default") {
			ImGuiIO& io = ImGui::GetIO();
			fontMap[fontName] = io.Fonts->AddFontFromFileTTF(fontName.c_str(), (float)fontSize);
			io.Fonts->Build();
			if (DEVICE && DC) {
				ImGui_ImplDX11_InvalidateDeviceObjects();
				ImGui_ImplDX11_CreateDeviceObjects();
			}
		}
	}
	void SetFont(const string& fontName) { 
		this->fontName = fontName; 
		// 폰트가 변경되면 폰트를 다시 로드
		if (fontName != "Default") {
			ImGuiIO& io = ImGui::GetIO();
			fontMap[fontName] = io.Fonts->AddFontFromFileTTF(fontName.c_str(), (float)fontSize);
			io.Fonts->Build();
			if (DEVICE && DC) {
				ImGui_ImplDX11_InvalidateDeviceObjects();
				ImGui_ImplDX11_CreateDeviceObjects();
			}
		}
	}
///	void SetTextColor(Color color) { textColor = color; }
private:

	int fontSize = 20;
	string fontName = "Default";  // 기본 폰트 이름
	
	// 정적 폰트 맵
	static map<string, ImFont*> fontMap;
	static bool fontsInitialized;

	// ImGui용 char 버퍼 (최대 256글자)
	char textBuffer[256] = "";
	Vector2 pos;
	Vector2 size;
	void WStringToCharArray();
	void CharArrayToWString();
//	ColorBuffer* textColor = new ColorBuffer(1.0f, 1.0f, 1.0f, 1.0f);

//	ImGui::

	//ColorBuffer
};