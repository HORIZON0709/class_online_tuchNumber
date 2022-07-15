//================================================
//
//������H��b[application.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "application.h"
#include "renderer.h"
#include "texture.h"

#include "object2D.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//***************************
//�萔�̒�`
//***************************
const float CApplication::POLYGON_SIZE = 100.0f;	//�|���S���̃T�C�Y
const float CApplication::START_POS_X = 250.0f;		//�ŏ��̃|���S���̈ʒu(X��)
const float CApplication::START_POS_Y = 120.0f;		//�ŏ��̃|���S���̈ʒu(Y��)

//***************************
//�ÓI�����o�ϐ�
//***************************
CTexture* CApplication::m_pTexture = nullptr;	//�e�N�X�`��
CRenderer* CApplication::m_pRenderer = nullptr;	//�����_���[

CObject2D* CApplication::m_apObject[MAX_POLYGON] = {};	//2D�I�u�W�F�N�g

DWORD CApplication::m_dwGameStartTime = {};	//�Q�[���J�n����
DWORD CApplication::m_dwGameTime = {};		//�Q�[���o�ߎ���

bool CApplication::m_bEndGame = false;	//�I���t���O

int CApplication::m_nTouchCount = 0;	//���Ƀ^�b�`���鐔��(1�`25)

//================================================
//�e�N�X�`�������擾
//================================================
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//================================================
//�����_���[�����擾
//================================================
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//================================================
//���Ԃ̕\��
//================================================
void CApplication::DrawTime(LPD3DXFONT pFont)
{
	RECT rect = 
	{//�\���G���A�̍��W
		(int)(CRenderer::SCREEN_WIDTH * 0.43f),	//Left
		20,										//Top
		CRenderer::SCREEN_WIDTH,				//Right
		CRenderer::SCREEN_HEIGHT				//Bottom
	};

	TCHAR str[256];

	if (!m_bEndGame)
	{//�Q�[���I�����Ă��Ȃ��ꍇ
		sprintf(str, ("�o�ߎ��� : %.3f\n"), (float)(m_dwGameTime * 0.001f));

		//�e�L�X�g�`��
		pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
		return;
	}

	/* �Q�[�����I�����Ă���ꍇ */

	//�Q�[�����ʂ̕\��
	sprintf(str, ("���Ȃ��̃^�C�� : %.3f\n"), (float)(m_dwGameTime * 0.001f));

	//�e�L�X�g�`��
	pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}

//================================================
//�^�b�`�������W���󂯎��
//================================================
void CApplication::Touch(const D3DXVECTOR2 &pos)
{
	if (m_bEndGame)
	{//�Q�[���I�����Ă���ꍇ
		return;
	}

	/* �Q�[���I�����Ă��Ȃ��ꍇ */

	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (i != m_nTouchCount)
		{//�J�E���g�����݂̔ԍ��ł͂Ȃ��ꍇ
			continue;
		}

		/* �J�E���g�����݂̔ԍ��̏ꍇ */

		D3DXVECTOR3 posObj =  m_apObject[i]->GetPos();	//�I�u�W�F�N�g�̈ʒu���擾
		float fSizeHalf = (POLYGON_SIZE * 0.5f);		//�T�C�Y�̔���

		//����p�͈̔͂�ݒ�
		float fLeft		= (posObj.x - fSizeHalf);	//���[
		float fRight	= (posObj.x + fSizeHalf);	//�E�[
		float fTop		= (posObj.y - fSizeHalf);	//��[
		float fBottom	= (posObj.y + fSizeHalf);	//���[

		//�u�^�b�`�������W���A�|���S���͈̔͂��傫�������������v�Ƃ�������
		bool bLargeOrSmall_Left		= (pos.x > fLeft);		//���[
		bool bLargeOrSmall_Right	= (pos.x < fRight);		//�E�[
		bool bLargeOrSmall_Top		= (pos.y > fTop);		//��[
		bool bLargeOrSmall_Bottom	= (pos.y < fBottom);	//���[

		if (bLargeOrSmall_Left && bLargeOrSmall_Right &&	//���E
			bLargeOrSmall_Top && bLargeOrSmall_Bottom)		//�㉺
		{//�S�Ă̔��肪true�̎�
			m_apObject[i]->Release();	//���
			m_nTouchCount++;			//���Ƀ^�b�`���鐔�����X�V
			break;
		}
	}
}

//================================================
//�R���X�g���N�^
//================================================
CApplication::CApplication()
{
}

//================================================
//�f�X�g���N�^
//================================================
CApplication::~CApplication()
{
}

