//================================================
//
//制作実践基礎[application.h]
//Author:Kishimoto Eiji
//
//================================================
//***************************
//インクルード
//***************************
#include "application.h"
#include "renderer.h"
#include "texture.h"

#include "object2D.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//***************************
//定数の定義
//***************************
const float CApplication::POLYGON_SIZE = 100.0f;	//ポリゴンのサイズ
const float CApplication::START_POS_X = 250.0f;		//最初のポリゴンの位置(X軸)
const float CApplication::START_POS_Y = 120.0f;		//最初のポリゴンの位置(Y軸)

//***************************
//静的メンバ変数
//***************************
CTexture* CApplication::m_pTexture = nullptr;	//テクスチャ
CRenderer* CApplication::m_pRenderer = nullptr;	//レンダラー

CObject2D* CApplication::m_apObject[MAX_POLYGON] = {};	//2Dオブジェクト

DWORD CApplication::m_dwGameStartTime = {};	//ゲーム開始時刻
DWORD CApplication::m_dwGameTime = {};		//ゲーム経過時間

bool CApplication::m_bEndGame = false;	//終了フラグ

//================================================
//テクスチャ情報を取得
//================================================
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//================================================
//レンダラー情報を取得
//================================================
CRenderer* CApplication::GetRenderer()
{
	return m_pRenderer;
}

//================================================
//時間の表示
//================================================
void CApplication::DrawTime(LPD3DXFONT pFont)
{
	RECT rect = 
	{//表示エリアの座標
		(int)(CRenderer::SCREEN_WIDTH * 0.43f),	//Left
		20,										//Top
		CRenderer::SCREEN_WIDTH,				//Right
		CRenderer::SCREEN_HEIGHT				//Bottom
	};

	TCHAR str[256];

	if (!m_bEndGame)
	{//ゲーム終了していない場合
		sprintf(str, ("経過時間 : %.3f\n"), (float)(m_dwGameTime * 0.001f));

		//テキスト描画
		pFont->DrawText(NULL, str, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
	}
}

//================================================
//コンストラクタ
//================================================
CApplication::CApplication()
{
}

//================================================
//デストラクタ
//================================================
CApplication::~CApplication()
{
}

//================================================
//初期化
//================================================
HRESULT CApplication::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	srand((unsigned)time(NULL));	//ランダム種子の初期化

	/* テクスチャ */

	if (m_pTexture == nullptr)
	{//NULLチェック
		m_pTexture = new CTexture;	//メモリの動的確保
	}

	/* レンダラー */

	if (m_pRenderer == nullptr)
	{//NULLチェック
		m_pRenderer = new CRenderer;	//メモリの動的確保
	}

	if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
	{//初期化処理が失敗した場合
		return E_FAIL;
	}

	/* 2Dオブジェクト */

	/* for文1個でやる場合 */
	//for (int nCntX = 0, nCntY = 0; nCntX < MAX_POLYGON; nCntX++)
	//{
	//	if (m_apObject[nCntX] != nullptr)
	//	{//NULLチェック
	//		continue;
	//	}

	//	/* nullptrの場合 */

	//	m_apObject[nCntX] = CObject2D::Create();	//生成

	//	m_apObject[nCntX]->Init();	//初期化

	//	//サイズの設定
	//	D3DXVECTOR2 size = D3DXVECTOR2(POLYGON_SIZE, POLYGON_SIZE);
	//	m_apObject[nCntX]->SetSize(size);

	//	if (nCntX % NUM_X == 0)
	//	{//5個横に配置していたら
	//		nCntY++;	//Y軸を1段分ずらす
	//	}

	//	//位置の設定
	//	D3DXVECTOR3 pos = D3DXVECTOR3(START_POS_X + ((START_POS_X * 0.5f) * ((nCntX % NUM_X) + 1)),
	//									(START_POS_Y * nCntY),
	//									0.0f);
	//	m_apObject[nCntX]->SetPos(pos);

	//	// テクスチャの設定
	//	m_apObject[nCntX]->SetTexture(CTexture::TEXTURE_number003);
	//	m_apObject[nCntX]->SetTexUV(MAX_POLYGON, nCntX);
	//}

	/* for文2個(二重ループ)でやる場合 */
	for (int nCntY = 0; nCntY < NUM_ROW; nCntY++)
	{
		for (int nCntX = 0; nCntX < NUM_COLUMN; nCntX++)
		{
			//インデックス数
			int nIdx = (nCntX + (nCntY * NUM_COLUMN));

			if (m_apObject[nIdx] != nullptr)
			{//NULLチェック
				continue;
			}

			/* nullptrの場合 */

			m_apObject[nIdx] = CObject2D::Create();	//生成

			m_apObject[nIdx]->Init();	//初期化

			//サイズの設定
			D3DXVECTOR2 size = D3DXVECTOR2(POLYGON_SIZE, POLYGON_SIZE);
			m_apObject[nIdx]->SetSize(size);

			//X軸とY軸の位置を設定
			float fPosX = (START_POS_X + ((START_POS_X * 0.5f) * ((nCntX % NUM_COLUMN) + 1)));
			float fPosY = (START_POS_Y * (nCntY + 1));

			//位置の設定
			D3DXVECTOR3 pos = D3DXVECTOR3(fPosX, fPosY, 0.0f);
			m_apObject[nIdx]->SetPos(pos);

			//テクスチャの設定
			m_apObject[nIdx]->SetTexture(CTexture::TEXTURE_number003);
			m_apObject[nIdx]->SetTexUV(MAX_POLYGON, nIdx);
		}
	}

	Shuffle();	//シャッフル

	m_dwGameStartTime = timeGetTime();	//ゲーム開始時刻を設定

	return S_OK;
}

