
// CV_201211265.h : CV_201211265 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CCV_201211265App:
// �� Ŭ������ ������ ���ؼ��� CV_201211265.cpp�� �����Ͻʽÿ�.
//

class CCV_201211265App : public CWinAppEx
{
public:
	CCV_201211265App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCV_201211265App theApp;
