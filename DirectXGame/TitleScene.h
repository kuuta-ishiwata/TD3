#pragma once
#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"

#include "Scene.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Scene.h"
class TitleScene {
public:
	// メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	TitleScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~TitleScene();

	void Initialize();

	void Update();

	void Draw();

	void Reset();

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kGameDescription; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isSceneEnd_ = false;

	Sprite* titlesprite_ = nullptr;

	int32_t timer_;

};
