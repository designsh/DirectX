#pragma once
#include "GameEnginePath.h"

// 분류 :
// 용도 :
// 설명 :
class GameEngineFile : public GameEnginePath
{
private:
	FILE* fileHandle_;
	std::string OpenMode;

public:		
	GameEngineFile(); // default constructer 디폴트 생성자
	GameEngineFile(const std::string& _Path); // default constructer 디폴트 생성자
	GameEngineFile(const std::string& _Path, const std::string& _Mode); // default constructer 디폴트 생성자
	~GameEngineFile(); // default destructer 디폴트 소멸자

public:		// delete constructer
	GameEngineFile(const GameEngineFile& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineFile(GameEngineFile&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

public:		//delete operator
	GameEngineFile& operator=(const GameEngineFile& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineFile& operator=(const GameEngineFile&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:		//member Func
	void Open(const std::string& _Mode);
	void Close();

public:
	void Write(const void* _Data, size_t _Size);

	// 템플릿으로 만들면 위험할때가 많아서
	// 직접 만들겠습니다.
	// 진짜 크기가 안변할 자료형들만 저장할겁니다.
	// 필요하면 직접 만드세요.
	// short 저장하는게 없어요 
	void Write(const std::string& _Data);
	void Write(const int& _Data);

	template<typename DataType>
	void Write(std::vector<DataType>& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		Write(&Size, sizeof(int));

		for (size_t i = 0; i < _Data.size(); i++)
		{
			Write(_Data[i]);
		}
	}

	template<typename DataType>
	void Write(std::list<DataType>& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		Write(&Size, sizeof(int));

		// 템플릿에서 다른 템플릿 사용할때는 형을 잘 모르므로
		// typename 붙여줘야 합니다.
		typename std::list<DataType>::iterator Start = _Data.begin();
		typename std::list<DataType>::iterator End = _Data.end();

		for (; Start != End; ++Start)
		{
			Write(*Start);
		}
	}

	template<typename KeyType, typename DataType>
	void Write(std::map<KeyType, DataType>& _Data)
	{
		int Size = static_cast<int>(_Data.size());
		Write(&Size, sizeof(int));

		typename std::map<KeyType, DataType>::iterator Start = _Data.begin();
		typename std::map<KeyType, DataType>::iterator End = _Data.end();

		for (; Start != End; ++Start)
		{
			Write(Start->first);
			Write(Start->second);
		}
	}



	// 크기가 변하는 자료형은 정말정말 위험하다.
	void Write(const size_t& _Data) = delete;

	void Read(void* _Buffer, size_t _BufferSize, size_t _Size);
	void Read(std::string& _Data);
	void Read(int& _Data);



	template<typename DataType>
	void Read(std::vector<DataType>& _Data)
	{
		int Size = 0;
		Read(&Size, sizeof(int), sizeof(int));

		for (int i = 0; i < Size; i++)
		{
			DataType Buffer;
			Read(Buffer);
			_Data.push_back(Buffer);
		}
	}

	template<typename DataType>
	void Read(std::list<DataType>& _Data)
	{
		int Size = 0;
		Read(&Size, sizeof(int), sizeof(int));

		for (int i = 0; i < Size; i++)
		{
			DataType Buffer;
			Read(Buffer);
			_Data.push_back(Buffer);
		}
	}

	template<typename KeyType, typename DataType>
	void Read(std::map<KeyType, DataType>& _Data)
	{
		int Size = 0;
		Read(&Size, sizeof(int), sizeof(int));

		for (int i = 0; i < Size; i++)
		{
			KeyType KeyBuffer;
			Read(KeyBuffer);
			DataType ValueBuffer;
			Read(ValueBuffer);

			_Data.insert(std::map<KeyType, DataType>::value_type(KeyBuffer, ValueBuffer));
		}
	}


};

