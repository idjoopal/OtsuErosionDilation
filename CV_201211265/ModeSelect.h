#pragma once


// CModeSelect 대화 상자입니다.

class CModeSelect : public CDialogEx
{
	DECLARE_DYNAMIC(CModeSelect)

public:
	CModeSelect(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CModeSelect();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString mode;
};
