#include <windows.h>

#include "include/color.h"
#include "include/ray.h"

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


bool hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = r.origin() - center;
	double a = dot(r.direction(), r.direction());
	double b = 2.0 * dot(oc, r.direction());
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4 * a * c;
	return (discriminant >= 0);
}

color ray_color(const ray& r) {
	if (hit_sphere(point3(0, 0, -1), 0.5, r))
		return color(1, 0, 0);

	vec3 unit_direction = unit_vector(r.direction());
	auto a = 0.5 * (unit_direction.y() + 1.0);
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
				point3 pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
				vec3 ray_direction = pixel_center - camera_center;
				ray r(camera_center, ray_direction);

				color pixel_color = ray_color(r);
				
				write_color(hdc, i, j, pixel_color);
			}
		}

		EndPaint(hWnd, &ps);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}

