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
	void AIstrategy();//�U���E�h��
	void ResetAIScores();//���Z�����Z�b�g
	bool AITurn = false;	//AI�̃^�[����
	bool AIWin;
private:
	bool IsLineN(int x, int y, int n, int dx, int dy, int turn);//n�A���Ȃ��ł邩�ǂ���
	void IsThreeLine();
	void IsTwoLine();
};