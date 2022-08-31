// OpenGLtestView.cpp: COpenGLtestView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "OpenGLtest.h"
#endif

#include "OpenGLtestDoc.h"
#include "OpenGLtestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//키보드 입력을 위한 값 생성
#define VK_KEY_A	0x41
#define VK_KEY_D	0x44 
#define VK_KEY_W	0x57 
#define VK_KEY_S	0x53       
#define VK_KEY_1	0x31
#define VK_KEY_2	0x32 
#define VK_OEM_PLUS	0xBB
#define VK_OEM_MINUS	0xBD

//속도를 위한 키값 생성
int n = 1;
float speed = 0.00;
//SetPixelformat
// desc: function to set the pixel format for the device context
// 
BOOL COpenGLtestView::SetDevicePixelFormat(HDC hdc)
{
	int pixelformat;

	PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_GENERIC_FORMAT |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0, 0, 0, 0, 0, 0,
		8,
		0,
		8,
		0, 0, 0, 0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0,
	};

	if ((pixelformat = ChoosePixelFormat(hdc, &pfd)) == FALSE) {
		MessageBox(LPCTSTR("ChoosepixelFormat failed"), LPCTSTR("Error"), MB_OK);
		return FALSE;
	}

	if (SetPixelFormat(hdc, pixelformat, &pfd) == FALSE) {
		MessageBox(LPCTSTR("SetPixelFormat failed"), LPCTSTR("Error"), MB_OK);
		return FALSE;
	}
	return TRUE;
}


// COpenGLtestView

IMPLEMENT_DYNCREATE(COpenGLtestView, CView)

BEGIN_MESSAGE_MAP(COpenGLtestView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &COpenGLtestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COpenGLtestView 생성/소멸

COpenGLtestView::COpenGLtestView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

COpenGLtestView::~COpenGLtestView()
{
}

BOOL COpenGLtestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// COpenGLtestView 그리기

void COpenGLtestView::OnDraw(CDC* /*pDC*/)
{
	COpenGLtestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	DrawGLScene();
	Invalidate(FALSE);
}
/*
void DrawTriangle()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(0.f, 0.f, 0.f, 1.f, 1.f, 0.f, 0.f, 1.f, 0.f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBegin(GL_TRIANGLES);
	glColor4f(1.0, 0.0, 0.0, 0.5);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 1.0, 0.0);

	glEnd();
}
*/
void COpenGLtestView::drawTriangle()
{
	glBegin(GL_TRIANGLES);
	glNormal3f(0.577, 0.577, 0.577);
	glVertex3f(1, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

// COpenGLtestView 메시지 처리기
void COpenGLtestView::InitGL(GLvoid)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	m_B911400.initialize();
	m_mouseMove = FALSE;
	//회전각을 위한 초기화
	rotate_x =  0.0;
	rotate_y = 0.0;
	rotate_z = 0.0;
	//카메라 위치 초기화
	m_camera_x = 0.0;
	m_camera_y = 3.0;
	m_camera_z = 3;
	
}

void COpenGLtestView::ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)
		height = 1;

	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
void COpenGLtestView::DrawGLScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//카메라 뷰
	gluLookAt(m_camera_x * (n-1), m_camera_y * (n-1) + 3, m_camera_z * (n - 1) + 4.5, (m_camera_x + rotate_x)*(n-1), (m_camera_y + rotate_y-1.5)*(n-1), (m_camera_z + rotate_z-4.5)*(n-1)-3, 0.f, 1.f, 0.f);
	//마우스를 이용한 카메라 뷰 설정
	GLdouble angleX, angleY;
	if (m_mouseMove)
	{
	angleX = 1 * (m_mouseCurrentPoint.x - m_mouseAnchorPoint.x);
	angleY = 1 * (m_mouseCurrentPoint.y - m_mouseAnchorPoint.y);
	glRotatef(angleX, 0, 1, 0);
	glRotatef(angleY, 1, 0, 0);
	}
	

	//B911400.cpp을 통해 빛 생성
	m_B911400.drawSphere();

	glClear(GL_COLOR_BUFFER_BIT);
	glRotatef(rotate_x, rotate_y, rotate_z, 1);
	glPointSize(1); // set point size 
	glBegin(GL_POINTS);
	//공간 상에서의 점들을 통해 이동 시 위치 확인을 할 수 있는 별 생성.
	for (int i = -50; i < 50; i += 2)
	{
		for (int j = -50; j < 50; j += 2)
		{
			for (int k = -50; k < 50; k += 2)
			{
				glVertex3f(i, j, k);
			}
		}
	}

	glEnd();
	glFlush();
	//처음 위치에서 z축 방향을 쉽게 알 수 있도록 화살표 모양 생성.
	glPointSize(30);
	glBegin(GL_POINTS);
	glVertex3f(0, 0, 0);
	glVertex3f(-0.15, 0, 0.15);
	glVertex3f(0.15, 0, 0.15);
	glVertex3f(0, 0, 0.2);
	glVertex3f(-0.25, 0, 0.35);
	glVertex3f(0.25, 0, 0.35);
	glVertex3f(0, 0, 0.4);
	glVertex3f(0, 0, 0.6);
	glVertex3f(0, 0, 0.8);
	glVertex3f(0, 0, 1);

	glEnd();
	glFlush();

	// 물체 회전 설정
	glTranslatef(rotate_x, rotate_y, rotate_z);
	glRotatef(-rotate_x * 10, 0, 1, 0);
	glRotatef(rotate_y * 10, 1, 0, 0);


	//비행체를 삼각형 3개를 이용하여 비행기 모양을 만듬.
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	glVertex3f(0, 0.5, -1.5);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0.5, -1.5);
	glVertex3f(-0.5, 0.5, 0);
	glVertex3f(0, 1, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0.5, -1.5);
	glVertex3f(0.5, 0.5, 0);
	glVertex3f(0, 1, 0);


	glEnd();
	
	//swap buffer
	SwapBuffers(m_hDC); 
}


