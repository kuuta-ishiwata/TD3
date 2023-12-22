#pragma once
#include"WorldTransform.h"
#include"Model.h"
#include"ImGuiManager.h"
#include"MATHEX.h"
#include "Input.h"
#include"WinApp.h"
#include"ViewProjection.h"

class Player {
public:

	void Initialize();

	void Update();

	void Draw(ViewProjection& viewProjection);

// スクリーン変換からワールド変換
	void ScreenWorldTransformation(ViewProjection& viewProjection);

	private:
	WorldTransform worldTransform_;

	Model* model_ = nullptr;

	// ゲームパッドの状態を得る変数
	XINPUT_STATE joyState;

};
