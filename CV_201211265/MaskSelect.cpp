// MaskSelect.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "CV_201211265.h"
#include "MaskSelect.h"
#include "afxdialogex.h"


// CMaskSelect ��ȭ �����Դϴ�.

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


// CMaskSelect �޽��� ó�����Դϴ�.


void CMaskSelect::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	GetDlgItemText(IDC_EDIT1, maskmode); //�̰� �߰��Ѵ�. 
	CDialogEx::OnOK();
}
