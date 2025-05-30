#include "Framework.h"

CharacterAnimation::CharacterAnimation()
{
}

CharacterAnimation::~CharacterAnimation()
{
    for (Clip* clip : clips)
        delete clip;
}

void CharacterAnimation::LoadClip(const string& path, const string& file, bool isLoop, float speed)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile((path + file).c_str());

    tinyxml2::XMLElement* atlas = doc.FirstChildElement();
    string textureFile = path + atlas->Attribute("imagePath");

    vector<Frame*> frames;
    for (tinyxml2::XMLElement* sprite = atlas->FirstChildElement(); sprite != nullptr; sprite = sprite->NextSiblingElement())
    {
        float x = sprite->FloatAttribute("x");
        float y = sprite->FloatAttribute("y");
        float w = sprite->FloatAttribute("w");
        float h = sprite->FloatAttribute("h");

        frames.push_back(new Frame(Utility::ToWString(textureFile), x, y, w, h));
    }

    clips.push_back(new Clip(frames, isLoop, speed));
}

void CharacterAnimation::LoadClip(const string& path, const string& file1, const string& file2, bool isLoop, float speed)
{
    tinyxml2::XMLDocument doc1, doc2;
    doc1.LoadFile((path + file1).c_str());
    doc2.LoadFile((path + file2).c_str());

    tinyxml2::XMLElement* atlas1 = doc1.FirstChildElement();
    tinyxml2::XMLElement* atlas2 = doc2.FirstChildElement();
    string tex1 = path + atlas1->Attribute("imagePath");
    string tex2 = path + atlas2->Attribute("imagePath");

    vector<Frame*> frames;

    for (tinyxml2::XMLElement* sprite = atlas1->FirstChildElement(); sprite != nullptr; sprite = sprite->NextSiblingElement())
    {
        float x = sprite->FloatAttribute("x");
        float y = sprite->FloatAttribute("y");
        float w = sprite->FloatAttribute("w");
        float h = sprite->FloatAttribute("h");

        frames.push_back(new Frame(Utility::ToWString(tex1), x, y, w, h));
    }

    for (tinyxml2::XMLElement* sprite = atlas2->FirstChildElement(); sprite != nullptr; sprite = sprite->NextSiblingElement())
    {
        float x = sprite->FloatAttribute("x");
        float y = sprite->FloatAttribute("y");
        float w = sprite->FloatAttribute("w");
        float h = sprite->FloatAttribute("h");

        frames.push_back(new Frame(Utility::ToWString(tex2), x, y, w, h));
    }

    clips.push_back(new Clip(frames, isLoop, speed));
}

void CharacterAnimation::Update(size_t index)
{
    if(index < clips.size())
        clips[index]->Update();
}

void CharacterAnimation::Play(size_t index)
{
    if (index < clips.size())
        clips[index]->Play();
}

void CharacterAnimation::Render(size_t index)
{
    if (index < clips.size())
        clips[index]->Render();
}

bool CharacterAnimation::IsPlay(size_t index) const
{
    if (index < clips.size())
        return clips[index]->IsPlay();
    return false;
}

Clip* CharacterAnimation::GetClip(size_t index)
{
    if (index < clips.size())
        return clips[index];
    return nullptr;
}

size_t CharacterAnimation::GetClipCount() const
{
    return clips.size();
}
