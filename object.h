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

public: /* �����o�֐� */
	CObject* GetObjects(int nIdx);	//�I�u�W�F�N�g���̎擾
	void Release();	//���

	/*
		�^�C�v�̐ݒ�
		const OBJ_TYPE &type ---> �C�ӂ̃^�C�v
	*/
	void SetObjType(const OBJ_TYPE &type);

	/*
		�^�C�v�̎擾
	*/
	OBJ_TYPE GetObjType();

private: /* �ÓI�����o�ϐ� */
	static CObject* m_apObject[MAX_OBJECT];	//�|�C���^
	static int m_nNumAll;					//�ő吔
	
private: /* �����o�ϐ� */
	int m_nID;					//�i�[��̔ԍ�
	CObject::OBJ_TYPE objType;	//���
};

#endif