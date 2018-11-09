
// CV_201211265View.cpp : CCV_201211265View Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "CV_201211265.h"
#endif

#include "CV_201211265Doc.h"
#include "CV_201211265View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCV_201211265View

IMPLEMENT_DYNCREATE(CCV_201211265View, CView)

BEGIN_MESSAGE_MAP(CCV_201211265View, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CCV_201211265View ����/�Ҹ�

CCV_201211265View::CCV_201211265View()
	: modeChked(false)
	, rgbBuffer(nullptr)
	, height(0)
	, width(0)
	, viewType(0)

	, BINARY_CLOSING(8)
	, BINARY_OPENING(7)
	, BINARY_EROSION(6)
	, BINARY_DILATION(5)
	, BINARY_EROSION_OC(4)
	, BINARY_DILATION_OC(3)
	, BINARY_OTSU_MULTI(2)
	, BINARY_OTSU(1)
	, BINARY_OTSU_OPENCV(0)

	, thresholdVal(0)
	, thresholdVal2(0)
	, grayBuffer(nullptr)
	, binaryBuffer(nullptr)
	, histogram(nullptr)
	
	, mask(nullptr)
	, row(0)
	, col(0)
	, mophoBuffer(NULL)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	
}

CCV_201211265View::~CCV_201211265View()
{
}

BOOL CCV_201211265View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}


// CCV_201211265View �μ�

BOOL CCV_201211265View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CCV_201211265View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CCV_201211265View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CCV_201211265View ����

#ifdef _DEBUG
void CCV_201211265View::AssertValid() const
{
	CView::AssertValid();
}

void CCV_201211265View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCV_201211265Doc* CCV_201211265View::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCV_201211265Doc)));
	return (CCV_201211265Doc*)m_pDocument;
}
#endif //_DEBUG


// CCV_201211265View �޽��� ó����

// CCV_201211265View �׸���

