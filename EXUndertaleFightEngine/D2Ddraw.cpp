#include "D2Ddraw.h"

D2Ddraw::D2Ddraw(IMAGE* image) {
	HRESULT ResultHandle = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&Factory
	);
	auto Property = D2D1::RenderTargetProperties(
		D2D1_RENDER_TARGET_TYPE::D2D1_RENDER_TARGET_TYPE_HARDWARE,
		D2D1::PixelFormat(
			DXGI_FORMAT_B8G8R8A8_UNORM,
			D2D1_ALPHA_MODE_IGNORE
		), 0.0, 0.0, D2D1_RENDER_TARGET_USAGE_GDI_COMPATIBLE, D2D1_FEATURE_LEVEL_DEFAULT
	);
	HRESULT Result = Factory->CreateDCRenderTarget(
		&Property,
		&DCRenderTarget
	);
	RECT WindowRect = { 0, 0,getwidth(), getheight() };
	if (image) {
		WindowRect = { 0, 0,image->getwidth(), image->getheight() };
	}
	DCRenderTarget->BindDC(GetImageHDC(image), &WindowRect);
	if (FAILED(Result))
	{
		assert(!"D2D Facotry Created Failed\n");
	}
	DCRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		&Brush
	);
	if (!Brush)
	{
		assert(!"D2D Brush Created Failed\n");
	}
}

D2Ddraw::~D2Ddraw() {
	DxObjectSafeRelease(&DCRenderTarget);
	DxObjectSafeRelease(&Brush);
	DxObjectSafeRelease(&Factory);
}

