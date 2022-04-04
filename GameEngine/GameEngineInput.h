#pragma once
#include <vector>
#include <map>
#include <string>

// �з� : Category Base
// �뵵 : Management
// ���� : ������ input���� �������ְ� �����ϴ� Ŭ����
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
            CheckKey_.push_back(_CurKey);
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
    static void CursorHide();
    static void CursorShow();

private: // member
    std::map<std::string, GameEngineKey*> AllKey_;

public: // construct destruct
    GameEngineInput();
    ~GameEngineInput();
    GameEngineInput(const GameEngineInput& _Other) = delete;
    GameEngineInput(const GameEngineInput&& _Other) = delete;

public: // operator
    // �� �Լ��� ���� �ϴ� ������� �ʱ�� �ߴ�.
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

        // TopUpper
        if ('a' <= _Key && 'z' >= _Key)
        {
            _Key = std::toupper(_Key);
        }

        GameEngineKey* NewKey = new GameEngineKey();
        NewKey->Reset();
        NewKey->PushKey(_Key);
        AllKey_.insert(std::map<std::string, GameEngineKey*>::value_type(_KeyName, NewKey));
    }

    void Update();


private:
    float4 MousePos_;
    float4 PrevMousePos_;
    float4 MousePos3D_;
    float4 PrevMousePos3D_;
    float4 MouseDir3D_;

public: // Mouse
    static float4 GetMousePos(); // ������ ������ ��ǥ�� ��ũ�� ����(����)
    static float4 GetPrevMousePos(); // ������ ������ ��ǥ�� ��ũ�� ����(����)
    static float4 GetMouse3DPos(); // �߾��� 0,0 ���κ��� ���οö󰥼��� y �����ϴ� 3d�� ��ũ�� ��ǥ(����)
    static float4 GetPrevMouse3DPos(); // �߾��� 0,0 ���κ��� ���οö󰥼��� y �����ϴ� 3d�� ��ũ�� ��ǥ(����)
    static float4 GetMouse3DDir(); // �׶� ���콺�� ������ ���콺 ��ǥ�� ��ȭ�� 
};