void CCV_201211265View::OnDraw(CDC* pDC)
{
	CCV_201211265Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
	
	// �̹��� �ҷ�����.
	if (rgbBuffer == nullptr) {
		DoImageloadOpencvload();
	}

	// ���� �̹��� ����
	if (rgbBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pDC->SetPixel(j, i, RGB(rgbBuffer[i][j].rgbRed, rgbBuffer[i][j].rgbGreen, rgbBuffer[i][j].rgbBlue));
			}
		}
	}

	
	
	CModeSelect m_dialog; // �� ���̾�α� Ŭ������ ����
	CString modestr; // ���� ���� ����
	if (m_dialog.DoModal() == IDOK) //���
	{
		modestr = m_dialog.mode; //���̾�α��� NewName�� �޾� ������ ����
		modeChked = true;
	}
	viewType = _ttoi(modestr) - 1;
	//viewType = BINARY_OTSU_MULTI;

	// ��� ����
	if (viewType == BINARY_OTSU_OPENCV) {
		DoOtsuByOpencv();
	}
	else if (viewType == BINARY_OTSU) {
		DoOtsuByOwn();

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pDC->SetPixel(j + width + 10, i, RGB(grayBuffer[i][j], grayBuffer[i][j], grayBuffer[i][j]));
				pDC->SetPixel(j + width * 2 + 10 * 2, i, RGB(binaryBuffer[i][j], binaryBuffer[i][j], binaryBuffer[i][j]));
			}
		}
		//������׷� �׷��� ���
		for (int i = 0; i < 256; i++) {
			for (int j = 256; j > 255 - histogram[i]; j--) {
				pDC->SetPixel(i, j + height + 10, RGB(0, 0, 0));
			}
			// �Ӱ��� ���
			if (i == thresholdVal) {
				for (int j = 0; j < 255; j++) {
					pDC->SetPixel(i, j + height + 10, RGB(255, 0, 0));
				}
			}
		}
	}
	else if (viewType == BINARY_OTSU_MULTI) {
		DoOtsuTwoThreshold();

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pDC->SetPixel(j + width + 10, i, RGB(grayBuffer[i][j], grayBuffer[i][j], grayBuffer[i][j]));
				pDC->SetPixel(j + width * 2 + 10 * 2, i, RGB(binaryBuffer[i][j], binaryBuffer[i][j], binaryBuffer[i][j]));
			}
		}
		//������׷� �׷��� ���
		for (int i = 0; i < 256; i++) {
			for (int j = 256; j > 255 - histogram[i]; j--) {
				pDC->SetPixel(i, j + height + 10, RGB(0, 0, 0));
			}
			// �Ӱ��� ���
			if (i == thresholdVal) {
				for (int j = 0; j < 255; j++) {
					pDC->SetPixel(i, j + height + 10, RGB(255, 0, 0));
				}
			}
			// �Ӱ��� ���
			if (i == thresholdVal2) {
				for (int j = 0; j < 255; j++) {
					pDC->SetPixel(i, j + height + 10, RGB(255, 0, 0));
				}
			}
		}
	}
	else if (viewType == BINARY_DILATION_OC) {
		DoDilationByOpencv();
	}
	else if (viewType == BINARY_EROSION_OC) {
		DoErosionByOpencv();
	}
	else if (viewType == BINARY_DILATION) {
		CMaskSelect m_dialog; // �� ���̾�α� Ŭ������ ����
		CString modestr; // ���� ���� ����
		if (m_dialog.DoModal() == IDOK) //���
		{
			modestr = m_dialog.maskmode; //���̾�α��� NewName�� �޾� ������ ����
		}
		int shape = _ttoi(modestr) - 1;
		DoSelectMask(shape);
		DoDilationOwn();

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pDC->SetPixel(j + width + 10, i, RGB(binaryBuffer[i][j], binaryBuffer[i][j], binaryBuffer[i][j]));
				pDC->SetPixel(j + width * 2 + 10 * 2, i, RGB(mophoBuffer[i][j], mophoBuffer[i][j], mophoBuffer[i][j]));
			}
		}
	}
	else if (viewType == BINARY_EROSION) {
		CMaskSelect m_dialog; // �� ���̾�α� Ŭ������ ����
		CString modestr; // ���� ���� ����
		if (m_dialog.DoModal() == IDOK) //���
		{
			modestr = m_dialog.maskmode; //���̾�α��� NewName�� �޾� ������ ����
		}
		int shape = _ttoi(modestr) - 1;
		DoSelectMask(shape);
		DoErosionOwn();

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pDC->SetPixel(j + width + 10, i, RGB(binaryBuffer[i][j], binaryBuffer[i][j], binaryBuffer[i][j]));
				pDC->SetPixel(j + width * 2 + 10 * 2, i, RGB(mophoBuffer[i][j], mophoBuffer[i][j], mophoBuffer[i][j]));
			}
		}
	}
	else if (viewType == BINARY_OPENING) {
		CMaskSelect m_dialog; // �� ���̾�α� Ŭ������ ����
		CString modestr; // ���� ���� ����
		if (m_dialog.DoModal() == IDOK) //���
		{
			modestr = m_dialog.maskmode; //���̾�α��� NewName�� �޾� ������ ����
		}
		int shape = _ttoi(modestr) - 1;
		DoSelectMask(shape);
		DoOpening();

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pDC->SetPixel(j + width + 10, i, RGB(binaryBuffer[i][j], binaryBuffer[i][j], binaryBuffer[i][j]));
				pDC->SetPixel(j + width * 2 + 10 * 2, i, RGB(mophoBuffer[i][j], mophoBuffer[i][j], mophoBuffer[i][j]));
			}
		}
	}
	else if (viewType == BINARY_CLOSING) {
		CMaskSelect m_dialog; // �� ���̾�α� Ŭ������ ����
		CString modestr; // ���� ���� ����
		if (m_dialog.DoModal() == IDOK) //���
		{
			modestr = m_dialog.maskmode; //���̾�α��� NewName�� �޾� ������ ����
		}
		int shape = _ttoi(modestr) - 1;
		DoSelectMask(shape);
		DoClosing();

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				pDC->SetPixel(j + width + 10, i, RGB(binaryBuffer[i][j], binaryBuffer[i][j], binaryBuffer[i][j]));
				pDC->SetPixel(j + width * 2 + 10 * 2, i, RGB(mophoBuffer[i][j], mophoBuffer[i][j], mophoBuffer[i][j]));
			}
		}
	}
}


