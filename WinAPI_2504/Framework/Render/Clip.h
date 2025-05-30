#pragma once

class Clip
{
private:
    const float FPS = 10.0f;

public:
    Clip(vector<Frame*> frames, bool isLoop = true, float speed = 1.0f);
    ~Clip();

    void Update();
    void Render();

    bool IsPlay() const { return isPlay; }
    void Play();
    void Stop() { isPlay = false; }

    void SetShader(wstring shaderFile);    

    Frame* GetCurFrame() { return frames[curFrameNum]; }

    void SetFrameEvent(UINT frame, function<void()> callback);

    float GetSpeed() { return speed; }
    void SetSpeed(float changeSpeed) { speed = changeSpeed; }

private:
    vector<Frame*> frames;

    UINT curFrameNum = 0;

    float frameTime = 0.0f;
    float intervalTime = 0.0f;
    float speed;

    bool isLoop;
    bool isPlay = true;

    map<UINT, function<void()>> frameEvents;
};