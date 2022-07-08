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