void CCV_201211265View::DoImageloadOpencvload()
{
	//1. ���� ���̾�α׷κ��� ��� ��������
	char szFilter[] = "Windows bitmap files(*.bmp) | *.bmp||";
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, (CA2T)szFilter);
	CString fileName;
	if (dlg.DoModal() == IDOK) {
		fileName = dlg.GetPathName();
	}
	else {
		return;
	}

	//2. �̹� �Ҵ�� ����� ���, ������ �Ҵ�� ���� ����
	int i, j;
	if (rgbBuffer != NULL) {
		for (int i = 0; i < height; i++)
			delete[] rgbBuffer[i];
		delete[] rgbBuffer;
	}

	//3. ���� ���� �о����
	CT2CA pszConvertedAnsiString(fileName);
	std::string imgfileName(pszConvertedAnsiString);
	//Mat img = imread(imgfileName, CV_LOAD_IMAGE_COLOR);
	img = imread(imgfileName, CV_LOAD_IMAGE_COLOR);
	width = img.cols;
	height = img.rows;

	//4. �̹����� ������ ��� ���� �Ҵ�
	rgbBuffer = new RGBQUAD*[height];
	for (i = 0; i < height; i++)
		rgbBuffer[i] = new RGBQUAD[width];

	//5. �̹��� ���� ��������
	for (i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			rgbBuffer[i][j].rgbRed = img.at<Vec3b>(i, j)[2];
			rgbBuffer[i][j].rgbGreen = img.at<Vec3b>(i, j)[1];
			rgbBuffer[i][j].rgbBlue = img.at<Vec3b>(i, j)[0];
		}
	}

	//6. ȭ�� ���
	Invalidate(TRUE);
}


