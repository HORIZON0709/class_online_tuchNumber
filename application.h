//================================================
//
//������H��b[application.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�O���錾
//***************************
class CRenderer;
class CTexture;

class CObject2D;

//***************************
//�A�v���P�[�V�����N���X�̒�`
//***************************
class CApplication
{/* ��{�N���X */
private: /* �萔�̒�` */
	static const int MAX_POLYGON = 25;	//�|���S���̍ő吔
	static const int NUM_COLUMN = 5;	//��(X��)�̐�
	static const int NUM_ROW = 5;		//�s(Y��)�̐�

	static const float POLYGON_SIZE;	//�|���S���̃T�C�Y
	static const float START_POS_X;		//�ŏ��̃|���S���̈ʒu(X��)
	static const float START_POS_Y;		//�ŏ��̃|���S���̈ʒu(Y��)

public: /* �ÓI�����o�֐� */
	static CTexture* GetTexture();		//�e�N�X�`�������擾
	static CRenderer* GetRenderer();	//�����_���[�����擾

	static void DrawTime(LPD3DXFONT pFont);	//���Ԃ�\��

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CApplication();
	~CApplication();

public: /* �����o�֐� */
	HRESULT Init(HWND hWnd, BOOL bWindow,HINSTANCE hInstance);	//������

	void Uninit();	//�I��
	void Update();	//�X�V
	void Draw();	//�`��
private:
	void Shuffle();						//�V���b�t��

private: /* �ÓI�����o�ϐ� */
	static CTexture* m_pTexture;	//�e�N�X�`���̃|�C���^
	static CRenderer* m_pRenderer;	//�����_���[�̃|�C���^

	static CObject2D* m_apObject[MAX_POLYGON];	//2D�I�u�W�F�N�g�̃|�C���^

	static DWORD m_dwGameStartTime;	//�Q�[���J�n����
	static DWORD m_dwGameTime;		//�Q�[���o�ߎ���

	static bool m_bEndGame;	//�I���t���O
};
#endif