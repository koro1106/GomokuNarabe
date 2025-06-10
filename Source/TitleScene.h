#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// タイトルシーン
/// 
/// タイトルを表示して、キーを押したらプレイシーンに移行する。
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
	int buttonX = 144;//ボタンのX座標
	int buttonY = 644;//ボタンのY座標
	int buttonWidth = 440;//ボタンの幅
	int buttonHeight = 140;//ボタンの高さ
	int mouseX, mouseY;
	bool prevButton; //前のボタンの状態
};
