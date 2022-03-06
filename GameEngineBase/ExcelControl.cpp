#include "PreCompile.h"
#include "ExcelControl.h"
#include "stdio.h"

CExcelControl::CExcelControl() :
	m_bCOMInited(false),
	m_bInit(false),
	m_instance{}
{
	if (CoInitialize(NULL) != S_OK)
	{
		m_bCOMInited = false;
	}
	else
	{
		m_bCOMInited = true;
	}
}

CExcelControl::~CExcelControl()
{
	if (m_bCOMInited)
	{
		CoUninitialize();
	}
}

HRESULT AutoWrap(int autoType, VARIANT* pvResult, IDispatch* Disp, LPOLESTR ptName, int cArgs...)
{
	// Begin variable_argument List
	va_list marker;
	va_start(marker, cArgs);
	if (!Disp)
	{
		_exit(0);
	}

	// Variables used
	DISPPARAMS dp = { NULL, NULL, 0, 0 };
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	DISPID dispID;
	HRESULT hr;
	char buf[256] = {};
	char szName[256] = {};

	// Convert WideChar to MultiBute
	WideCharToMultiByte(CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL);

	// Get DISPID for Name passed
	hr = Disp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
	if (FAILED(hr))
	{
		sprintf_s(buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr);

		_exit(0);
		return hr;
	}

	// Allcate Memory for arguments
	VARIANT* pArgs = new VARIANT[cArgs + 1];

	// Extract Argument
	for (int i = 0; i < cArgs; i++)
	{
		pArgs[i] = va_arg(marker, VARIANT);
	}

	// Build DISPPARAMS
	dp.cArgs = cArgs;
	dp.rgvarg = pArgs;

	// Handle special-case for property-puts
	if (autoType & DISPATCH_PROPERTYPUT)
	{
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
	}

	// Make the call
	hr = Disp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
	if (FAILED(hr))
	{
		return hr;
	}

	va_end(marker);
	delete[] pArgs;
	return hr;
}

int CExcelControl::SetVisible(bool bVisible)
{
	if (!CheckExcelInnit())
	{
		return -1;
	}

	// String Edit
	WCHAR TypeStr[256] = {};
	lstrcpy(TypeStr, L"Visible");

	// Make it visible
	VARIANT x;
	x.vt = VT_I4;
	x.lVal = bVisible ? 1 : 0;
	HRESULT hr = AutoWrap(DISPATCH_PROPERTYPUT, NULL, m_instance.pXlApp, TypeStr, 1, x);
	if (FAILED(hr))
	{
		return -1;
	}

	return 1;
}

int CExcelControl::Open(const char* File)
{
	if (Init() < 0)
	{
		return -1;
	}
	if (!CheckExcelInnit())
	{
		return -1;
	}
	if (File == NULL)
	{
		return -1;
	}

	// String Edit
	WCHAR TypeStr[256] = {};
	lstrcpy(TypeStr, L"Open");

	VARIANT result;
	VariantInit(&result);
	_bstr_t str = File;
	VARIANT vaPath;
	vaPath.vt = VT_BSTR;
	vaPath.bstrVal = ::SysAllocString(str);
	AutoWrap(DISPATCH_METHOD, &result, m_instance.pXlBooks, TypeStr, 1, vaPath);
	m_instance.pXlBook = result.pdispVal;
	SysFreeString(vaPath.bstrVal);

	return 1;
}

int CExcelControl::SetActiveSheet(int SheetNo)
{
	// String Edit
	WCHAR TypeStr[256] = {};
	lstrcpy(TypeStr, L"Worksheets");

	// Get ActiveSheet Object
	VARIANT result;
	VariantInit(&result);
	VARIANT vaSheet;
	vaSheet.vt = VT_I4;
	vaSheet.lVal = SheetNo;
	AutoWrap(DISPATCH_PROPERTYGET, &result, m_instance.pXlApp, TypeStr, 1, vaSheet);
	m_instance.pXlSheet = result.pdispVal;

	return 1;
}

