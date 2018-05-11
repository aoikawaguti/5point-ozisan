#include "DxLib.h"

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(1920, 1080, 32);
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	SetDrawScreen(DX_SCREEN_BACK);
	int floorBlock = DxLib::LoadGraph("dlmap/angurasakaba.png");
	int floorBlock2 = DerivationGraph(0,128,48,64,floorBlock);
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		/*for (int i = 0; i < 10; i++) {
			DrawExtendGraph(i * 200, 800, i* 200 + 200, 1080, floorBlock2, TRUE);
		}*/
		ScreenFlip();//裏画面を表画面にコピー
	}

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}