// ModeSelect.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CV_201211265.h"
#include "ModeSelect.h"
#include "afxdialogex.h"


// CModeSelect 대화 상자입니다.

IMPLEMENT_DYNAMIC(CModeSelect, CDialogEx)

CModeSelect::CModeSelect(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, mode(_T(""))
{

}

CModeSelect::~CModeSelect()
{
}

void CModeSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CModeSelect, CDialogEx)
	ON_BN_CLICKED(IDOK, &CModeSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// CModeSelect 메시지 처리기입니다.


void CModeSelect::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT, mode); //이거 추가한다. 
	CDialogEx::OnOK();
}
