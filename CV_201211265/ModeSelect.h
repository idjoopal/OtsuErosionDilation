#pragma once


// CModeSelect ��ȭ �����Դϴ�.

class CModeSelect : public CDialogEx
{
	DECLARE_DYNAMIC(CModeSelect)

public:
	CModeSelect(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CModeSelect();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString mode;
};