//================================================
//終了
//================================================
void CApplication::Uninit()
{
	/* オブジェクト */

	CObject2D::ReleaseAll();	//全ての解放(2D)
	
	/* レンダラー */

	if (m_pRenderer != nullptr)
	{//NULLチェック
		m_pRenderer->Uninit();	//終了処理
		delete m_pRenderer;		//メモリの解放
		m_pRenderer = nullptr;	//nullptrにする
	}

	/* テクスチャ */

	if (m_pTexture != nullptr)
	{//NULLチェック
		m_pTexture->ReleaseAll();	//終了処理
		delete m_pTexture;			//メモリの解放
		m_pTexture = nullptr;		//nullptrにする
	}
}

//================================================
//更新
//================================================
void CApplication::Update()
{
	if (m_pRenderer != nullptr)
	{//NULLチェック
		m_pRenderer->Update();	//レンダラー
	}

	if (!m_bEndGame)
	{//ゲーム終了していない場合
		//ゲーム経過時間を計算(更新)
		m_dwGameTime = (timeGetTime() - m_dwGameStartTime);
	}
}

//================================================
//描画
//================================================
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{//NULLチェック
		m_pRenderer->Draw();	//レンダラー
	}
}

//================================================
//シャッフル
//================================================
void CApplication::Shuffle()
{
	for (int i = (MAX_POLYGON - 1); i > 0; i--)
	{
		int nIdxShuffle = rand() % i;	//「入れ替えられる側」をランダムで選択

		//「入れ替えられる側」の位置
		D3DXVECTOR3 posSwap = m_apObject[nIdxShuffle]->GetPos();

		//「入れ替える側」の位置
		D3DXVECTOR3 posWasSwap = m_apObject[i]->GetPos();

		/* 位置の入れ替え */

		//「入れ替える側」--->「入れ替えられる側」に入れる
		m_apObject[nIdxShuffle]->SetPos(posWasSwap);

		//「入れ替えられる側」--->「入れ替える側」に入れる
		m_apObject[i]->SetPos(posSwap);

	}
}