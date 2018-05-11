#include "DxLib.h"
void paint();
int floorBlock = DxLib::LoadGraph("dlmap/angurasakaba.png");
int floorBlock2 = DerivationGraph(0, 128, 16, 16, floorBlock);
int mouse;
int clickX, clickY;
int i, j;
int newClick, oldClick;
int map[13][22] =
{//マップチップ
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
};

void init() {
	floorBlock = DxLib::LoadGraph("dlmap/angurasakaba.png");
	floorBlock2 = DerivationGraph(0, 128, 16, 16, floorBlock);
}

void paint() {//描画関数
	for (j = 0; j < 13; j++) {
		for (i = 0; i < 22; i++) {
		
			switch (map[j][i]) {
			case 0:
				
				break;
			case 1:
				DrawExtendGraph(i * 60, j * 60, i * 60 + 60, j * 60 + 60, floorBlock2, TRUE);
				break;
			}
		}
	}
}
// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(1320,780,32);
	if (DxLib_Init() == -1)	// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}
	init();
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		SetDrawScreen(DX_SCREEN_BACK);//描画先を裏画面に
		/*newClick = (GetMouseInput() & MOUSE_INPUT_LEFT);
		if (oldClick == 0 && newClick == 1) {
			GetMousePoint(&clickX, &clickY);
			oldClick = newClick;//押している状態へ
		}
		else if (oldClick == 1 && newClick == 0) {//マウスが離れたら押していない
			oldClick = 0;
		}*/
		paint();
		ScreenFlip();//裏画面を表画面にコピー
		}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}