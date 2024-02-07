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
#include"Score.h"
#include"Result.h"
#include<memory>
class GameClearScene {
public:
	// メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameClearScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameClearScene();

	void Initialize();

	void Update();

	void Draw();

	void Reset();

	void GameReset();

	bool IsSceneEnd() { return isSceneEnd_; }
	Scene::SceneType NextScene() { return Scene::SceneType::kTitle; }

	bool IsClear() { return isClear_; }

private:
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	bool isSceneEnd_ = false;

	Sprite* titlesprite_ = nullptr;

	std::unique_ptr<Score> score_;
	std::unique_ptr<Result> result_;

	bool isClear_ = false;

	Vector2 pos_[2];
	
};
