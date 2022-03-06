#pragma once
#include <ole2.h>

class CExcelControl
{
private:
	bool m_bCOMInited;
	bool m_bInit;
	struct PROPERTIES
	{
		IDispatch* pXlApp;
		IDispatch* pXlBooks;
		IDispatch* pXlBook;
		IDispatch* pXlSheet;
	}m_instance;

public:
	CExcelControl();
	virtual ~CExcelControl();

public:
	int SetVisible(bool Visible);
	int Open(const char* File);
	int SetActiveSheet(int SheetNo);
	bool GetData(char* pPos, char* Data);
	bool SetData(char* Pos, char* Data);
	void Save();
	void Close();

protected:
	int Init();
	bool CheckExcelInnit();
};

