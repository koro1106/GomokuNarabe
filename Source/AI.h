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
private:
	bool AIWin;
	bool CheckOpenThree(int target);
};