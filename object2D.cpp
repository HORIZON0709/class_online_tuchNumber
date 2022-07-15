//================================================
//
//������H��b[object2D.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "object2D.h"
#include "application.h"
#include "renderer.h"

#include <assert.h>

//================================================
//����
//================================================
CObject2D* CObject2D::Create()
{
	CObject2D* pObject2D = nullptr;	//�|�C���^

	if (pObject2D != nullptr)
	{//NULL�`�F�b�N
		assert(false);
	}

	/* nullptr�̏ꍇ */

	pObject2D = new CObject2D;	//�������̓��I�m��

	pObject2D->Init();	//������

	return pObject2D;	//���I�m�ۂ������̂�Ԃ�
}

//================================================
//�R���X�g���N�^
//================================================
CObject2D::CObject2D() : 
	m_pTexture(nullptr),
	m_pVtxBuff(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rot(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_size(D3DXVECTOR2(0.0f,0.0f)),
	m_texture(CTexture::TEXTURE_NONE)
{
}

//================================================
//�f�X�g���N�^
//================================================
CObject2D::~CObject2D()
{
	/* ����R��̊m�F */
	assert(m_pTexture == nullptr);
	assert(m_pVtxBuff == nullptr);
}

//================================================
//������
//================================================
HRESULT CObject2D::Init()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//�����o�ϐ��̏����ݒ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_texture = CTexture::TEXTURE_NONE;

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
								D3DUSAGE_WRITEONLY,
								FVF_VERTEX_2D,
								D3DPOOL_MANAGED,
								&m_pVtxBuff,
								NULL);

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_����ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//================================================
//�I��
//================================================
void CObject2D::Uninit()
{
	//���_�o�b�t�@�̔j��
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//�e�N�X�`���̔j��
	if (m_pTexture != nullptr)
	{
		m_pTexture->Release();
		m_pTexture = nullptr;
	}
}

//================================================
//�X�V
//================================================
void CObject2D::Update()
{
	
}

//================================================
//�`��
//================================================
void CObject2D::Draw()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CApplication::GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	CTexture* pTexture = CApplication::GetTexture();	//�e�N�X�`�����擾

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, pTexture->GetTexture(m_texture));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,					//�`�悷��ŏ��̒��_�C���f�b�N�X
							2);					//�`�悷��v���~�e�B�u��
}

//================================================
//�ʒu��ݒ�
//================================================
void CObject2D::SetPos(const D3DXVECTOR3 &pos)
{
	m_pos = pos;	//�ʒu��ݒ�

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidthHalf = (m_size.x * 0.5f);	//�����̔���
	float fHeightHalf = (m_size.y * 0.5f);	//�c���̔���

	//���_����ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3(-fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(+fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-fWidthHalf, +fHeightHalf, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(+fWidthHalf, +fHeightHalf, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�ʒu���擾
//================================================
D3DXVECTOR3 CObject2D::GetPos()
{
	return m_pos;
}

//================================================
//�T�C�Y�̐ݒ�
//================================================
void CObject2D::SetSize(const D3DXVECTOR2 &size)
{
	m_size = size;	//�T�C�Y�̐ݒ�

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fWidthHalf = (m_size.x * 0.5f);	//�����̔���
	float fHeightHalf = (m_size.y * 0.5f);	//�c���̔���

	//���_����ݒ�
	pVtx[0].pos = m_pos + D3DXVECTOR3(-fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(+fWidthHalf, -fHeightHalf, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-fWidthHalf, +fHeightHalf, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(+fWidthHalf, +fHeightHalf, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�T�C�Y�̎擾
//================================================
D3DXVECTOR2 CObject2D::GetSize()
{
	return m_size;
}

//================================================
//�ړ��ʂ̐ݒ�
//================================================
void CObject2D::SetMove(const D3DXVECTOR3 &move)
{
	m_move = move;
}

//================================================
//�ړ��ʂ̎擾
//================================================
D3DXVECTOR3 CObject2D::GetMove()
{
	return m_move;
}

//================================================
//�e�N�X�`���̐ݒ�
//================================================
void CObject2D::SetTexture(CTexture::TEXTURE texture)
{
	m_texture = texture;
}

//================================================
//�e�N�X�`�����W�̐ݒ�
//================================================
void CObject2D::SetTexUV(float fLeft, float fRight, float fTop, float fBottom)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fLeft,  fTop);
	pVtx[1].tex = D3DXVECTOR2(fRight, fTop);
	pVtx[2].tex = D3DXVECTOR2(fLeft,  fBottom);
	pVtx[3].tex = D3DXVECTOR2(fRight, fBottom);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//================================================
//�e�N�X�`�����W�̐ݒ�(�A�j���[�V�����ɑΉ�)
//================================================
void CObject2D::SetTexUV(const int &nDivNum, const int &nPtnAnim)
{
	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

 	float fDivide = (1.0f / nDivNum);	//��Z�p��float�ɕϊ�

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(fDivide * nPtnAnim,		0.0f);
	pVtx[1].tex = D3DXVECTOR2(fDivide * (nPtnAnim + 1), 0.0f);
 	pVtx[2].tex = D3DXVECTOR2(fDivide * nPtnAnim,		1.0f);
	pVtx[3].tex = D3DXVECTOR2(fDivide * (nPtnAnim + 1), 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}