void CCV_201211265View::DoOtsuByOpencv()
{
	//OpenCV���� Otsu Method
	Mat gray_img;
	cvtColor(img, gray_img, CV_BGR2GRAY);

	imshow("gray", gray_img);

	Mat otsu_img;
	threshold(gray_img, otsu_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	imshow("otsu", otsu_img);
}


void CCV_201211265View::DoOtsuByOwn()
{
	//0. ���� �Ҵ�� ���� �����ϱ�.
	if (histogram != nullptr)
		delete[] histogram;

	if (grayBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] grayBuffer[i];
		}
		delete[] grayBuffer;
	}

	if (binaryBuffer != nullptr) {
		for (int i = 0; i < height; i++){
			delete[] binaryBuffer[i];
		}
		delete[] binaryBuffer;
	}

	//1. �̹��� �ε��ϱ�
	/*if (rgbBuffer == nullptr) {
		//OmBmpLoad();
		OnImageloadOpencvload();
	}
	*/

	//2. �ε��� �̹��� ����� �°� ���� �Ҵ� �� �ʱ�ȭ
	grayBuffer = new int*[height];
	binaryBuffer = new int*[height];
	for (int i = 0; i < height; i++) {
		grayBuffer[i] = new int[width];
		binaryBuffer[i] = new int[width];
	}
	histogram = new int[256];
	for (int i = 0; i < 256; i++)
		histogram[i] = 0;


	//3. Grayscale �̹��� ��� �� histogram ���
	float sum = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grayBuffer[i][j] = (rgbBuffer[i][j].rgbRed + rgbBuffer[i][j].rgbGreen + rgbBuffer[i][j].rgbBlue) / 3;
			histogram[grayBuffer[i][j]]++;
		}
	}

	//4. �󵵼� * ���� ����
	for (int i = 0; i < 256; i++) {
		sum += (float)(i*histogram[i]);
	}

	//5. ���꿡 ����� ���� �ʱ�ȭ
	float sumB = 0.0f;
	float wB = 0.0f;
	float wF = 0.0f;
	float maxVal = 0;
	thresholdVal = 0;

	//6. �� �ȼ����� threshold�� �����Ͽ��� ��,
	for (int i = 0; i < 256; i++) {
		wB += histogram[i];
		if (wB == 0)
			continue;
		wF = height * width - wB;
		if (wF == 0)
			break;

		sumB += (float)(i*histogram[i]);
		float mB = sumB / wB;
		float mF = (sum - sumB) / wF;
		float between = wB* wF*pow(mB - mF, 2);
		if (between > maxVal) {
			maxVal = between;
			thresholdVal = i;
		}
	}

	//7. ��� ������ ����ȭ ����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grayBuffer[i][j] > thresholdVal)
				binaryBuffer[i][j] = 255;
			else
				binaryBuffer[i][j] = 0;
		}
	}

	//7.2 ������׷� ����� ���� ���� ������ 0-255�� ����
	int maxP = 0;
	int minP = height*width;
	for (int i = 0; i < 256; i++) {
		maxP = histogram[i] > maxP ? histogram[i] : maxP;
		minP = histogram[i] < minP ? histogram[i] : minP;
	}
	for (int i = 0; i < 256; i++) {
		histogram[i] = (histogram[i] - minP) * 255 / (maxP - minP);
	}

	//7.3 ��� �Ķ���� ���� �� ȭ�� ��� �Լ� ȣ��
	//viewType = BINARY_OTSU;
	Invalidate(FALSE);
}

void CCV_201211265View::DoOtsuTwoThreshold()
{
	//0. ���� �Ҵ�� ���� �����ϱ�.
	if (histogram != nullptr)
		delete[] histogram;

	if (grayBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] grayBuffer[i];
		}
		delete[] grayBuffer;
	}

	if (binaryBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] binaryBuffer[i];
		}
		delete[] binaryBuffer;
	}

	//1. �̹��� �ε��ϱ�
	/*if (rgbBuffer == nullptr) {
	//OmBmpLoad();
	OnImageloadOpencvload();
	}
	*/

	//2. �ε��� �̹��� ����� �°� ���� �Ҵ� �� �ʱ�ȭ
	grayBuffer = new int*[height];
	binaryBuffer = new int*[height];
	for (int i = 0; i < height; i++) {
		grayBuffer[i] = new int[width];
		binaryBuffer[i] = new int[width];
	}
	histogram = new int[256];
	for (int i = 0; i < 256; i++)
		histogram[i] = 0;


	//3. Grayscale �̹��� ��� �� histogram ���
	int sum = 0;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grayBuffer[i][j] = (rgbBuffer[i][j].rgbRed + rgbBuffer[i][j].rgbGreen + rgbBuffer[i][j].rgbBlue) / 3;

			if (grayBuffer[i][j] > 5 && grayBuffer[i][j] < 255) {
				histogram[grayBuffer[i][j]]++;
				sum++;
			}
		}
	}

	//5. ���꿡 ����� ���� �ʱ�ȭ
	float w0k = 0.0f;
	float w1k = 0.0f;
	float w2k = 0.0f;

	float m0 = 0.0f;
	float m1 = 0.0f;
	float m2 = 0.0f;

	float m0k = 0.0f;
	float m1k = 0.0f;
	float m2k = 0.0f;
	
	float mT = 0.0f;
	float maxVal = 0.0f;
	float nowVal = 0.0f;
	
	thresholdVal = 0;
	thresholdVal2 = 0;

	//6. �� �ȼ����� threshold�� �����Ͽ��� ��,
	
	//�� ���
	for (int i = 0; i <= 255; i++) {
		mT += i * (histogram[i] / (float)sum);
	}

	for (int t1 = 0; t1 <= 255; t1++) {
		w0k += histogram[t1] / (float)sum;
		m0k += t1 * (histogram[t1] / (float)sum);
		m0 = m0k / w0k;

		w1k = 0;
		m1k = 0;

		for (int t2 = t1 + 1; t2 <= 255; t2++) {
			w1k += histogram[t2] / (float)sum;
			m1k += t2 * (histogram[t2] / (float)sum);
			m1 = m1k / w1k;

			w2k = 1 - (w0k + w1k);
			m2k = mT - (m0k + m1k);

			if (w2k <= 0) break;
			
			m2 = m2k / w2k;

			nowVal = w0k * pow((m0 - mT), 2) + w1k * pow((m1 - mT),2) + w2k * pow((m2 - mT),2);

			if (maxVal <= nowVal) {
				maxVal = nowVal;
				thresholdVal = t1;
				thresholdVal2 = t2;
			}
		}
	}

	//7. ��� ������ ����ȭ ����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grayBuffer[i][j] > thresholdVal) {
				if (grayBuffer[i][j] > thresholdVal2) {
					binaryBuffer[i][j] = 255;
				}
				else {
					binaryBuffer[i][j] = 127;
				}
			}
			else {
				binaryBuffer[i][j] = 0;
			}
		}
	}

	//7.2 ������׷� ����� ���� ���� ������ 0-255�� ����
	int maxP = 0;
	int minP = height*width;
	for (int i = 0; i < 256; i++) {
		maxP = histogram[i] > maxP ? histogram[i] : maxP;
		minP = histogram[i] < minP ? histogram[i] : minP;
	}
	for (int i = 0; i < 256; i++) {
		histogram[i] = (histogram[i] - minP) * 255 / (maxP - minP);
	}

	//7.3 ��� �Ķ���� ���� �� ȭ�� ��� �Լ� ȣ��
	//viewType = BINARY_OTSU;
	Invalidate(FALSE);
}


