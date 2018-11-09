// MaskSelect.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "CV_201211265.h"
#include "MaskSelect.h"
#include "afxdialogex.h"


// CMaskSelect 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMaskSelect, CDialogEx)

CMaskSelect::CMaskSelect(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, maskmode(_T(""))
{

}

CMaskSelect::~CMaskSelect()
{
}

void CMaskSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMaskSelect, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMaskSelect::OnBnClickedOk)
END_MESSAGE_MAP()


// CMaskSelect 메시지 처리기입니다.


void CMaskSelect::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	GetDlgItemText(IDC_EDIT1, maskmode); //이거 추가한다. 
	CDialogEx::OnOK();
}
