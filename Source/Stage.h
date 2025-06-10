#pragma once
#include "../Library/GameObject.h"

const int HEIGHT = 15;
const int WIDTH = 15;

class Stage : public GameObject {
public:
	Stage();
	~Stage();
	void Draw() override;
	void SetMapValue(int x, int y, int value);
    int Put(int x, int y, int value);
	int GetMapValue(int x, int y);
	int backGround;
	bool IsCellEmpty(int x, int y); //�Z�����󂢂Ă邩�`�F�b�N
	bool CheckWin(int turn);
	bool isGameOver ;
	bool isTie();//������������
	bool Tie;
	int CountLine(int x, int y, int a, int b);
	void Horizontal();
};