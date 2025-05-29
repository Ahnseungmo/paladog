#include "Framework.h"

Character::Character(Vector2 size) : RectCollider(size)
{
    clipTransform = new Transform();
    clipTransform->SetParent(this);
    clipTransform->SetTag("CharacterClip");

    worldBuffer = new MatrixBuffer();

    CreateHPBar();
}

Character::~Character()
{
    for (Clip* clip : clips)
        delete clip;

    delete clipTransform;
    delete worldBuffer;
}

void Character::Update()
{
    if (curState != Dead)
        State();

    if (curState == Attack)
        AttackTarget();

    Animation();
    clipTransform->UpdateWorld();
    UpdateHPBar();
    UpdateWorld();
}

void Character::Render()
{
    Collider::Render();

    worldBuffer->Set(clipTransform->GetWorld());
    worldBuffer->SetVS(0);
    clips[curState]->Render();
    RenderHPBar();
}

void Character::Edit()
{
    clipTransform->Edit();
    Transform::Edit();
}

void Character::LoadClip(string path, string file, bool isLoop, float speed)
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

    clips.push_back(new Clip(frames, isLoop, speed));

    delete document;
}

void Character::LoadClip(string path, string file, string file2, bool isLoop, float speed)
{
    tinyxml2::XMLDocument* document = new tinyxml2::XMLDocument();
    tinyxml2::XMLDocument* document2 = new tinyxml2::XMLDocument();
    document->LoadFile((path + file).c_str());
    document2->LoadFile((path + file2).c_str());

    tinyxml2::XMLElement* atlas = document->FirstChildElement();
    tinyxml2::XMLElement* atlas2 = document2->FirstChildElement();
    string textureFile = path + atlas->Attribute("imagePath");
    string textureFile2 = path + atlas2->Attribute("imagePath");

    vector<Frame*> frames;
    tinyxml2::XMLElement* sprite = atlas->FirstChildElement();
    tinyxml2::XMLElement* sprite2 = atlas2->FirstChildElement();

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

    while (sprite2 != nullptr)
    {
        float x, y, w, h;
        x = sprite2->FloatAttribute("x");
        y = sprite2->FloatAttribute("y");
        w = sprite2->FloatAttribute("w");
        h = sprite2->FloatAttribute("h");

        wstring file = Utility::ToWString(textureFile2);
        frames.push_back(new Frame(file, x, y, w, h));

        sprite2 = sprite2->NextSiblingElement();
    }

    clips.push_back(new Clip(frames, isLoop, speed));

    delete document;
}

void Character::Move()
{
    if (team == TeamType::Ally)
        Translate(Vector2::Right() * stat.moveSpeed * DELTA);
    else
        Translate(Vector2::Left() * stat.moveSpeed * DELTA);
}

void Character::State()
{
    FindTarget();
    if (target)
        curState = Attack;
    else
        curState = Run;
}

void Character::Animation()
{
    switch (curState)
    {
    case Run:
        Move();
        clips[Run]->Update();
        break;
    case Attack:
        clips[Attack]->Update();
        break;
    case Dead:
        clips[Dead]->Update();
        if (!clips[Dead]->IsPlay())
            SetActive(false);
        break;
    }
}

void Character::FindTarget()
{
    target = nullptr;
    for (Character* unit : *targetList)
    {
        if (!unit->IsActive())
            continue;

        float distance = abs(GetGlobalPosition().x - unit->GetGlobalPosition().x);

        if (distance <= stat.attackRange)
        {
            target = unit;
            break;
        }
    }
}

void Character::AttackTarget()
{
    if (!target || !target->IsActive())
        return;

    attackTimer += DELTA;

    if (attackTimer >= stat.attackSpeed)
    {
        attackTimer -= stat.attackSpeed;

        target->TakeDamage(stat.attack);
    }
}

void Character::TakeDamage(float damage)
{
    if (curState == Dead)
        return;
    hp -= damage;
    if (hp <= 0.0f)
    {
        hp = 0.0f;
        curState = Dead;
        if (clips.size() > Dead && clips[Dead])
            clips[Dead]->Play();
    }
}

void Character::CreateHPBar()
{
    background = new Quad(L"Resources/Textures/White.png");
    background->SetColor(0.2f, 0.2f, 0.2f);
    background->SetSize(Vector2(HPBAR_WIDTH, HPBAR_HEIGHT));

    hpBar = new Quad(L"Resources/Textures/White.png");
    hpBar->SetColor(1.0f, 0.0f, 0.0f);
    hpBar->SetSize(Vector2(HPBAR_WIDTH, HPBAR_HEIGHT));
}

void Character::UpdateHPBar()
{
    float ratio = (stat.maxHp > 0.0f) ? (hp / stat.maxHp) : 0.0f;
    ratio = max(0.0f, min(1.0f, ratio));
    float width = HPBAR_WIDTH * ratio;

    Vector2 basePos = GetGlobalPosition() + Vector2(0, Size().y * HPBAR_POS);

    background->SetLocalPosition(basePos);
    background->SetSize(Vector2(HPBAR_WIDTH, HPBAR_HEIGHT));

    Vector2 hpBarPos = basePos + Vector2(-(HPBAR_WIDTH - width) * 0.5f, 0);
    hpBar->SetLocalPosition(hpBarPos);
    hpBar->SetSize(Vector2(width, HPBAR_HEIGHT));

    background->UpdateWorld();
    hpBar->UpdateWorld();
}

void Character::RenderHPBar()
{
    background->Render();
    hpBar->Render();
}
