//================================================
//
//タッチナンバー[object.cpp]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "object2D.h"
#include "renderer.h"

//***************************
//静的メンバ変数
//***************************
CObject* CObject::m_apObject[MAX_OBJECT] = {};	//ポインタ
int CObject::m_nNumAll = 0;						//最大数

//================================================
//全ての解放
//================================================
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		m_apObject[i]->Release();	//解放
	}
}

//================================================
//全ての更新
//================================================
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		m_apObject[i]->Update();	//更新
	}
}

//================================================
//全ての描画
//================================================
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] == nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrではない場合 */

		m_apObject[i]->Draw();	//描画
	}
}

//================================================
//コンストラクタ
//================================================
CObject::CObject()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_apObject[i] != nullptr)
		{//NULLチェック
			continue;
		}

		/* nullptrの場合 */

		m_apObject[i] = this;	//自身のポインタを返す

		m_nID = i;		//自分の番号を設定
		objType = (CObject::OBJ_TYPE)this->m_nID;
		m_nNumAll++;	//数を増やす
		break;
	}
}

//================================================
//デストラクタ
//================================================
CObject::~CObject()
{
}

//================================================
//オブジェクト情報の取得
//================================================
CObject* CObject::GetObjects(int nIdx)
{
	return m_apObject[nIdx];
}

//================================================
//タイプの設定
//================================================
void CObject::SetObjType(const CObject::OBJ_TYPE &type)
{
	objType = type;
}

//================================================
//タイプの取得
//================================================
CObject::OBJ_TYPE CObject::GetObjType()
{
	return objType;
}

//================================================
//解放
//================================================
void CObject::Release()
{
	if (m_apObject[m_nID] == nullptr)
	{//NULLチェック
		return;
	}

	/* nullptrではない場合 */

	int nID = m_nID;	//番号を保存

	m_apObject[nID]->Uninit();	//終了
	delete m_apObject[nID];		//メモリの解放
	m_apObject[nID] = nullptr;	//nullptrにする

	m_nNumAll--;	//数を減らす
}