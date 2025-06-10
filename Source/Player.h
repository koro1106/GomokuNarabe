#pragma once
#include "../Library/GameObject.h"

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;
	bool isPlayerTurn;
	int gridOriginX = 450;//�Ֆʍ���X���W
	int gridOriginY = 100;//�Ֆʍ���Y���W
	int cellSize = 50;//�}�X�T�C�Y
private:
	int MouseX, MouseY;
	bool prevButton; //�O�̃{�^���̏��
	bool PlayerWin;
	
};
