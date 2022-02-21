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

    // 'a' 's' == 2개의 키가 다 눌려야 true이다.
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
    // 키가 눌렸다.
    if (true == KeyCheck())
    {
        // 이전까지 키가 안눌렸다.
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
        // 이전까지 키가 눌렸다.
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
    // 레인지드 for
    // 편하게 for문을 돌릴수 있게 지원해주는 문법
    // delete하는 코드나 insert하는 코드를 내부에서 사용하면
    // 크게 잘못될 가능성이 있다.
    for (std::pair<std::string, GameEngineInput::GameEngineKey*>&& _Key : AllKey_)
    {
        _Key.second->Update();
    }

    //POINT P;

    //// 모니터 상에서의 위치 현재 커서의 위치를 가져오고
    //GetCursorPos(&P);

    //// 윈도우 상에서의 위치로 바꾸고
    //// 이 핸들을 가진 윈도우를 기준으로한 좌표로 변경
    //ScreenToClient(GameEngineWindow::GetInst().GetWindowHWND(), &P);
    //// 4가지 캐스트를 적절하게 이용해야 한다.
    //MousePos_.x = static_cast<float>(P.x);
    //MousePos_.y = static_cast<float>(P.y);

    //// 요거 이해됐나요?
    //// 이전거 저장해 놓은 다음에
    //// 너무 급격하게 변할수 있으니까.
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
