#pragma once
#include <vector>
#include <map>

// 분류 : Category Base
// 용도 : Management
// 설명 : 게임의 input들을 관리해주고 정리하는 클래스
class GameEngineInput
{
private:
    class GameEngineKey 
    {
    private:
        bool Down_;
        bool Press_;
        bool Up_;
        bool Free_;

        std::vector<int> CheckKey_;

        friend GameEngineInput;

    public:
        void PushKey(int _CurKey)
        {
            //if ('a'<= _CurKey && 'z' >= _CurKey)
            //{
            //    _CurKey = toupper(_CurKey);
            //}

            CheckKey_.push_back(_CurKey);
        }

        void PushKey()
        {
        }

    private:
        bool KeyCheck();
        void Update();
        void Reset();
    };

private: // static member 
    static GameEngineInput* Inst;

public: // static Func
    static GameEngineInput& GetInst()
    {
        return *Inst;
    }

    static void Destroy()
    {
        if (nullptr != Inst)
        {
            delete Inst;
            Inst = nullptr;
        }
    }

    static bool IsKey(const std::string& _Name);
    static bool Down(const std::string& _Name);
    static bool Up(const std::string& _Name);
    static bool Press(const std::string& _Name);
    static bool Free(const std::string& _Name);

private: // member
    std::map<std::string, GameEngineKey*> AllKey_;

public: // construct destruct
    GameEngineInput();
    ~GameEngineInput();
    GameEngineInput(const GameEngineInput& _Other) = delete;
    GameEngineInput(const GameEngineInput&& _Other) = delete;

public: // operator
    // 이 함수는 내가 일단 사용하지 않기로 했다.
    GameEngineInput operator=(const GameEngineInput& _Other) = delete;
    GameEngineInput operator=(const GameEngineInput&& _Other) = delete;

private:
    GameEngineKey* FindKey(const std::string& _KeyName);

public: // member func
    void CreateKey(const std::string& _KeyName, int _Key)
    {
        if (nullptr != FindKey(_KeyName))
        {
            assert("if (nullptr != FindKey(_KeyName))");
            return;
        }

        GameEngineKey* NewKey = new GameEngineKey();
        NewKey->Reset();
        NewKey->PushKey(_Key);
        AllKey_.insert(std::map<std::string, GameEngineKey*>::value_type(_KeyName, NewKey));
    }

    void Update();

private:
    float4 MousePos_;
    float4 MousePos3D_;
    float4 PrevMousePos3D_;
    float4 MouseDir3D_;

public: // Mouse
    static float4 GetMousePos(); // 순수한 윈도우 좌표계 스크린 포스
    static float4 GetMouse3DPos(); // 중앙을 0,0 으로보고 위로올라갈수록 y 증가하는 3d용 스크린 좌표
    static float4 GetMouse3DDir(); // 그때 마우스가 움직인 마우스 좌표의 변화량 

};

