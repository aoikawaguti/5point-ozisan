#include "DxLib.h"
void paint();
int floorBlock = DxLib::LoadGraph("dlmap/angurasakaba.png");
int floorBlock2 = DerivationGraph(0, 128, 16, 16, floorBlock);
int mouse;
int clickX, clickY;
int i, j;
int newClick, oldClick;
int map[13][22] =
{//�}�b�v�`�b�v
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
	SetDrawScreen(DX_SCREEN_BACK);
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		SetDrawScreen(DX_SCREEN_BACK);//�`���𗠉�ʂ�
		/*newClick = (GetMouseInput() & MOUSE_INPUT_LEFT);
		if (oldClick == 0 && newClick == 1) {
			GetMousePoint(&clickX, &clickY);
			oldClick = newClick;//�����Ă����Ԃ�
		}
		else if (oldClick == 1 && newClick == 0) {//�}�E�X�����ꂽ�牟���Ă��Ȃ�
			oldClick = 0;
		}*/
		paint();
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
		}
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}