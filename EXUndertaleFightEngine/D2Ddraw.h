#pragma once
#include <wincodec.h>
#include <d2d1.h>
#include <assert.h>
#include <Windows.h>
#include <dwmapi.h>
#include <easyx.h>
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "Dwmapi.lib")

class D2Ddraw {
public:
	D2Ddraw(IMAGE* image);
	~D2Ddraw();
	void begin_draw();
	void end_draw();
	void draw_line(POINT, POINT);
	void draw_circle(POINT, int);
	void fill_circle(POINT, int);
	void draw_ellipse(POINT, int, int);
	void fill_ellipse(POINT, int, int);
	void draw_rectangle(POINT, POINT);
	void fill_rectangle(POINT, POINT);
	void draw_round_rectrange(POINT, POINT, float, float);
	void fill_round_rectrange(POINT, POINT, float, float);
	void set_brush_thickness(float);
	void set_brush_color(COLORREF);
	void set_fill_color(COLORREF);
	COLORREF get_fill_color();
	COLORREF get_brush_color();
private:
	template <class T> void DxObjectSafeRelease(T** ppT);
	void auto_begin_draw();
	void auto_end_draw();
private:
	bool begin = false, end = false;
	ID2D1Factory* Factory = NULL;
	ID2D1DCRenderTarget* DCRenderTarget = NULL;
	ID2D1SolidColorBrush* Brush = NULL;
	float brush_thick_ness = 2.f;
	COLORREF brush_color = WHITE;
	COLORREF fill_color = WHITE;
};