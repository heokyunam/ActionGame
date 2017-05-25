#pragma once
class GFont
{
private:
	LPD3DXFONT font;
public:
	GFont();
	~GFont();
	void Load(Device device, String type);
	void Draw(Sprite sprite, String text, int x, int y);
};

