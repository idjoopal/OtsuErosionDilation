#pragma once


// CMaskSelect ��ȭ �����Դϴ�.

class CMaskSelect : public CDialogEx
{
	DECLARE_DYNAMIC(CMaskSelect)

public:
	CMaskSelect(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMaskSelect();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString maskmode;
	afx_msg void OnBnClickedOk();
};
