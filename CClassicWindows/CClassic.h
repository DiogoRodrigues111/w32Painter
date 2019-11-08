#pragma once
/*
	Ainda não implementado
*/
/* 

for (i = 0; i < 6; i++) {
			hPen = ExtCreatePen(PS_COSMETIC | dwPenStyle[i], 1, &lB, 0, NULL);
			hOldPen = SelectObject(hDC, hPen);
			MoveToEx(hDC, rc.left + (i * 20), rc.top, NULL);
			LineTo(hDC, rc.left + (i * 20), rc.bottom);
			SelectObject(hDC, hOldPen);
			DeleteObject(hPen);
		}

		rc.left += 150;

		for (i = 0; i < 6; i++) {
			lB.lbStyle = BS_HATCHED;
			lB.lbColor = RGB(255, 0, 0);
			lB.lbHatch = uHatch[i];

			hPen = ExtCreatePen(PS_GEOMETRIC, 5, &lB, 0, NULL);
			hOldPen = SelectObject(hDC, hPen);
			MoveToEx(hDC, rc.left + (i * 20), rc.top, NULL);
			LineTo(hDC, rc.left + (i * 20), rc.bottom);
			SelectObject(hDC, hOldPen);
			DeleteObject(hPen);
		}

		MoveToEx(hDC, rc.left + (6 * 20), rc.top, &point);
					LineTo(hDC, rc.left + (6 * 20), rc.bottom);
					SelectObject(hDC, hPen);

	case WM_LBUTTONUP:
				if (bDraw) {
					hDC = GetDC(hWnd);
					MoveToEx(hDC, point.x, point.y, NULL);
					LineTo(hDC, LOWORD(lParam), LOWORD(lParam));
					ReleaseDC(hWnd, hDC);
				}
				bDraw = FALSE;
				break;


						rc.left += 10;
		rc.right += 10;
		rc.bottom -= 10;

		lB.lbColor = RGB(255, 0, 0);
		lB.lbStyle = BS_SOLID;
		lB.lbHatch = 0;

// Evento de chamada
INT_PTR CALLBACK EventDraw(
	_In_ HWND hWnd,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam)
{
	BOOL bDraw = FALSE;

	switch (uMsg) {
	case WM_LBUTTONDOWN:
		bDraw = TRUE;
		point.x = LOWORD(lParam);
		point.y = LOWORD(lParam);
		return 0L;
	case WM_LBUTTONUP:
		if (bDraw) {
			hDC = GetDC(hWnd);
			MoveToEx(hDC, point.x, point.y, NULL);
			LineTo(hDC, LOWORD(lParam), LOWORD(lParam));
			ReleaseDC(hWnd, hDC);
		}
		bDraw = FALSE;
		return 0L;
	case WM_MOUSEMOVE:
		if (bDraw) {
			MoveToEx(hDC, point.x, point.y, NULL);
			LineTo(hDC, point.x = LOWORD(lParam), point.y = HIWORD(lParam));
			ReleaseDC(hWnd, hDC);
		}
		return 0L;
	}

	return (INT_PTR)FALSE;
}

*/