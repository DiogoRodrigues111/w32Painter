/*
	Este programa exerce as funcionalidades de desenho Windows GDI da biblioteca wingdi.h
	O codigo está disponível na minha pagina para download no Github :https://github.com/DiogoRodrigues111 
	Este código fornece o poder da Linguagem C para Windows Win32 API
															Criado por Diogo Rodrigues Roessler (dez 2019)
*/

#include "CClassic.h"

#include <Windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <wingdi.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpStr, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR OpenFileDialog(HWND hWnd);

/* Funções ainda não implementada */
//INT_PTR CALLBACK EventDraw(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//INT_PTR CALLBACK Draw(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

static TCHAR lpClassName[] = _T("WindowClassOne");
static TCHAR lpWindowName[] = _T("Editor v001");

HINSTANCE hInstance;
POINT point;

int WINAPI WinMain(		
				_In_ HINSTANCE hInst,
				_In_opt_ HINSTANCE hPrevInstance,
				_In_ LPSTR lpStr,
				_In_ int nCmdShow)
{
	hInstance = hInst;
	WNDCLASSEX wc;

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW|CS_HREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = lpClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL,
			_T("Falha ao carregar a class pai, tente contactar o proprietário do Software para mais informações"),
			_T("WARRING: Class has FAILED - Não pode harmonizar as funcionalidades"),
			MB_ICONINFORMATION | MB_OK);
		return 1;
	}

	HWND hWnd = CreateWindow(lpClassName,
		lpWindowName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1024, 786, NULL,
		(HMENU)NULL, hInstance, NULL);

	if (!hWnd) {
		MessageBox(NULL,
			_T("Falha ao carregar a janela pai, tente contactar o proprietário do Software para mais informações"),
			_T("WARRING: Window has FAILED - Não pode harmonizar as funcionalidades da Janela Pai"),
			MB_ICONINFORMATION | MB_OK);
		return 1;
	}

	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG Msg;
	while (GetMessage(&Msg, NULL, 0, 0) != 0) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return (INT)Msg.wParam;
}