bool CExcelControl::GetData(char* pPos, char* pData)
{
	if (pPos == NULL || pData == NULL)
	{
		return false;
	}

	// Get Range object for the Range A1:O15...
	_bstr_t str;
	str = pPos; // BSTR
	str += ":";
	str += pPos;
	IDispatch* pXlRange;
	{
		// String Edit
		WCHAR TypeStr[256] = {};
		lstrcpy(TypeStr, L"Range");

		VARIANT parm;
		parm.vt = VT_BSTR;
		parm.bstrVal = ::SysAllocString(str);
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, m_instance.pXlSheet, TypeStr, 1, parm);
		VariantClear(&parm);
		pXlRange = result.pdispVal;
	}

	// String Edit
	WCHAR TypeStr[256] = {};
	lstrcpy(TypeStr, L"Value");

	VARIANT tmp;
	tmp.vt = VT_BSTR;
	AutoWrap(DISPATCH_PROPERTYGET, &tmp, pXlRange, TypeStr, 0, 0);
	if (tmp.vt == VT_EMPTY)
	{
		pData[0] = '\0';
	}
	else
	{
		HRESULT hr = VariantChangeType(&tmp, &tmp, VARIANT_NOUSEROVERRIDE, VT_BSTR);
		if (FAILED(hr))
		{
			pData[0] = '\0';
		}

		str = tmp.bstrVal;

		strcpy_s(pData, sizeof(str) * 2, str);
	}

	// Release references...
	pXlRange->Release();

	return true;
}

bool CExcelControl::SetData(char* pPos, char* pData)
{
	if (pPos == NULL || pData == NULL)
	{
		return false;
	}

	_bstr_t str;
	VARIANT tmp;
	tmp.vt = VT_BSTR;
	tmp.bstrVal = ::SysAllocString(str);
	// Get Range object for the Range       
	str = pPos;
	str += ":";
	str += pPos;
	IDispatch* pXlRange;
	{
		// String Edit
		WCHAR TypeStr[256] = {};
		lstrcpy(TypeStr, L"Range");

		VARIANT parm;
		parm.vt = VT_BSTR;
		parm.bstrVal = ::SysAllocString(str);
		VARIANT result;
		VariantInit(&result);
		AutoWrap(DISPATCH_PROPERTYGET, &result, m_instance.pXlSheet, TypeStr, 1, parm);
		VariantClear(&parm);
		pXlRange = result.pdispVal;
	}
	// String Edit
	WCHAR TypeStr[256] = {};
	lstrcpy(TypeStr, L"Value");

	// Set range with our safearray...
	AutoWrap(DISPATCH_PROPERTYPUT, NULL, pXlRange, TypeStr, 1, tmp);//     

	// Release references...
	pXlRange->Release();

	return true;
}

void CExcelControl::Save()
{
	// String Edit
	WCHAR TypeStr[256] = {};
	lstrcpy(TypeStr, L"Save");

	AutoWrap(DISPATCH_METHOD, NULL, m_instance.pXlApp, TypeStr, 0);
}

void CExcelControl::Close()
{
	// String Edit
	WCHAR TypeStr[256] = {};
	lstrcpy(TypeStr, L"Quit");

	AutoWrap(DISPATCH_METHOD, NULL, m_instance.pXlApp, TypeStr, 0);
	m_instance.pXlSheet->Release();
	m_instance.pXlBook->Release();
	m_instance.pXlBooks->Release();
	m_instance.pXlApp->Release();
}

int CExcelControl::Init()
{
	// Get CLSID for our server
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"Excel.Application", &clsid);
	if (FAILED(hr))
	{
		return -1;
	}

	// Start server and get IDIspatch
	hr = CoCreateInstance(clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&m_instance.pXlApp);
	if (FAILED(hr))
	{
		return -2;
	}

	// String Edit
	WCHAR TypeStr[256] = {};
	lstrcpy(TypeStr, L"Workbooks");

	// Get Workbooks Collection
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET, &result, m_instance.pXlApp, TypeStr, 0);
	m_instance.pXlBooks = result.pdispVal;
	m_bInit = true;

	return 1;
}

bool CExcelControl::CheckExcelInnit()
{
	return m_bInit;
}
