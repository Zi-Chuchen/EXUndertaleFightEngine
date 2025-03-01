#pragma once
#include <easyx.h>
#include "camera.h"
//用于存放工具

#define PI 3.1415926

#pragma comment(lib,"msimg32.lib")

void putimage_alpha(int x, int y, IMAGE* in) {
	AlphaBlend(GetImageHDC(GetWorkingImage()), x , y , in->getwidth(), in->getheight(), GetImageHDC(in), 0, 0, in->getwidth(), in->getheight(), { AC_SRC_OVER,0,255,AC_SRC_ALPHA });
}

void putimage_alpha(int x, int y, IMAGE* srcimg, UINT transparentcolor)
{
	HDC dstDC = GetImageHDC(GetWorkingImage());
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x , y , w, h, srcDC, 0, 0, w, h, transparentcolor);
}

IMAGE rotateimage_alpha(IMAGE pImg, double radian, COLORREF bkcolor = BLACK, RECT* result = NULL)
{
	IMAGE pImge = pImg;
	radian = -radian;														// 由于 y 轴翻转，旋转角度需要变负
	float fSin = (float)sin(radian), fCos = (float)cos(radian);				// 存储三角函数值
	float fNSin = (float)sin(-radian), fNCos = (float)cos(-radian);
	int left = 0, top = 0, right = 0, bottom = 0;							// 旋转后图像顶点
	int w = pImge.getwidth(), h = pImge.getheight();
	DWORD* pBuf = GetImageBuffer(&pImge);
	POINT points[4] = { {0, 0}, {w, 0}, {0, h}, {w, h} };					// 存储图像顶点
	for (int j = 0; j < 4; j++)												// 旋转图像顶点，搜索旋转后的图像边界
	{
		points[j] = {
			(int)(points[j].x * fCos - points[j].y * fSin),
			(int)(points[j].x * fSin + points[j].y * fCos)
		};
		if (points[j].x < points[left].x)	left = j;
		if (points[j].y > points[top].y)	top = j;
		if (points[j].x > points[right].x)	right = j;
		if (points[j].y < points[bottom].y)	bottom = j;
	}

	int nw = points[right].x - points[left].x;								// 旋转后的图像尺寸
	int nh = points[top].y - points[bottom].y;
	int nSize = nw * nh;
	int offset_x = points[left].x < 0 ? points[left].x : 0;					// 旋转后图像超出第一象限的位移（据此调整图像位置）
	int offset_y = points[bottom].y < 0 ? points[bottom].y : 0;

	IMAGE img(nw, nh);
	DWORD* pNewBuf = GetImageBuffer(&img);
	if (bkcolor != BLACK)													// 设置图像背景色
		for (int i = 0; i < nSize; i++)
			pNewBuf[i] = BGR(bkcolor);

	for (int i = offset_x, ni = 0; ni < nw; i++, ni++)						// i 用于映射原图像坐标，ni 用于定位旋转后图像坐标
	{
		for (int j = offset_y, nj = 0; nj < nh; j++, nj++)
		{
			int nx = (int)(i * fNCos - j * fNSin);							// 从旋转后的图像坐标向原图像坐标映射
			int ny = (int)(i * fNSin + j * fNCos);
			if (nx >= 0 && nx < w && ny >= 0 && ny < h)						// 若目标映射在原图像范围内，则拷贝色值
				pNewBuf[nj * nw + ni] = pBuf[ny * w + nx];
			if (result != NULL) {
				if (nx == 0 && ny == 0) {
					result->left = ni;
					result->top = nj;
				}
				else if (nx == w - 1 && ny == h - 1) {
					result->right = ni;
					result->bottom = nj;
				}
			}
		}
	}
	/*if (result != NULL) {
		result->left = left;
		result->right = right;
		result->bottom = bottom;
		result->top = top;
	}*/
	return img;
}

void rotate_putimage(IMAGE* image,double rotate_r, POINT rotate_o = { 0,0 }) {
	RECT i;
	IMAGE r_image = rotateimage_alpha(*image, rotate_r, BLACK, &i);
	putimage_alpha(-i.left + rotate_o.x, -i.top + rotate_o.x, &r_image);
}
