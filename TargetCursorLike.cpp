/* 
    レイ(光線)を利用した当たり判定の再現
    DirectX9の勉強中,D3DXIntersect関数でお世話になったので。
    擬似的に2Dでもやってみた。
*/

#include "DxLib.h"
#define WINDOW_RES_WIDTH 640
#define WINDOW_RES_HEIGHT 480

struct chara
{
	int x, y;
	int RayplusX, RayminusX, RayplusY, RayminusY;
	const int color = 0xff0000;
};

int map[15][20]
{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};


int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	SetOutApplicationLogValidFlag(FALSE);
	SetGraphMode(WINDOW_RES_WIDTH, WINDOW_RES_HEIGHT, 32);
	SetWindowTextA("やみのま！");
	ChangeWindowMode(false);
	chara unkoman = { 320,240 };
	unkoman.RayminusX = unkoman.RayplusX = unkoman.x;
	unkoman.RayminusY = unkoman.RayplusY = unkoman.y;
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClearDrawScreen();
		if (CheckHitKey(KEY_INPUT_UP)) unkoman.y -= 3;
		if (CheckHitKey(KEY_INPUT_DOWN)) unkoman.y += 3;
		if (CheckHitKey(KEY_INPUT_LEFT)) unkoman.x -= 3;
		if (CheckHitKey(KEY_INPUT_RIGHT)) unkoman.x += 3;
		if (unkoman.x > 600) unkoman.x = 600;
		if (unkoman.x < 40) unkoman.x = 40;
		if (unkoman.y > 440) unkoman.y = 440;
		if (unkoman.y < 40) unkoman.y = 40;
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				switch (map[i][j])
				{
				case 1:
					DrawBox(j * 32, i * 32, j * 32 + 32, i * 32 + 32, 0x0000ff, true);
					break;
				default:
					break;
				}
			}
		}
		DrawBox(unkoman.x - 8, unkoman.y - 8, unkoman.x + 8, unkoman.y + 8, unkoman.color, false);
		DrawLine(unkoman.x + 8, unkoman.y, WINDOW_RES_WIDTH - 32, unkoman.y, 0x00ffff);
		DrawLine(unkoman.x - 9, unkoman.y, 32, unkoman.y, 0x00ffff);
		DrawLine(unkoman.x, unkoman.y - 9, unkoman.x, 32, 0x00ffff);
		DrawLine(unkoman.x, unkoman.y + 8, unkoman.x, WINDOW_RES_HEIGHT - 32, 0x00ffff);
		DrawString(0, 0, "↑←↓→キーで移動", 0xffffff,0xff0000);
		ScreenFlip();
	}
	DxLib_End();
	return 0;
}