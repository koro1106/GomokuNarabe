#pragma once
#include "../Library/GameObject.h"

const int HEIGHT = 15;
const int WIDTH = 15;

class Stage : public GameObject {
public:
	Stage();
	~Stage();
	void Draw() override;
	void Update() override;
	void SetMapValue(int x, int y, int value);//�}�b�v��Player��AI���u��
	int GetMapValue(int x, int y);//�R�}�擾
    int Put(int x, int y, int value);
	bool IsCellEmpty(int x, int y); //�Z�����󂢂Ă邩�`�F�b�N
	bool CheckWin(int turn);
	bool isGameOver ;
	bool isTie();//������������
	bool Tie;
	int CountLine(int x, int y, int dx, int dy, int turn);
	       //(x,y)�͕���ł��邩���׎n�߂�ʒu
	       //(dx,dy)�́A����ł������������(dx=x�ɑ����l�Ady=y�ɑ����l)
	       //turn�́A���ׂĂ�R�}���ǂ����Ȃ̂��iPlayer��AI��)���݂�
private:
	int backGround = LoadGraph("data/image/backGround.png");
	int playerGraph = LoadGraph("data/image/player.png");
	int aiGraph = LoadGraph("data/image/AI.png");
};