LRESULT CALLBACK WndProc(	
						_In_ HWND hWnd,
						_In_ UINT uMsg,
						_In_ WPARAM wParam,
						_In_ LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	RECT rc;
	int i = 0;
	HBRUSH hBrush = NULL;
	BOOL bDraw = FALSE;
	HPEN hPen = NULL;
	HDC hCompatibleDC;
	COLORREF color;

	DWORD dwPenStyle[] = {
	PS_DASH,
	PS_DASHDOT,
	PS_DOT,
	PS_INSIDEFRAME,
	PS_NULL,
	PS_SOLID
	};

	UINT uHatch[] = {
		HS_BDIAGONAL,
		HS_CROSS,
		HS_DIAGCROSS,
		HS_FDIAGONAL,
		HS_HORIZONTAL,
		HS_VERTICAL
	};

	switch (uMsg)
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);
		hCompatibleDC = CreateCompatibleDC(hDC);
		SelectObject(hCompatibleDC, hPen);
		color = GetBkColor(hDC);
		hBrush = CreateSolidBrush(color);
		ReleaseDC(hWnd, hDC);
		hPen = CreatePen(PS_SOLID, 6, RGB(0, 0, 0));
		return 0;

	case WM_PAINT:
		GetClientRect(hWnd, &rc);

		hDC = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		break;

	case WM_LBUTTONDOWN:
		bDraw = TRUE;
		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		return 0;
	case WM_LBUTTONUP:
		if (IntersectRect(&rc, &rc, &rc))
		{

			// Erase the bitmap rectangle by filling it with  
			// the background color.  

			hDC = GetDC(hWnd);
			FillRect(hDC, &rc, color);

			// Redraw the target rectangle because the part  
			// that intersected with the bitmap rectangle was  
			// erased by the call to FillRect.  

			Rectangle(hDC, rc.left, rc.top,
				rc.right, rc.bottom);

			// Copy the bitmap into the target rectangle.  

			StretchBlt(hDC, rc.left + 1, rc.top + 1,
				(rc.right - rc.left) - 2,
				(rc.bottom - rc.top) - 2, hCompatibleDC,
				0, 0, 32, 32, SRCCOPY);

			// Copy the target rectangle to the bitmap  
			// rectangle, set the coordinates of the target  
			// rectangle to 0, then reset the fDragRect flag.  

			CopyRect(&rc, &rc);
			SetRectEmpty(&rc);
			ReleaseDC(hWnd, hDC);
			bDraw = FALSE;
		}

		else if (bDraw)
		{

			// Draw the bitmap rectangle, copy the bitmap into  
			// it, and reset the fDragRect flag.  

			hDC = GetDC(hWnd);
			Rectangle(hDC, rc.left, rc.top,
				rc.right, rc.bottom);
			StretchBlt(hDC, rc.left + 1, rc.top + 1,
				(rc.right - rc.left) - 2,
				(rc.bottom - rc.top) - 2, hCompatibleDC,
				0, 0, 32, 32, SRCCOPY);
			ReleaseDC(hWnd, hDC);
			bDraw = FALSE;
		}

		// Release the mouse cursor.  

		ClipCursor((LPRECT)NULL);
		return 0;
	case WM_MOUSEMOVE:
		bDraw = TRUE;
		if (bDraw) {
			if ((wParam && MK_LBUTTON)
				&& !bDraw) {
				hDC = GetDC(hWnd);
				SetROP2(hDC, R2_NOTXORPEN);

				if (!IsRectEmpty(&rc))
				{
					Rectangle(hDC, rc.left, rc.top,
						rc.right, rc.bottom);
				}

				if (point.x < (LONG)LOWORD(lParam) 
					&& point.y >(LONG)HIWORD(lParam)) {
					SetRect(&rc, point.x, HIWORD(lParam), LOWORD(lParam), point.y);
				}
				else if ((point.x > (LONG)LOWORD(lParam)) &&
					(point.y > (LONG)HIWORD(lParam)))
				{
					SetRect(&rc, LOWORD(lParam),
						HIWORD(lParam), point.x, point.y);
				}
				else if ((point.x > (LONG)LOWORD(lParam)) &&
					(point.y < (LONG)HIWORD(lParam)))
				{
					SetRect(&rc, LOWORD(lParam), point.y,
						point.x, HIWORD(lParam));
				}
				else
				{
					SetRect(&rc, point.x, point.y, LOWORD(lParam),
						HIWORD(lParam));
				}
				Rectangle(hDC, rc.left, rc.top,
					rc.right, rc.bottom);
				ReleaseDC(hWnd, hDC);
			}
			else if ((wParam && MK_LBUTTON)
				&& bDraw)
			{

				// Set the mix mode so that the pen color is the  
				// inverse of the background color.  

				hDC = GetDC(hWnd);
				SetROP2(hDC, R2_NOTXORPEN);

				// Select the dotted pen into the DC and erase  
				// the previous bitmap rectangle by drawing  
				// another rectangle on top of it.  

				SelectObject(hDC, hPen);

				// Set the new coordinates of the bitmap rectangle,  
				// then redraw it.  

				OffsetRect(&rc, LOWORD(lParam) - point.x,
					HIWORD(lParam) - point.y);
				Rectangle(hDC, rc.left, rc.top,
					rc.right, rc.bottom);
				ReleaseDC(hWnd, hDC);

				// Save the coordinates of the mouse cursor.  

				point.x = (LONG)LOWORD(lParam);
				point.y = (LONG)HIWORD(lParam);
			}
		}
		FillRect(ps.hdc, &ps.rcPaint, hBrush);
		return 0;

	case WM_COMMAND:
		break;

	case WM_DESTROY:
		DeleteObject(color);
		DeleteDC(hCompatibleDC);
		PostQuitMessage(EXIT_SUCCESS);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	return 0;
}

/* Open File System */
INT_PTR OpenFileDialog(
					_In_ HWND hWnd) 
{
	OPENFILENAME ofn;
	char szFile[260];

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.nMaxFile = sizeof(szFile);
	ofn.nMaxFileTitle = 0;
	ofn.nFilterIndex = 1;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrDefExt = NULL;
	ofn.hwndOwner = hWnd;
	ofn.hInstance = hInstance;
	ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
	ofn.dwReserved = 0;

	if (GetOpenFileName(&ofn)) {
		
	}
	else
	{ }

	return 0;
}