void CCV_201211265View::DoDilationByOpencv()
{
	Mat gray_img;
	cvtColor(img, gray_img, CV_BGR2GRAY);

	Mat binary_img;
	threshold(gray_img, binary_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	imshow("binary_mag", binary_img);

	Mat dilate_img;
	Mat element(7, 7, CV_8U, Scalar(1));
	dilate(binary_img, dilate_img, Mat());

	imshow("dilated", dilate_img);
}


void CCV_201211265View::DoErosionByOpencv()
{
	Mat gray_img;
	cvtColor(img, gray_img, CV_BGR2GRAY);

	Mat binary_img;
	threshold(gray_img, binary_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

	imshow("binary_mag", binary_img);

	Mat erode_img;
	Mat element(7, 7, CV_8U, Scalar(1));
	erode(binary_img, erode_img, Mat());

	imshow("eroded", erode_img);
}



void CCV_201211265View::DoSelectMask(int shape)
{
	const int SHAPE_33RECT = 0;
	const int SHAPE_55RECT = 1;
	const int SHAPE_33DIAMOND = 2;
	const int SHAPE_55DIAMOND = 3;
	const int SHAPE_13BAR = 4;
	const int SHAPE_31BAR = 5;
	const int SHAPE_55CIRCLE = 6;

	boolean fill = false;

	switch (shape) {
	case SHAPE_33RECT:
		row = 3;
		col = 3;
		fill = true;
		break;
	case SHAPE_55RECT:
		row = 5;
		col = 5;
		fill = true;
		break;
	case SHAPE_33DIAMOND:
		row = 3;
		col = 3;
		fill = false;
		break;
	case SHAPE_55DIAMOND:
		row = 5;
		col = 5;
		fill = false;
		break;
	case SHAPE_13BAR:
		row = 1;
		col = 3;
		fill = true;
		break;
	case SHAPE_31BAR:
		row = 3;
		col = 1;
		fill = true;
		break;
	case SHAPE_55CIRCLE:
		row = 5;
		col = 5;
		fill = false;
		break;
	}
	mask = new int*[row];
	for (int i = 0; i < col; i++) {
		mask[i] = new int[col];
	}

	if (fill) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				mask[i][j] = 255;
			}
		}
	}
	else {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				mask[i][j] = 0;
			}
		}

		switch (shape) {
		case SHAPE_33DIAMOND:
			mask[0][1] = 255;
			mask[1][0] = 255;
			mask[1][1] = 255;
			mask[1][2] = 255;
			mask[2][1] = 255;
			break;
		case SHAPE_55DIAMOND:
			mask[0][2] = 255;

			mask[1][1] = 255;
			mask[1][2] = 255;
			mask[1][3] = 255;
			
			mask[2][0] = 255;
			mask[2][1] = 255;
			mask[2][2] = 255;
			mask[2][3] = 255;
			mask[2][4] = 255;
			
			mask[3][1] = 255;
			mask[3][2] = 255;
			mask[3][3] = 255;
			
			mask[4][2] = 255;
			break;
		case SHAPE_55CIRCLE:
			mask[0][1] = 255;
			mask[0][2] = 255;
			mask[0][3] = 255;

			mask[1][0] = 255;
			mask[1][1] = 255;
			mask[1][2] = 255;
			mask[1][3] = 255;
			mask[1][4] = 255;

			mask[2][0] = 255;
			mask[2][1] = 255;
			mask[2][2] = 255;
			mask[2][3] = 255;
			mask[2][4] = 255;

			mask[3][0] = 255;
			mask[3][1] = 255;
			mask[3][2] = 255;
			mask[3][3] = 255;
			mask[3][4] = 255;

			mask[4][1] = 255;
			mask[4][2] = 255;
			mask[4][3] = 255;
			break;
		}
	}


}

