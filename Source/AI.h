#pragma once
#include "../Library/GameObject.h"

const int AI_HEIGHT = 15;
const int AI_WIDTH = 15;

class AI : public GameObject {
public:
	AI();
	~AI();
	void Update() override;
	void Draw() override;
	void AIstrategy();//攻撃・防御
	void ResetAIScores();//加算をリセット
	bool AITurn = false;	//AIのターンか
	bool AIWin;
private:
	bool IsLineN(int x, int y, int n, int dx, int dy, int turn);//n連続ならんでるかどうか
	void IsThreeLine();
	void IsTwoLine();
};