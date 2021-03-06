// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"
	
#ifdef DWMBLUR	//win7毛玻璃开关
#include <dwmapi.h>
#pragma comment(lib,"dwmapi.lib")
#endif
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	#ifdef DWMBLUR	//win7毛玻璃开关
	MARGINS mar = {5,5,30,5};
	DwmExtendFrameIntoClientArea ( m_hWnd, &mar );
	#endif

	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
	return 0;
}

void CMainDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_RETURN) {
		OnBtnWebkitGo();
	}
	else {
		SetMsgHandled(FALSE);
	}
}

HRESULT CMainDlg::OnBtnWebkitGo()
{
	SWkeWebkit *pWebKit = FindChildByName2<SWkeWebkit>(L"wke_test");
	assert(pWebKit);
	SEdit *pEdit = FindChildByName2<SEdit>(L"edit_url");
	SStringT strUrl = pEdit->GetWindowText();
	pWebKit->SetAttribute(L"url", S_CT2W(strUrl), FALSE);
	return S_OK;
}

HRESULT CMainDlg::OnBtnWebkitRefresh()
{
	SWkeWebkit *pWebkit = FindChildByName2<SWkeWebkit>(L"wke_test");
	assert(pWebkit);
	pWebkit->GetWebView()->reload();

	return S_OK;
}
HRESULT CMainDlg::OnBtnWebkitBackward()
{
	SWkeWebkit *pWebkit = FindChildByName2<SWkeWebkit>(L"wke_test");
	assert(pWebkit);
	pWebkit->GetWebView()->goBack();

	return S_OK;
}
HRESULT CMainDlg::OnBtnWebkitForward()
{
	SWkeWebkit *pWebkit = FindChildByName2<SWkeWebkit>(L"wke_test");
	assert(pWebkit);
	pWebkit->GetWebView()->goForward();

	return S_OK;
}


//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}