void CCV_201211265View::DoDilationOwn()
{
	//����ũ dilation������ ����
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mask[i][j] = 255 - mask[i][j];
		}
	}

	if (grayBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] grayBuffer[i];
		}
		delete[] grayBuffer;
	}

	if (binaryBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] binaryBuffer[i];
		}
		delete[] binaryBuffer;
	}

	if (mophoBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] mophoBuffer[i];
		}
		delete[] mophoBuffer;
	}
	//1. �ε��� �̹��� ����� �°� ���� �Ҵ� �� �ʱ�ȭ
	grayBuffer = new int*[height];
	binaryBuffer = new int*[height];
	mophoBuffer = new int*[height];
	for (int i = 0; i < height; i++) {
		grayBuffer[i] = new int[width];
		binaryBuffer[i] = new int[width];
		mophoBuffer[i] = new int[width];
	}
	//2. Grayscale �̹��� ��� �� histogram ���
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grayBuffer[i][j] = (rgbBuffer[i][j].rgbRed + rgbBuffer[i][j].rgbGreen + rgbBuffer[i][j].rgbBlue) / 3;
			mophoBuffer[i][j] = 0;
		}
	}
	//3. ��� ������ ����ȭ ����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grayBuffer[i][j] > 127)
				binaryBuffer[i][j] = 255;
			else
				binaryBuffer[i][j] = 0;
		}
	}
	int center_row = (row - 1) / 2;
	int center_col = (col - 1) / 2;
	//4. ����ũ �����Ű��
	for (int i = 0; i < height - row + 1; i++) {
		for (int j = 0; j < width - col + 1; j++) {

			boolean chk_mask = true;
			for (int x = 0; x < row; x++) {
				for (int y = 0; y < col; y++) {
					if (binaryBuffer[i + x][j + y] != mask[x][y]) {
						chk_mask = false;
					}
				}
			}

			if (chk_mask) {
				mophoBuffer[i + center_row][j + center_col] = 0;
			}
			else {
				mophoBuffer[i + center_row][j + center_col] = 255;
			}
		}
	}

	//����ũ �ٽ� ���󺹱�
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mask[i][j] = 255 - mask[i][j];
		}
	}
}