//================================================
//������
//================================================
HRESULT CApplication::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	srand((unsigned)time(NULL));	//�����_����q�̏�����

	/* �e�N�X�`�� */

	if (m_pTexture == nullptr)
	{//NULL�`�F�b�N
		m_pTexture = new CTexture;	//�������̓��I�m��
	}

	/* �����_���[ */

	if (m_pRenderer == nullptr)
	{//NULL�`�F�b�N
		m_pRenderer = new CRenderer;	//�������̓��I�m��
	}

	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//���������������s�����ꍇ
		return E_FAIL;
	}

	/* 2D�I�u�W�F�N�g */

	/* for��1�ł��ꍇ */
	//for (int nCntX = 0, nCntY = 0; nCntX < MAX_POLYGON; nCntX++)
	//{
	//	if (m_apObject[nCntX] != nullptr)
	//	{//NULL�`�F�b�N
	//		continue;
	//	}

	//	/* nullptr�̏ꍇ */

	//	m_apObject[nCntX] = CObject2D::Create();	//����

	//	m_apObject[nCntX]->Init();	//������

	//	//�T�C�Y�̐ݒ�
	//	D3DXVECTOR2 size = D3DXVECTOR2(POLYGON_SIZE, POLYGON_SIZE);
	//	m_apObject[nCntX]->SetSize(size);

	//	if (nCntX % NUM_X == 0)
	//	{//5���ɔz�u���Ă�����
	//		nCntY++;	//Y����1�i�����炷
	//	}

	//	//�ʒu�̐ݒ�
	//	D3DXVECTOR3 pos = D3DXVECTOR3(START_POS_X + ((START_POS_X * 0.5f) * ((nCntX % NUM_X) + 1)),
	//									(START_POS_Y * nCntY),
	//									0.0f);
	//	m_apObject[nCntX]->SetPos(pos);

	//	// �e�N�X�`���̐ݒ�
	//	m_apObject[nCntX]->SetTexture(CTexture::TEXTURE_number003);
	//	m_apObject[nCntX]->SetTexUV(MAX_POLYGON, nCntX);
	//}

	/* for��2��(��d���[�v)�ł��ꍇ */
	for (int nCntY = 0; nCntY < NUM_ROW; nCntY++)
	{
		for (int nCntX = 0; nCntX < NUM_COLUMN; nCntX++)
		{
			//�C���f�b�N�X��
			int nIdx = (nCntX + (nCntY * NUM_COLUMN));

			if (m_apObject[nIdx] != nullptr)
			{//NULL�`�F�b�N
				continue;
			}

			/* nullptr�̏ꍇ */

			m_apObject[nIdx] = CObject2D::Create();	//����

			m_apObject[nIdx]->Init();	//������

			//�T�C�Y�̐ݒ�
			D3DXVECTOR2 size = D3DXVECTOR2(POLYGON_SIZE, POLYGON_SIZE);
			m_apObject[nIdx]->SetSize(size);

			//X����Y���̈ʒu��ݒ�
			float fPosX = (START_POS_X + ((START_POS_X * 0.5f) * ((nCntX % NUM_COLUMN) + 1)));
			float fPosY = (START_POS_Y * (nCntY + 1));

			//�ʒu�̐ݒ�
			D3DXVECTOR3 pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);
			m_apObject[nIdx]->SetPos(pos);

			//�e�N�X�`���̐ݒ�
			m_apObject[nIdx]->SetTexture(CTexture::TEXTURE_number003);
			m_apObject[nIdx]->SetTexUV(MAX_POLYGON, nIdx);
		}
	}

	Shuffle();	//�V���b�t��

	m_dwGameStartTime = timeGetTime();	//�Q�[���J�n������ݒ�

	return S_OK;
}

//================================================
//�I��
//================================================
void CApplication::Uninit()
{
	/* �I�u�W�F�N�g */

	CObject2D::ReleaseAll();	//�S�Ẳ��(2D)
	
	/* �����_���[ */

	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Uninit();	//�I������
		delete m_pRenderer;		//�������̉��
		m_pRenderer = nullptr;	//nullptr�ɂ���
	}

	/* �e�N�X�`�� */

	if (m_pTexture != nullptr)
	{//NULL�`�F�b�N
		m_pTexture->ReleaseAll();	//�I������
		delete m_pTexture;			//�������̉��
		m_pTexture = nullptr;		//nullptr�ɂ���
	}
}

//================================================
//�X�V
//================================================
void CApplication::Update()
{
	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Update();	//�����_���[
	}

	if (!m_bEndGame)
	{//�Q�[���I�����Ă��Ȃ��ꍇ
		//�Q�[���o�ߎ��Ԃ��v�Z(�X�V)
		m_dwGameTime = (timeGetTime() - m_dwGameStartTime);
	}

	if (m_nTouchCount == MAX_POLYGON)
	{//�S�Ẵ|���S�����^�b�`������
		m_bEndGame = true;	//�Q�[�����I���t���O�𗧂Ă�
	}
}

//================================================
//�`��
//================================================
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{//NULL�`�F�b�N
		m_pRenderer->Draw();	//�����_���[
	}
}

//================================================
//�V���b�t��
//================================================
void CApplication::Shuffle()
{
	for (int i = (MAX_POLYGON - 1); i > 0; i--)
	{
		int nIdxShuffle = rand() % i;	//�u����ւ����鑤�v�������_���őI��

		//�u����ւ����鑤�v�̈ʒu
		D3DXVECTOR3 posSwap = m_apObject[nIdxShuffle]->GetPos();

		//�u����ւ��鑤�v�̈ʒu
		D3DXVECTOR3 posWasSwap = m_apObject[i]->GetPos();

		/* �ʒu�̓���ւ� */

		//�u����ւ��鑤�v--->�u����ւ����鑤�v�ɓ����
		m_apObject[nIdxShuffle]->SetPos(posWasSwap);

		//�u����ւ����鑤�v--->�u����ւ��鑤�v�ɓ����
		m_apObject[i]->SetPos(posSwap);

	}
}