#include "stdafx.h"
#include "MyBitmap.h"


CMyBitmap::CMyBitmap()
{
}


CMyBitmap::~CMyBitmap()
{
	Release();
}

void CMyBitmap::Load_Bmp(const TCHAR * _pFilePath)
{
	// �̹����� �׸� Ÿ�ֿ̹� �Ź� �ҷ����⸦ �ϸ� ������ Ŀ���� �ȴ�.
	// ȿ�������� �����ϱ� ���� �̹����� �ҷ��� �� �׷� ���´�.
	// �̹����� �׷� ���� DC�� �ʿ��ѵ�, GetDC()�� DC������ �׸��ٸ�?
	// GetDC()�� ������ DC�� ȭ�鿡 ����ϴ� DC�̹Ƿ� �ǹ̰� �������� �ȴ�.
	// �̸� �ذ��ϱ� ���� ���ο� DC�� �ʿ��ѵ� ������ ����ϴ� DC�� ȣȯ�� �Ǵ� DC�� �ʿ��ϴ�.
	// ##1. GetDC()�� DC�� �ҷ��´�.
	// ##2. CreateCompatibleDC()�� ȣȯ�Ǵ� DC�� �Ҵ��Ѵ�. -> ���� �Ѵ�.
	// ##3. �ҷ��� DC�� ReleaseDC()�� ���� �����ش�.
	HDC hDC = GetDC(g_hWnd);
	m_hMemDC = CreateCompatibleDC(hDC);
	ReleaseDC(g_hWnd, hDC);

	// LoadImage()
	// LR_LOADFROMFILE : ���Ͽ��� �̹����� �ҷ����ڴ�.
	// LR_CREATEDIBSECTION : �о�� ������ DIB ���·� ��ȯ�ϰڴ�.
	m_hBitmap = (HBITMAP)LoadImage(NULL, _pFilePath, IMAGE_BITMAP, 0, 0
		, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

	// SelectObject()
	// LoadImage�� ��Ʈ���� ������ ������ �ִ� ���� / �׸��� �ʰ� �ִ�.
	// ��Ʈ���� �׸��� ���� m_hMemDC�� �غ��Ͽ�����,���� ���õ� GDI ������Ʈ�� ����Ʈ ���̴�.
	// SelectObject() ������ �������ִ� �Լ��̴�.
	// ��, GDI ������Ʈ�� �����ϱ� ���� ������ ������ �ִ� ������ ��ȯ�Ѵ�.
	m_hOldBmp = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);

}

void CMyBitmap::Release()
{
	SelectObject(m_hMemDC, m_hOldBmp);
	DeleteObject(m_hBitmap);
	DeleteDC(m_hMemDC);
}