void CCV_201211265View::DoErosionOwn()
{
	if (grayBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] grayBuffer[i];
		}
		delete[] grayBuffer;
	}

	if (binaryBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] binaryBuffer[i];
		}
		delete[] binaryBuffer;
	}

	if (mophoBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] mophoBuffer[i];
		}
		delete[] mophoBuffer;
	}
	//1. �ε��� �̹��� ����� �°� ���� �Ҵ� �� �ʱ�ȭ
	grayBuffer = new int*[height];
	binaryBuffer = new int*[height];
	mophoBuffer = new int*[height];
	for (int i = 0; i < height; i++) {
		grayBuffer[i] = new int[width];
		binaryBuffer[i] = new int[width];
		mophoBuffer[i] = new int[width];
	}
	//2. Grayscale �̹��� ��� �� histogram ���
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grayBuffer[i][j] = (rgbBuffer[i][j].rgbRed + rgbBuffer[i][j].rgbGreen + rgbBuffer[i][j].rgbBlue) / 3;
			mophoBuffer[i][j] = 0;
		}
	}
	//3. ��� ������ ����ȭ ����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grayBuffer[i][j] > 127)
				binaryBuffer[i][j] = 255;
			else
				binaryBuffer[i][j] = 0;
		}
	}
	int center_row = (row - 1) / 2;
	int center_col = (col - 1) / 2;
	//4. ����ũ �����Ű��
	for (int i = 0; i < height-row+1; i++) {
		for (int j = 0; j < width-col+1; j++) {

			boolean chk_mask = true;
			for (int x = 0; x < row; x++) {
				for (int y = 0; y < col; y++) {
					if (binaryBuffer[i + x][j + y] != mask[x][y]) {
						chk_mask = false;
					}
				}
			}

			if (chk_mask) {
				mophoBuffer[i+center_row][j+center_col] = 255;
			}
			else {
				mophoBuffer[i+center_row][j+center_col] = 0;
			}
		}
	}

}


void CCV_201211265View::DoOpening()
{
	if (grayBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] grayBuffer[i];
		}
		delete[] grayBuffer;
	}

	if (binaryBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] binaryBuffer[i];
		}
		delete[] binaryBuffer;
	}

	if (mophoBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] mophoBuffer[i];
		}
		delete[] mophoBuffer;
	}
	//1. �ε��� �̹��� ����� �°� ���� �Ҵ� �� �ʱ�ȭ
	int** tempBuffer = new int*[height];
	grayBuffer = new int*[height];
	binaryBuffer = new int*[height];
	mophoBuffer = new int*[height];
	for (int i = 0; i < height; i++) {
		grayBuffer[i] = new int[width];
		binaryBuffer[i] = new int[width];
		mophoBuffer[i] = new int[width];
		tempBuffer[i] = new int[width];
	}
	//2. Grayscale �̹��� ��� �� histogram ���
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grayBuffer[i][j] = (rgbBuffer[i][j].rgbRed + rgbBuffer[i][j].rgbGreen + rgbBuffer[i][j].rgbBlue) / 3;
			mophoBuffer[i][j] = 0;
			tempBuffer[i][j] = 0;
		}
	}
	//3. ��� ������ ����ȭ ����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grayBuffer[i][j] > 127)
				binaryBuffer[i][j] = 255;
			else
				binaryBuffer[i][j] = 0;
		}
	}
	int center_row = (row - 1) / 2;
	int center_col = (col - 1) / 2;

	//4. Erosion ����ũ �����Ű��
	for (int i = 0; i < height - row + 1; i++) {
		for (int j = 0; j < width - col + 1; j++) {

			boolean chk_mask = true;
			for (int x = 0; x < row; x++) {
				for (int y = 0; y < col; y++) {
					if (binaryBuffer[i + x][j + y] != mask[x][y]) {
						chk_mask = false;
					}
				}
			}

			if (chk_mask) {
				tempBuffer[i + center_row][j + center_col] = 255;
			}
			else {
				tempBuffer[i + center_row][j + center_col] = 0;
			}
		}
	}

	//5. Dilation �ϱ�
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mask[i][j] = 255 - mask[i][j];
		}
	}
	for (int i = 0; i < height - row + 1; i++) {
		for (int j = 0; j < width - col + 1; j++) {

			boolean chk_mask = true;
			for (int x = 0; x < row; x++) {
				for (int y = 0; y < col; y++) {
					if (tempBuffer[i + x][j + y] != mask[x][y]) {
						chk_mask = false;
					}
				}
			}

			if (chk_mask) {
				mophoBuffer[i + center_row][j + center_col] = 0;
			}
			else {
				mophoBuffer[i + center_row][j + center_col] = 255;
			}
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mask[i][j] = 255 - mask[i][j];
		}
	}

}


