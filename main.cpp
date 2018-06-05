#include "DxLib.h"
#include <stdio.h>
#define MAP_X 22//�}�b�v�̉���
#define MAP_Y 13//�}�b�v�̏c��
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
int stageNum;//���݉��X�e�[�W�ڂ�
int newClick, oldClick;
int map[MAP_Y][MAP_X];//�}�b�v�`�b�v

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
		oldClick = newClick;//�����Ă����Ԃ�
		if (x > btnX && x < btnX + btnWidth && y < btnY + btnHeight && y > btnY) {
			return STATE_MAIN;//�X�^�[�g�{�^���������ꂽ��Q�[����
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
		oldClick = newClick;//�����Ă����Ԃ�
		if (x > btnX && x < btnX + btnWidth && y < btnY + btnHeight && y > btnY) {
			return STATE_TITLE;//�X�^�[�g�{�^���������ꂽ��Q�[����
		}
	}
	return STATE_END;
}
void fileread() {
	FILE *fp;
	bool eofFlag = false;
	int gyou = 0;
	int retu = 0;
	int enemyCnt = 0;//�}�b�v�̃G�l�~�[��
	int c;
	char buf[10];
	char fileName[30] = "MapData";
	char fileNameEnd[5] = ".csv";

	sprintf(&fileName[7], "%d", stageNum);//MapData�Ɍ��݂̃X�e�[�W�ԍ��A��
	strcat(fileName, fileNameEnd);		  //MapData??��.csv��A��
	fp = fopen(fileName, "r");			  //fp��ǂݎ��`���ŊJ��
	while (1) {
		while (1) {
			c = fgetc(fp);
			if (c == EOF) {
				eofFlag = true;//EndOfFile�̎��Ƀ��[�v�𔲂���
				break;
			}
			if (c != ',' && c != '\n') {
				strcat(buf, (const char*)&c);//c���Z���̋�؂肩���s�łȂ���΁Abuf�ɘA������
			}
			else {
				int num = atoi(buf);//buf��int�^�ɒ����āA���Ȃ̃��[�J���ϐ�num�ɑ��
				if (num == 8 || num == 9 || num == 10) {//�G�Ȃ�
					enemyCnt++;
				}
				map[gyou][retu] = num;
				memset(buf, 0, sizeof(buf));//buf�����Z�b�g
				break;//��؂肩���s�Ȃ烋�[�v�𔲂���
			}
		}
		//1�Z�����̃��[�v�𔲂�����
		if (eofFlag)break;
		if (c == ',')retu++;
		if (c == '\n') {//���s��������s�𑝂₷
			gyou++;
			retu = 0;
		}
	}

	enemyCnt = 0;
	fclose(fp);
}

void paint() {//�`��֐�
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
// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(1320,780,32);
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	init();
	fileread();
	
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		switch (gameState) {
		case STATE_TITLE:gameState = title(); break;
		case STATE_MAIN:gameState = gamemain(); break;
		case STATE_END:gameState = gameend(); break;
		}
		newClick = (GetMouseInput() & MOUSE_INPUT_LEFT);
		if (oldClick == 0 && newClick == 1) {
		stageNum++;
		fileread();
		oldClick = newClick;//�����Ă����Ԃ�
		}
		else if (oldClick == 1 && newClick == 0) {//�}�E�X�����ꂽ�牟���Ă��Ȃ�
		oldClick = 0;
		}
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}
	InitGraph();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}