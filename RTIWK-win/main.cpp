#include <windows.h>

#include "include/color.h"


//win
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("DrawText");

//ray-tracer
constexpr double aspect_ratio = 16.0 / 9.0;
int image_width;
int image_height;
double viewport_height;
double viewport_width;

//main
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, image_width + 16, image_height + 39,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	//ray-tracer
	image_width = 400;
	image_height = static_cast<const int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	viewport_height = 2.0f;
	viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);

	//event loop
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		// Render
		for (int j = 0; j < image_height; ++j) {
			for (int i = 0; i < image_width; ++i) {
				color pixel_color = color(double(i) / (image_width - 1), double(j) / (image_height - 1), 0);
				write_color(hdc, i, j, pixel_color);
			}
		}

		EndPaint(hWnd, &ps);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

