#include "DxLib.h"
#include <stdio.h>
#define MAP_X 22//�}�b�v�̉���
#define MAP_Y 13//�}�b�v�̏c��
void init();
void fileread();
void paint();

int floorBlock;
int floorBlock2;
int i, j;

int stageNum;//���݉��X�e�[�W�ڂ�
int newClick, oldClick;
int map[MAP_Y][MAP_X];//�}�b�v�`�b�v

void init() {
	floorBlock = DxLib::LoadGraph("dlmap/angurasakaba.png");
	floorBlock2 = DerivationGraph(0, 128, 16, 16, floorBlock);
	stageNum = 1;
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
	init();
	fileread();
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�

		newClick = (GetMouseInput() & MOUSE_INPUT_LEFT);
		if (oldClick == 0 && newClick == 1) {
		stageNum++;
		fileread();
		oldClick = newClick;//�����Ă����Ԃ�
		}
		else if (oldClick == 1 && newClick == 0) {//�}�E�X�����ꂽ�牟���Ă��Ȃ�
		oldClick = 0;
		}
		paint();
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}