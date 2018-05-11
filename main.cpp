#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE);
	SetGraphMode(1920, 1080, 32);
	if (DxLib_Init() == -1)	// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	int floorBlock = DxLib::LoadGraph("dlmap/angurasakaba.png");
	int floorBlock2 = DerivationGraph(0,128,48,64,floorBlock);
	while (ProcessMessage() == 0)
	{
		ClearDrawScreen();//����ʏ���
		/*for (int i = 0; i < 10; i++) {
			DrawExtendGraph(i * 200, 800, i* 200 + 200, 1080, floorBlock2, TRUE);
		}*/
		ScreenFlip();//����ʂ�\��ʂɃR�s�[
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}