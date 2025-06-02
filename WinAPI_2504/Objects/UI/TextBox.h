#pragma once

class TextBox : public Transform{
public:
	TextBox(Vector2 pos, Vector2 size, wstring text);
	~TextBox();

	void Render() ;
	void SetText(wstring text) { this->text = text; }
	void SetFontSize(int size) { fontSize = size; }
///	void SetTextColor(Color color) { textColor = color; }
private:
	Quad* quad;
	wstring text;
	int fontSize = 20;
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