void D2Ddraw::begin_draw() {
	DCRenderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE::D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	DCRenderTarget->BeginDraw();
	begin = true;
	end = false;
}
void D2Ddraw::end_draw() {
	DCRenderTarget->EndDraw();
	end = true;
	begin = false;
}
void D2Ddraw::draw_line(POINT start, POINT end) {
	auto_begin_draw();
	if (!Brush)
	{
		assert(!"D2D Brush Dosen't Create\n");
	}
	DCRenderTarget->DrawLine(D2D1_POINT_2F{ start.x + 0.f, start.y + 0.f }, D2D1_POINT_2F{ end.x + 0.f, end.y + 0.f }, Brush, brush_thick_ness);
	auto_end_draw();
}
void D2Ddraw::draw_circle(POINT pos, int radius) {
	auto_begin_draw();
	if (!Brush)
	{
		assert(!"D2D Brush Dosen't Create\n");
	}
	DCRenderTarget->DrawEllipse(D2D1_ELLIPSE{ D2D1_POINT_2F{ pos.x + 0.f,pos.y + 0.f }, radius + 0.f, radius + 0.f }, Brush, brush_thick_ness);
	auto_end_draw();
}
void D2Ddraw::fill_circle(POINT pos, int radius) {
	auto_begin_draw();
	if (!Brush)
	{
		assert(!"D2D Brush Dosen't Create\n");
	}
	COLORREF brush_old_color = get_brush_color();
	set_brush_color(get_fill_color());
	DCRenderTarget->FillEllipse(D2D1_ELLIPSE{ D2D1_POINT_2F{ pos.x + 0.f,pos.y + 0.f }, radius + 0.f, radius + 0.f }, Brush);
	set_brush_color(brush_old_color);
	auto_end_draw();
}
void D2Ddraw::draw_ellipse(POINT pos, int x_radius, int y_radius) {
	auto_begin_draw();
	if (!Brush)
	{
		assert(!"D2D Brush Dosen't Create\n");
	}
	DCRenderTarget->DrawEllipse(D2D1_ELLIPSE{ D2D1_POINT_2F{ pos.x + 0.f,pos.y + 0.f }, x_radius + 0.f, y_radius + 0.f }, Brush, brush_thick_ness);
	auto_end_draw();
}
void D2Ddraw::fill_ellipse(POINT pos, int x_radius, int y_radius) {
	auto_begin_draw();
	if (!Brush)
	{
		assert(!"D2D Brush Dosen't Create\n");
	}
	COLORREF brush_old_color = get_brush_color();
	set_brush_color(get_fill_color());
	draw_ellipse(pos, x_radius, y_radius);
	DCRenderTarget->FillEllipse(D2D1_ELLIPSE{ D2D1_POINT_2F{ pos.x + 0.f,pos.y + 0.f }, x_radius + 0.f, y_radius + 0.f }, Brush);
	set_brush_color(brush_old_color);
	auto_end_draw();
}
void D2Ddraw::draw_rectangle(POINT left_top, POINT right_bottom) {
	auto_begin_draw();
	if (!Brush)
	{
		assert(!"D2D Brush Dosen't Create\n");
	}
	int left = left_top.x;
	int top = left_top.y;
	int right = right_bottom.x;
	int bottom = right_bottom.y;
	DCRenderTarget->DrawRectangle(D2D_RECT_F{ left + 0.f,top + 0.f,right + 0.f,bottom + 0.f }, Brush, brush_thick_ness);
	auto_end_draw();
}
void D2Ddraw::fill_rectangle(POINT left_top, POINT right_bottom) {
	auto_begin_draw();
	if (!Brush)
	{
		assert(!"D2D Brush Dosen't Create\n");
	}
	int left = left_top.x;
	int top = left_top.y;
	int right = right_bottom.x;
	int bottom = right_bottom.y;
	COLORREF brush_old_color = get_brush_color();
	set_brush_color(get_fill_color());
	DCRenderTarget->FillRectangle(D2D_RECT_F{ left + 0.f,top + 0.f,right + 0.f,bottom + 0.f }, Brush);
	set_brush_color(brush_old_color);
	auto_end_draw();
}
void D2Ddraw::draw_round_rectrange(POINT left_top, POINT right_bottom, float x_radius, float y_radius) {
	auto_begin_draw();
	if (!Brush)
	{
		assert(!"D2D Brush Dosen't Create\n");
	}
	int left = left_top.x;
	int top = left_top.y;
	int right = right_bottom.x;
	int bottom = right_bottom.y;
	DCRenderTarget->DrawRoundedRectangle(D2D1_ROUNDED_RECT{ D2D_RECT_F{ left + 0.f,top + 0.f,right + 0.f,bottom + 0.f },x_radius,y_radius }, Brush, brush_thick_ness);
	auto_end_draw();
}
void D2Ddraw::fill_round_rectrange(POINT left_top, POINT right_bottom, float x_radius, float y_radius) {
	auto_begin_draw();
	if (!Brush)
	{
		assert(!"D2D Brush Dosen't Create\n");
	}
	int left = left_top.x;
	int top = left_top.y;
	int right = right_bottom.x;
	int bottom = right_bottom.y;
	COLORREF brush_old_color = get_brush_color();
	set_brush_color(get_fill_color());
	DCRenderTarget->FillRoundedRectangle(D2D1_ROUNDED_RECT{ D2D_RECT_F{ left + 0.f,top + 0.f,right + 0.f,bottom + 0.f } ,x_radius,y_radius }, Brush);
	set_brush_color(brush_old_color);
	auto_end_draw();
}
void D2Ddraw::set_brush_thickness(float brush_thick_ness) {
	this->brush_thick_ness = brush_thick_ness;
}
void D2Ddraw::set_brush_color(COLORREF color) {
	brush_color = color;
	if (Brush) {
		DxObjectSafeRelease(&Brush);
	}
	DCRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF(GetRValue(color) / 255.f, GetGValue(color) / 255.f, GetBValue(color) / 255.f)),
		&Brush
	);
}
void D2Ddraw::set_fill_color(COLORREF fill_color) {
	this->fill_color = fill_color;
}
COLORREF D2Ddraw::get_fill_color() {
	return fill_color;
}
COLORREF D2Ddraw::get_brush_color() {
	return brush_color;
}
template <class T> void D2Ddraw::DxObjectSafeRelease(T** ppT)
{
	if (*ppT)
	{
		(*ppT)->Release();
		*ppT = NULL;
	}
}
void D2Ddraw::auto_begin_draw() {
	if (!begin)
		begin_draw();
}
void D2Ddraw::auto_end_draw() {
	if (!end)
		end_draw();
}