//================================================
//
//タッチナンバー[application.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _APPLICATION_H_
#define _APPLICATION_H_

//***************************
//インクルード
//***************************
#include <d3dx9.h>

//***************************
//前方宣言
//***************************
class CRenderer;
class CTexture;

class CObject2D;

//***************************
//アプリケーションクラスの定義
//***************************
class CApplication
{/* 基本クラス */
private: /* 定数の定義 */
	static const int MAX_POLYGON = 25;	//ポリゴンの最大数
	static const int NUM_COLUMN = 5;	//列(X軸)の数
	static const int NUM_ROW = 5;		//行(Y軸)の数

	static const float POLYGON_SIZE;	//ポリゴンのサイズ
	static const float START_POS_X;		//最初のポリゴンの位置(X軸)
	static const float START_POS_Y;		//最初のポリゴンの位置(Y軸)

public: /* 静的メンバ関数 */
	static CTexture* GetTexture();		//テクスチャ情報を取得
	static CRenderer* GetRenderer();	//レンダラー情報を取得

	static void DrawTime(LPD3DXFONT pFont);		//時間を表示
	static void Touch(const D3DXVECTOR2 &pos);	//タッチした座標を受け取る

public: /* コンストラクタ・デストラクタ */
	CApplication();
	~CApplication();

public: /* メンバ関数 */
	HRESULT Init(HWND hWnd, BOOL bWindow,HINSTANCE hInstance);	//初期化

	void Uninit();	//終了
	void Update();	//更新
	void Draw();	//描画
private:
	void Shuffle();	//シャッフル

private: /* 静的メンバ変数 */
	static CTexture* m_pTexture;	//テクスチャのポインタ
	static CRenderer* m_pRenderer;	//レンダラーのポインタ

	static CObject2D* m_apObject[MAX_POLYGON];	//2Dオブジェクトのポインタ

	static DWORD m_dwGameStartTime;	//ゲーム開始時刻
	static DWORD m_dwGameTime;		//ゲーム経過時間

	static bool m_bEndGame;	//終了フラグ

	static int m_nTouchCount;	//次にタッチする数字(1～25)
};
#endif