// COpenGLtestView 인쇄


void COpenGLtestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL COpenGLtestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void COpenGLtestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void COpenGLtestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void COpenGLtestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void COpenGLtestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// COpenGLtestView 진단

#ifdef _DEBUG
void COpenGLtestView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLtestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLtestDoc* COpenGLtestView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLtestDoc)));
	return (COpenGLtestDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLtestView 메시지 처리기


int COpenGLtestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	m_hDC = GetDC()->m_hDC;

	// set the pixel format
	if (!SetDevicePixelFormat(m_hDC))
	{
		return -1;
	}
	m_hglRC = wglCreateContext(m_hDC);
	wglMakeCurrent(m_hDC, m_hglRC);

	InitGL();
	return 0;
}


void COpenGLtestView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	m_B911400.destroy();

	wglMakeCurrent(m_hDC, NULL);
	wglDeleteContext(m_hglRC);
}



void COpenGLtestView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	ReSizeGLScene(cx, cy);
}

//각 키에 따르는 마우스 포인터를 이용한 설정(385줄~408줄)
void COpenGLtestView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mouseMove = TRUE;
	m_mouseAnchorPoint = point;
	CView::OnLButtonDown(nFlags, point);
}


void COpenGLtestView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mouseMove = FALSE;
	CView::OnLButtonUp(nFlags, point);
}


void COpenGLtestView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_mouseCurrentPoint = point;
	CView::OnMouseMove(nFlags, point);
} 


void COpenGLtestView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//키보드 +,-,a,d,w,s,1,2 각 키에 따르는 설정. (속도 증감, 물체 회전, 카메라 회전, 카메라 기본 설정)
	switch (nChar) {
	case VK_OEM_PLUS://+(=)키
		speed += 0.01;
		break;
	case VK_OEM_MINUS://-(_)키
		speed -= 0.01;
		break;
	case VK_KEY_A://A키
		rotate_x -= 0.03 + speed;
		rotate_z -= 0.03 +speed;
		m_camera_x -= 0.04 + speed;
		m_camera_z -= 0.025 + speed;
		break;
	case VK_KEY_D://D키
		rotate_x += 0.03 + speed;
		rotate_z -= 0.03 + speed;
		m_camera_x += 0.04 + speed;
		m_camera_z -= 0.025 + speed;
		break;
	case VK_KEY_W://W키
		rotate_y += 0.03 + speed;
		rotate_z -= 0.03 + speed;
		m_camera_y += 0.04 + speed;
		m_camera_z -= 0.025 + speed;
		break;
	case VK_KEY_S://S키
		rotate_y -= 0.03 + speed;
		rotate_z -= 0.03 + speed;
		m_camera_y -= 0.04 + speed;
		m_camera_z -= 0.025 +speed;
		break;
	case VK_KEY_1://1(!)키
		n = 1;
		m_camera_x = 0.0;
		m_camera_y = 3.0;
		m_camera_z = 3.0;
		break;
	case VK_KEY_2://2(@)키
		n = 2;
		m_camera_x = m_camera_x * n;
		m_camera_y = m_camera_y * n - 3;
		m_camera_z = m_camera_z * n ;
		break;
	} 
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


