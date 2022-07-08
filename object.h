//================================================
//
//������H��b[object.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

//***************************
//�C���N���[�h
//***************************
#include <d3dx9.h>

//***************************
//�I�u�W�F�N�g�N���X�̒�`
//***************************
class CObject
{/* ��{�N���X */
public: /* �񋓌^�̒�` */
	enum OBJ_TYPE
	{/* �I�u�W�F�N�g�̎�� */
		PLAYER = 0,	//�v���C���[
		ENEMY,		//�G
		BULLET,		//�e
		EXPLOSION,	//����
		BG,			//�w�i
		MAX,
		NONE
	};

public: /* �萔�̒�` */
	static const int MAX_OBJECT = 64;	//�|���S���̍ő吔

public: /* �ÓI�����o�֐� */
	static void ReleaseAll();	//�S�Ẳ��
	static void UpdateAll();	//�S�Ă̍X�V
	static void DrawAll();		//�S�Ă̕`��

public: /* �R���X�g���N�^�E�f�X�g���N�^ */
	CObject();
	virtual ~CObject();

public: /* �������z�֐� */
	virtual HRESULT Init() = 0;	//������
	virtual void Uninit() = 0;	//�I��
	virtual void Update() = 0;	//�X�V
	virtual void Draw() = 0;	//�`��
public: /* Set,Get�n */
	/* Pos */
	virtual void SetPos(const D3DXVECTOR3 &pos) = 0;	//�ʒu��ݒ�
	virtual D3DXVECTOR3 GetPos() = 0;					//�ʒu���擾

	/* Size */
	virtual void SetSize(const D3DXVECTOR2 &size) = 0;	//�T�C�Y��ݒ�
	virtual D3DXVECTOR2 GetSize() = 0;					//�T�C�Y���擾

	/* Move */
	virtual void SetMove(const D3DXVECTOR3 &move) = 0;	//�ړ��ʂ�ݒ�
	virtual D3DXVECTOR3 GetMove() = 0;					//�ړ��ʂ��擾

public: /* �����o�֐� */
	CObject* GetObjects(int nIdx);	//�I�u�W�F�N�g���̎擾

	/* ObjType */
	void SetObjType(const OBJ_TYPE &type);	//�^�C�v�̐ݒ�
	OBJ_TYPE GetObjType();					//�^�C�v�̎擾

	void Release();	//���

private: /* �ÓI�����o�ϐ� */
	static CObject* m_apObject[MAX_OBJECT];	//�|�C���^
	static int m_nNumAll;					//�ő吔
	
private: /* �����o�ϐ� */
	int m_nID;					//�i�[��̔ԍ�
	CObject::OBJ_TYPE objType;	//���
};

#endif