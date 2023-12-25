#include <windows.h>

#include "include/rtweekend.h"
#include "include/color.h"
#include "include/ray.h"
#include "include/sphere.h"
#include "include/hittable.h"
#include "include/hittable_list.h"

//win
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("rt-win");

//ray-tracer
constexpr double aspect_ratio = 16.0 / 9.0;
int image_width;
int image_height;
double viewport_height;
double viewport_width;
double focal_length;
point3 camera_center = point3(0, 0, 0);
vec3 viewport_u;
vec3 viewport_v;
vec3 pixel_delta_u;
vec3 pixel_delta_v;
point3 viewport_upper_left;
point3 pixel00_loc;
hittable_list world;


//한 광선이 월드에 있는 오브젝트와 교차하는지 검사한다.
color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	//교차하면 rec에 정보가 저장되고 then이 실행됨.
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}
	vec3 unit_direction = unit_vector(r.direction());
	double a = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}

//main
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	//ray-tracer
	image_width = 400;
	image_height = static_cast<int>(image_width / aspect_ratio);
	image_height = (image_height < 1) ? 1 : image_height;

	//world
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
	
	//cam
	focal_length = 1.0;
	viewport_height = 2.0;
	viewport_width = viewport_height * (static_cast<double>(image_width) / image_height);
	camera_center = point3(0, 0, 0);
	viewport_u = vec3(viewport_width, 0, 0);
	viewport_v = vec3(0, -viewport_height, 0);
	pixel_delta_u = viewport_u / image_width;
	pixel_delta_v = viewport_v / image_height;
	viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u / 2 - viewport_v / 2;
	pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


	//win
	HWND hWnd;
	WNDCLASS WndClass{
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
	RegisterClass(&WndClass);

	g_hInst = hInstance;

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, image_width + 16, image_height + 39,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	

	//event loop
	MSG Message{};
	while (GetMessage(&Message, NULL, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	DestroyWindow(hWnd);
	UnregisterClass(WndClass.lpszClassName, WndClass.hInstance);
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
				point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
				vec3 ray_direction = pixel_center - camera_center;
				ray r(camera_center, ray_direction);

				color pixel_color = ray_color(r, world);
				
				write_color(hdc, i, j, pixel_color);
			}
		}

		EndPaint(hWnd, &ps);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

