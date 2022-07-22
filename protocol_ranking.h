//================================================
//
//タッチナンバー[protocol_ranking.h]
//Author:Kishimoto Eiji
//
//================================================
#ifndef _PROTOCOL_RANKING_H_
#define _PROTOCOL_RANKING_H_

//***************************
//列挙型の定義
//***************************

/* 通信の決まり事 */
enum class COMMAND_TYPE
{
	NONE = 0,		//何も無し
	SET_RANKING,	//ランキングの設定
	GET_RANKING,	//ランキングの取得
	MAX,
};

#endif