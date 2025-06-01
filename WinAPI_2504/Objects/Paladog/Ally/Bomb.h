#pragma once

class Bomb : public RectCollider
{
public:
    Bomb(Vector2 size = Vector2(60, 60));
    ~Bomb();

    void Update();
    void Render();

    void Fire(Vector2 pos, vector<Character*> targets);
    void Explode();
    void Move();

private:
    enum class BombState
    {
        Flying,
        Exploding
    };

    BombState state = BombState::Flying;

    vector<Character*> targets;
    float speed = 400.0f;
    Vector2 dir;

    Transform* clipTransform;
    CharacterAnimation* animation;
    MatrixBuffer* worldBuffer;
};
