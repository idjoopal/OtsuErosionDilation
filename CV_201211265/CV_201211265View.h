
// CV_201211265View.h : CCV_201211265View Ŭ������ �������̽�
//

#pragma once
#include <opencv\cv.h>
#include <opencv\cxcore.h>
#include <opencv\highgui.h>
#include "C:\Users\idjoo\Documents\Visual Studio 2015\Projects\CV_201211265\CV_201211265\include\opencv2\core\core.hpp"
#include "ModeSelect.h"
#include "MaskSelect.h"
using namespace cv;


class CCV_201211265View : public CView
{
protected: // serialization������ ��������ϴ�.
	CCV_201211265View();
	DECLARE_DYNCREATE(CCV_201211265View)

// Ư���Դϴ�.
public:
	CCV_201211265Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CCV_201211265View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	RGBQUAD** rgbBuffer;
	int height;
	int width;
	void DoImageloadOpencvload();
	int viewType;
	Mat img;
	void DoOtsuByOpencv();
	void DoOtsuByOwn();
	const int BINARY_OTSU;
	const int BINARY_OTSU_OPENCV;
	int thresholdVal;
	int** grayBuffer;
	int** binaryBuffer;
	int* histogram;
	const int BINARY_DILATION_OC;
	void DoDilationByOpencv();
	const int BINARY_EROSION_OC;
	void DoErosionByOpencv();
	void DoOtsuTwoThreshold();
	int thresholdVal2;
	const int BINARY_OTSU_MULTI;
	boolean modeChked;
	void DoSelectMask(int shape);
	int** mask;
	void DoDilationOwn();
	void DoErosionOwn();
	int row;
	int col;
	int** mophoBuffer;
	const int BINARY_DILATION;
	const int BINARY_EROSION;
	const int BINARY_OPENING;
	const int BINARY_CLOSING;
	void DoOpening();
	void DoClosing();
};

#ifndef _DEBUG  // CV_201211265View.cpp�� ����� ����
inline CCV_201211265Doc* CCV_201211265View::GetDocument() const
   { return reinterpret_cast<CCV_201211265Doc*>(m_pDocument); }
#endif

