#include "Framework.h"

Chest::Chest() : RectCollider(Vector2(650, 500))
{
	CreateClips();
	clipTransform = new Transform();
	clipTransform->SetTag("ChestClip");
	clipTransform->SetParent(this);
	clip->Stop();
	worldBuffer = new MatrixBuffer();
}

Chest::~Chest()
{
	delete clip;

	delete clipTransform;
	delete worldBuffer;
}

void Chest::Update()
{
	if (Input::Get()->IsKeyDown('1'))
		ChestIdle();
	if (Input::Get()->IsKeyDown('2'))
		ChestOpen();

	clip->Update();
	clipTransform->UpdateWorld();
	UpdateWorld();
}
void Chest::ChestOpen() {
	curState = Open;
	clip->Play();


}
void Chest::ChestIdle() {

	curState = Idle;
	clip->Play();
	clip->Stop();
}

void Chest::Render()
{
	Collider::Render();

	worldBuffer->Set(clipTransform->GetWorld());
	worldBuffer->SetVS(0);
	clip->Render();
}

void Chest::Edit()
{
	clipTransform->Edit();
	Transform::Edit();
}

bool Chest::IsOpenEnd()
{
	if (curState == Open && clip->IsPlay() == false)
	{
		//		curState = Idle;
		return true;
	}
	return false;
}


void Chest::CreateClips()
{

	LoadClip("Resources/Textures/Paladog/Gotcha/", "Chest_Open.xml", false);
}

void Chest::LoadClip(string path, string file, bool isLoop, float speed)
{
	tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
	document->LoadFile((path + file).c_str());

	tinyxml2::XMLElement* atlas = document->FirstChildElement();
	string textureFile = path + atlas->Attribute("imagePath");

	vector<Frame*> frames;
	tinyxml2::XMLElement* sprite = atlas->FirstChildElement();

	while (sprite != nullptr)
	{
		float x, y, w, h;
		x = sprite->FloatAttribute("x");
		y = sprite->FloatAttribute("y");
		w = sprite->FloatAttribute("w");
		h = sprite->FloatAttribute("h");

		wstring file = Utility::ToWString(textureFile);
		frames.push_back(new Frame(file, x, y, w, h));

		sprite = sprite->NextSiblingElement();
	}

	clip = new Clip(frames, isLoop, speed);

	delete document;
}
