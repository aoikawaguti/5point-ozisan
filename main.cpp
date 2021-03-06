#include "DxLib.h"
#include <stdio.h>
#define MAP_X 22//マップの横幅
#define MAP_Y 13//マップの縦幅
enum {
STATE_TITLE,
STATE_MAIN,
STATE_END
};
void init();
int title();
int gamemain();
int gameend();
void fileread();
void paint();
int btnX, btnY;
int btnWidth, btnHeight;
int floorBlock;
int floorBlock2;
int i, j;
int x, y;
int gameState;
int stageNum;//現在何ステージ目か
int newClick, oldClick;
int map[MAP_Y][MAP_X];//マップチップ

void init() {
	floorBlock = DxLib::LoadGraph("dlmap/angurasakaba.png");
	floorBlock2 = DerivationGraph(0, 128, 16, 16, floorBlock);
	stageNum = 1;
	gameState = 0;
	btnX = 500;
	btnY = 600;
	btnWidth = 240;
	btnHeight = 100;
}
int title() {
	DrawBox(btnX, btnY, btnX + btnWidth, btnY + btnHeight,GetColor(255,255,255),TRUE);
	newClick = (GetMouseInput() & MOUSE_INPUT_LEFT);
	if (oldClick == 0 && newClick == 1) {
		GetMousePoint(&x, &y);
		oldClick = newClick;//押している状態へ
		if (x > btnX && x < btnX + btnWidth && y < btnY + btnHeight && y > btnY) {
			return STATE_MAIN;//スタートボタンが押されたらゲームへ
		}
	}
	return STATE_TITLE;
}
int gamemain() {
	paint();
	return STATE_MAIN;
}
int gameend() {
	DrawBox(btnX, btnY, btnX + btnWidth, btnY + btnHeight, GetColor(255, 255, 255), TRUE);
	newClick = (GetMouseInput() & MOUSE_INPUT_LEFT);
	if (oldClick == 0 && newClick == 1) {
		GetMousePoint(&x, &y);
		oldClick = newClick;//押している状態へ
		if (x > btnX && x < btnX + btnWidth && y < btnY + btnHeight && y > btnY) {
			return STATE_TITLE;//スタートボタンが押されたらゲームへ
		}
	}
	return STATE_END;
}
void fileread() {
	FILE *fp;
	bool eofFlag = false;
	int gyou = 0;
	int retu = 0;
	int enemyCnt = 0;//マップのエネミー数
	int c;
	char buf[10];
	char fileName[30] = "MapData";
	char fileNameEnd[5] = ".csv";

	sprintf(&fileName[7], "%d", stageNum);//MapDataに現在のステージ番号連結
	strcat(fileName, fileNameEnd);		  //MapData??に.csvを連結
	fp = fopen(fileName, "r");			  //fpを読み取り形式で開く
	while (1) {
		while (1) {
			c = fgetc(fp);
			if (c == EOF) {
				eofFlag = true;//EndOfFileの時にループを抜ける
				break;
			}
			if (c != ',' && c != '\n') {
				strcat(buf, (const char*)&c);//cがセルの区切りか改行でなければ、bufに連結する
			}
			else {
				int num = atoi(buf);//bufをint型に直して、即席のローカル変数numに代入
				if (num == 8 || num == 9 || num == 10) {//敵なら
					enemyCnt++;
				}
				map[gyou][retu] = num;
				memset(buf, 0, sizeof(buf));//bufをリセット
				break;//区切りか改行ならループを抜ける
			}
		}
		//1セル分のループを抜けたら
		if (eofFlag)break;
		if (c == ',')retu++;
		if (c == '\n') {//改行だったら行を増やす
			gyou++;
			retu = 0;
		}
	}

	enemyCnt = 0;
	fclose(fp);
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
	SetDrawScreen(DX_SCREEN_BACK);
	init();
	fileread();
	
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//裏画面消す
		switch (gameState) {
		case STATE_TITLE:gameState = title(); break;
		case STATE_MAIN:gameState = gamemain(); break;
		case STATE_END:gameState = gameend(); break;
		}
		newClick = (GetMouseInput() & MOUSE_INPUT_LEFT);
		if (oldClick == 0 && newClick == 1) {
		stageNum++;
		fileread();
		oldClick = newClick;//押している状態へ
		}
		else if (oldClick == 1 && newClick == 0) {//マウスが離れたら押していない
		oldClick = 0;
		}
		ScreenFlip();//裏画面を表画面にコピー
	}
	InitGraph();
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}