//================================================
//
//������H��b[object.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//�C���N���[�h
//***************************
#include "object2D.h"
#include "renderer.h"

//***************************
//�ÓI�����o�ϐ�
//***************************
CObject* CObject::m_apObject[MAX_OBJECT] = {};	//�|�C���^
int CObject::m_nNumAll = 0;						//�ő吔

//================================================
//�S�Ẳ��
//================================================
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apObject[i]->Release();	//���
	}
}

//================================================
//�S�Ă̍X�V
//================================================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apObject[i]->Update();	//�X�V
	}
}

//================================================
//�S�Ă̕`��
//================================================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�ł͂Ȃ��ꍇ */

		m_apObject[i]->Draw();	//�`��
	}
}

//================================================
//�R���X�g���N�^
//================================================
CObject::CObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] != nullptr)
		{//NULL�`�F�b�N
			continue;
		}

		/* nullptr�̏ꍇ */

		m_apObject[i] = this;	//���g�̃|�C���^��Ԃ�

		m_nID = i;		//�����̔ԍ���ݒ�
		objType = (CObject::OBJ_TYPE)this->m_nID;
		m_nNumAll++;	//���𑝂₷
		break;
	}
}

//================================================
//�f�X�g���N�^
//================================================
CObject::~CObject()
{
}

//================================================
//�I�u�W�F�N�g���̎擾
//================================================
CObject* CObject::GetObjects(int nIdx)
{
	return m_apObject[nIdx];
}

//================================================
//�^�C�v�̐ݒ�
//================================================
void CObject::SetObjType(const CObject::OBJ_TYPE &type)
{
	objType = type;
}

//================================================
//�^�C�v�̎擾
//================================================
CObject::OBJ_TYPE CObject::GetObjType()
{
	return objType;
}

//================================================
//���
//================================================
void CObject::Release()
{
	if (m_apObject[m_nID] == nullptr)
	{//NULL�`�F�b�N
		return;
	}

	/* nullptr�ł͂Ȃ��ꍇ */

	int nID = m_nID;	//�ԍ���ۑ�

	m_apObject[nID]->Uninit();	//�I��
	delete m_apObject[nID];		//�������̉��
	m_apObject[nID] = nullptr;	//nullptr�ɂ���

	m_nNumAll--;	//�������炷
}