#include "PreCompile.h"
#include "GameEngineInput.h"
#include "GameEngineWindow.h"

// class GameEngineInput::GameEngineKey : public PtrParent<GameEngineKey> --------------------------

bool GameEngineInput::GameEngineKey::KeyCheck() 
{

    if (0 == CheckKey_.size())
    {
        return false;
    }

    // 'a' 's' == 2���� Ű�� �� ������ true�̴�.
    for (size_t i = 0; i < CheckKey_.size(); i++)
    {
        if (0 == GetAsyncKeyState(CheckKey_[i]))
        {
            return false;
        }
    }

    return true;
}

void GameEngineInput::GameEngineKey::Update()
{
    // Ű�� ���ȴ�.
    if (true == KeyCheck())
    {
        // �������� Ű�� �ȴ��ȴ�.
        if (false == Press_)
        {
            Down_ = true;
            Press_ = true;
            Up_ = false;
            Free_ = false;
        }
        else 
        {
            Down_ = false;
            Press_ = true;
            Up_ = false;
            Free_ = false;
        }
    }
    else 
    {
        // �������� Ű�� ���ȴ�.
        if (true == Press_)
        {
            Down_ = false;
            Press_ = false;
            Up_ = true;
            Free_ = false;
        }
        else
        {
            Down_ = false;
            Press_ = false;
            Up_ = false;
            Free_ = true;
        }
    }
}

void GameEngineInput::GameEngineKey::Reset() 
{
    Down_ = false;
    Press_ = false;
    Up_ = false;
    Free_ = true;
}

// static member ------------------------------------------------------------------
GameEngineInput* GameEngineInput::Inst = new GameEngineInput();

// static Func --------------------------------------------------------------------

bool GameEngineInput::IsKey(const std::string & _Name)
{
    if (nullptr != GetInst().FindKey(_Name))
    {
        return true;
    }
    return false;
}

bool GameEngineInput::Down(const std::string& _Name)
{
    GameEngineKey* FindKey = GetInst().FindKey(_Name);

    if (nullptr == FindKey)
    {
        return false;
    }

    return FindKey->Down_;
}
bool GameEngineInput::Up(const std::string& _Name)
{
    GameEngineKey* FindKey = GetInst().FindKey(_Name);

    if (nullptr == FindKey)
    {
        return false;
    }

    return FindKey->Up_;
}
bool GameEngineInput::Press(const std::string& _Name)
{
    GameEngineKey* FindKey = GetInst().FindKey(_Name);

    if (nullptr == FindKey)
    {
        return false;
    }

    return FindKey->Press_;
}
bool GameEngineInput::Free(const std::string& _Name)
{
    GameEngineKey* FindKey = GetInst().FindKey(_Name);

    if (nullptr == FindKey)
    {
        return false;
    }

    return FindKey->Free_;
}

// construct destruct -------------------------------------------------------------
GameEngineInput::GameEngineInput()
{
}
GameEngineInput::~GameEngineInput()
{
    for (std::pair<std::string, GameEngineKey*> PairData : AllKey_)
    {
        delete PairData.second;
        PairData.second = nullptr;
    }
}
// member func --------------------------------------------------------------------

GameEngineInput::GameEngineKey* GameEngineInput::FindKey(const std::string& _KeyName)
{
    std::map<std::string, GameEngineInput::GameEngineKey*>::iterator FindIter = AllKey_.find(_KeyName);

    if (FindIter == AllKey_.end())
    {
        return nullptr;
    }

    return FindIter->second;
}

void GameEngineInput::Update() 
{
    // �������� for
    // ���ϰ� for���� ������ �ְ� �������ִ� ����
    // delete�ϴ� �ڵ峪 insert�ϴ� �ڵ带 ���ο��� ����ϸ�
    // ũ�� �߸��� ���ɼ��� �ִ�.
    for (std::pair<std::string, GameEngineInput::GameEngineKey*>&& _Key : AllKey_)
    {
        _Key.second->Update();
    }

    //POINT P;

    //// ����� �󿡼��� ��ġ ���� Ŀ���� ��ġ�� ��������
    //GetCursorPos(&P);

    //// ������ �󿡼��� ��ġ�� �ٲٰ�
    //// �� �ڵ��� ���� �����츦 ���������� ��ǥ�� ����
    //ScreenToClient(GameEngineWindow::GetInst().GetWindowHWND(), &P);
    //// 4���� ĳ��Ʈ�� �����ϰ� �̿��ؾ� �Ѵ�.
    //MousePos_.x = static_cast<float>(P.x);
    //MousePos_.y = static_cast<float>(P.y);

    //// ��� ���صƳ���?
    //// ������ ������ ���� ������
    //// �ʹ� �ް��ϰ� ���Ҽ� �����ϱ�.
    //PrevMousePos3D_ = MousePos3D_;
    //MousePos3D_.x = MousePos_.x - GameEngineWindow::GetInst().GetSize().hx();
    //MousePos3D_.y = MousePos_.y - GameEngineWindow::GetInst().GetSize().hy();
    //MousePos3D_.y *= -1.0f;

    //MouseDir3D = MousePos3D - PrevMousePos3D;
    //MouseDir3D = MouseDir3D.GetNormalize();
}

float4 GameEngineInput::GetMousePos()
{
    return Inst->MousePos_;
}

float4 GameEngineInput::GetMouse3DPos() 
{
    return Inst->MousePos3D_;
}

float4 GameEngineInput::GetMouse3DDir() 
{
    return Inst->MouseDir3D_;
}
