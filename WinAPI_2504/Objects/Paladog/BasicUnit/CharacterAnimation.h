#pragma once

class CharacterAnimation
{
public:
    CharacterAnimation();
    ~CharacterAnimation();

    void LoadClip(const string& path, const string& file, bool isLoop, float speed = 1.0f);
    void LoadClip(const string& path, const string& file1, const string& file2, bool isLoop, float speed = 1.0f);

    void Update(size_t index);
    void Play(size_t index);
    void Render(size_t index);
    bool IsPlay(size_t index) const;

    Clip* GetClip(size_t index);
    size_t GetClipCount() const;

private:
    vector<Clip*> clips;
};