#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// �^�C�g���V�[��
/// 
/// �^�C�g����\�����āA�L�[����������v���C�V�[���Ɉڍs����B
/// </summary>
class TitleScene : public SceneBase
{
public:
	TitleScene();
	~TitleScene();
	void Update() override;
	void Draw() override;
private:
	int TitleImage;
	int buttonX = 144;//�{�^����X���W
	int buttonY = 644;//�{�^����Y���W
	int buttonWidth = 440;//�{�^���̕�
	int buttonHeight = 140;//�{�^���̍���
	int mouseX, mouseY;
	bool prevButton; //�O�̃{�^���̏��
};
