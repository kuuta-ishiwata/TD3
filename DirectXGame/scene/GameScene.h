#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include  "DebugCamera.h"
#include "Model.h"
#include "FollowCamera.h"
#include "Skydome.h"
#include "Ground.h"
#include "MATHEX.h"


/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

		
	Model* model_;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	// デバッグカメラ
	bool isDebugCameraActive_ = false;

	// フォローカメラ
	std::unique_ptr<FollowCamera> followCamera_;
		// 天球
	std::unique_ptr<Skydome> skydome_;

	std::unique_ptr<Model> skydomeModel_;

		// グラウンド
	std::unique_ptr<Ground> ground_;

	std::unique_ptr<Model> groundModel_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
