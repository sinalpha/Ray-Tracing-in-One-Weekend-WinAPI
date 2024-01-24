#include <windows.h>
#include <memory>

#include "include/rtweekend.h"
#include "include/camera.h"
#include "include/hittable_list.h"
#include "include/sphere.h"
#include "include/color.h"
#include "include/material.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("rt-win");

std::unique_ptr<hittable_list> world = std::make_unique<hittable_list>(hittable_list());
std::unique_ptr<camera> cam = std::make_unique<camera>(camera());

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
	auto material_left = make_shared<dielectric>(1.5);
	auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

	//world
	world->add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world->add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world->add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world->add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.4, material_left));
	world->add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
	
	//cam
	cam->aspect_ratio = 16.0 / 9.0;
	cam->image_width = 400;
	cam->image_height = static_cast<int>(cam->image_width / cam->aspect_ratio);
	cam->image_height = (cam->image_height < 1) ? 1 : cam->image_height;
	cam->max_depth = 100;
	
	
	//win
	WNDCLASS wc{
		CS_HREDRAW | CS_VREDRAW,
		WndProc,
		0,
		0,
		hInstance,
		LoadIcon(NULL, IDI_APPLICATION),
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)GetStockObject(WHITE_BRUSH),
		NULL,
		lpszClass,
	};
	RegisterClass(&wc);

	g_hInst = hInstance;
	RECT wr = { 0, 0, cam->image_width, cam->image_height };
	AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);
	HWND hWnd = CreateWindow(wc.lpszClassName, lpszClass,
		WS_OVERLAPPEDWINDOW,
		800,
		400, 
		wr.right - wr.left, 
		wr.bottom - wr.top,
		NULL, (HMENU)NULL, wc.hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	
	MSG Message{};
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	DestroyWindow(hWnd);
	UnregisterClass(wc.lpszClassName, wc.hInstance);
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

		cam->render(hdc, *world);

		EndPaint(hWnd, &ps);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

