#include <iostream>
#include <Windows.h>

//x64
//Безвредная программа, выход - ALT + F4

int scrWidth, scrHeight; // Ширина экрана Высота экрана
int interval = 100; // Частота движения потоков экрана в ms

// Создание эффекта плывущего экрана
LRESULT CALLBACK Melt(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
		case WM_CREATE: {
			HDC desktop = GetDC(HWND_DESKTOP);
			HDC window = GetDC(hWnd);

			BitBlt(window, 0, 0, scrWidth, scrHeight, desktop, 0, 0, SRCCOPY);

			ReleaseDC(hWnd, window);
			ReleaseDC(HWND_DESKTOP, desktop);

			SetTimer(hWnd, 0, interval, 0);
			ShowWindow(hWnd, SW_SHOW);

			break;
		}
		case WM_PAINT: {
			ValidateRect(hWnd, 0);

			break;
		}
		case WM_TIMER: {
			HDC Window = GetDC(hWnd);

			int x = (rand() % scrWidth) - (200 / 2),
				y = (rand() % 15),
				width = (rand() % 200);

			BitBlt(Window, x, y, width, scrHeight, Window, x, 0, SRCCOPY);

			ReleaseDC(hWnd, Window);

			break;
		}
		case WM_DESTROY: {
			KillTimer(hWnd, 0);

			PostQuitMessage(0);

			break;
		}
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int APIENTRY main(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int showCmd) { // ДЛЯ х86 убираем APIENTRY

	// Получаем ширину и высоту дисплея
	scrWidth = GetSystemMetrics(SM_CXSCREEN);
	scrHeight = GetSystemMetrics(SM_CYSCREEN);

	WNDCLASS wndClass = { 0, Melt, 0, 0, inst, 0, LoadCursorW(0, IDC_ARROW), 0, 0, L"ScreenMelting" };

	if (RegisterClass(&wndClass)) {
		// Создаём перекрывающее окно "melter"
		HWND hWnd = CreateWindowExW(WS_EX_TOPMOST, L"ScreenMelting", 0, WS_POPUP, 0, 0, scrWidth, scrHeight, HWND_DESKTOP, 0, inst, 0);

		if (hWnd) {
			// Начальное значение для рандомизации
			srand(GetTickCount());

			MSG msg = { 0 };

			// Запускаем цикл "melter"а
			while (msg.message != WM_QUIT) {
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}
}