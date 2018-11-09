#pragma once


// CMaskSelect 대화 상자입니다.

class CMaskSelect : public CDialogEx
{
	DECLARE_DYNAMIC(CMaskSelect)

public:
	CMaskSelect(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMaskSelect();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString maskmode;
	afx_msg void OnBnClickedOk();
};
