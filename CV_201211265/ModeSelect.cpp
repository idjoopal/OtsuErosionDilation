// ModeSelect.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CV_201211265.h"
#include "ModeSelect.h"
#include "afxdialogex.h"


// CModeSelect ��ȭ �����Դϴ�.

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


// CModeSelect �޽��� ó�����Դϴ�.


void CModeSelect::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemText(IDC_EDIT, mode); //�̰� �߰��Ѵ�. 
	CDialogEx::OnOK();
}