void CCV_201211265View::DoClosing()
{

	if (grayBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] grayBuffer[i];
		}
		delete[] grayBuffer;
	}

	if (binaryBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] binaryBuffer[i];
		}
		delete[] binaryBuffer;
	}

	if (mophoBuffer != nullptr) {
		for (int i = 0; i < height; i++) {
			delete[] mophoBuffer[i];
		}
		delete[] mophoBuffer;
	}
	//1. �ε��� �̹��� ����� �°� ���� �Ҵ� �� �ʱ�ȭ
	int** tempBuffer = new int*[height];
	grayBuffer = new int*[height];
	binaryBuffer = new int*[height];
	mophoBuffer = new int*[height];
	for (int i = 0; i < height; i++) {
		grayBuffer[i] = new int[width];
		binaryBuffer[i] = new int[width];
		mophoBuffer[i] = new int[width];
		tempBuffer[i] = new int[width];
	}
	//2. Grayscale �̹��� ��� �� histogram ���
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			grayBuffer[i][j] = (rgbBuffer[i][j].rgbRed + rgbBuffer[i][j].rgbGreen + rgbBuffer[i][j].rgbBlue) / 3;
			mophoBuffer[i][j] = 0;
			tempBuffer[i][j] = 0;
		}
	}
	//3. ��� ������ ����ȭ ����
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (grayBuffer[i][j] > 127)
				binaryBuffer[i][j] = 255;
			else
				binaryBuffer[i][j] = 0;
		}
	}
	int center_row = (row - 1) / 2;
	int center_col = (col - 1) / 2;

	//4. Dilation �ϱ�
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mask[i][j] = 255 - mask[i][j];
		}
	}
	for (int i = 0; i < height - row + 1; i++) {
		for (int j = 0; j < width - col + 1; j++) {

			boolean chk_mask = true;
			for (int x = 0; x < row; x++) {
				for (int y = 0; y < col; y++) {
					if (binaryBuffer[i + x][j + y] != mask[x][y]) {
						chk_mask = false;
					}
				}
			}

			if (chk_mask) {
				tempBuffer[i + center_row][j + center_col] = 0;
			}
			else {
				tempBuffer[i + center_row][j + center_col] = 255;
			}
		}
	}
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			mask[i][j] = 255 - mask[i][j];
		}
	}

	//5. Erosion ����ũ �����Ű��
	for (int i = 0; i < height - row + 1; i++) {
		for (int j = 0; j < width - col + 1; j++) {

			boolean chk_mask = true;
			for (int x = 0; x < row; x++) {
				for (int y = 0; y < col; y++) {
					if (tempBuffer[i + x][j + y] != mask[x][y]) {
						chk_mask = false;
					}
				}
			}

			if (chk_mask) {
				mophoBuffer[i + center_row][j + center_col] = 255;
			}
			else {
				mophoBuffer[i + center_row][j + center_col] = 0;
			}
		}
	}
}
