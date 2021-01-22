
#include <Windows.h>

UINT8 flags = 1;

// position and size

	POINT pos   = { 32, 32 };
	SIZE  size  = { 32, 32 };

// graphics

	COLORREF	key   = RGB(253, 255, 254);
	HBRUSH		back  = CreateSolidBrush(key);

	HDC			gfx;
	PAINTSTRUCT	ps;

static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	static HWND hWnd;
	static WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_NOCLOSE | CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = 0;//LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = 0;
	wc.hbrBackground = back;//(HBRUSH)COLOR_DESKTOP;
	wc.lpszClassName = "DualpointMain";

	RegisterClassEx(&wc);

	hWnd = CreateWindowEx(
		WS_EX_NOACTIVATE | WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW,
		"DualpointMain", "",
		WS_POPUP,
		32, 32,
		32, 32,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hWnd, nCmdShow);

	SetWindowLong(hWnd, -20, (GetWindowLong(hWnd, -20) | 524288L | 128L | 32L));

	SetLayeredWindowAttributes(hWnd, key, 128, LWA_COLORKEY);


	static MSG msg;

	while (TRUE)
	{
		pos.x += 1;

		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		//while (GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		Sleep(20);

		SetWindowPos(hWnd, HWND_TOPMOST,
			pos.x, pos.y,
			size.cx, size.cy,
			SWP_NOACTIVATE | SWP_NOREDRAW);

	}

	return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		if (flags & 1)
		{
			flags &= ~1;
			gfx = BeginPaint(hWnd, &ps);

			FillRect(gfx, &ps.rcPaint, (HBRUSH)COLOR_DESKTOP);
			EndPaint(hWnd, &ps);
		}
		break;
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
