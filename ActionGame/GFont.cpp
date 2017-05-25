#include "stdafx.h"
#include "GFont.h"


GFont::GFont()
{
}


GFont::~GFont()
{
}

void GFont::Load(Device device, String type)
{
	D3DXCreateFont(device, 25, 0, FW_BOLD, 1, false, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY
		, DEFAULT_PITCH | FF_DONTCARE, type.c_str(), &font);
}
void GFont::Draw(Sprite sprite, String text, int x, int y)
{
	RECT rt = { x, y, 0, 0 };
	font->DrawTextA(sprite, text.c_str(), -1, &rt, DT_NOCLIP, 0xff000000);
}