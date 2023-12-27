#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include  "DebugCamera.h"
#include <memory>
#include "Model.h"
#include "FollowCamera.h"
#include "Skydome.h"
#include "Ground.h"
#include "MATHEX.h"
#include "Enemy.h"
#include <sstream>
#include "Player.h"
#include <memory>

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

	/// <summary>	
	// 敵発生データの読み込み
	/// </summary>
	void LoadEnemyPopData();

	/// <summary>
	// 敵発生コマンドの更新
	/// </summary>
	void UpdateEnemyPopCommands();

	/// <summary>
	// 敵発生関数
	/// </summary>
	void EnemyPop(Vector3 pos);

	Vector3 GetEnemyPopPos() { return enemyPopPos; }
	void SetEnemyPopPos(Vector3 pos) { enemyPopPos = pos; }

	//void CheakCollision();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	std::unique_ptr<Model> model_;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t textureHandle_ = 0u;

	// デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;

	// フォローカメラ
	std::unique_ptr<FollowCamera> followCamera_;

		// 天球
	std::unique_ptr<Skydome> skydome_;
	std::unique_ptr<Model> skydomeModel_;

		// グラウンド
	std::unique_ptr<Ground> ground_;
	std::unique_ptr<Model> groundModel_;

	//プレイヤー
	std::unique_ptr<Player> player_;

	// エネミー
	std::list<std::unique_ptr<Enemy>> enemies_;
	// 敵リストを取得
	// 敵発生コマンド
	std::stringstream enemyPopCommands;
	Vector3 enemyPopPos = {};

	// 待機中フラグ
	bool isWait = false;
	// 待機タイマー
	uint32_t waitTimer = 0;

	// 3Dモデル
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterBody2_;
	std::unique_ptr<Model> modelFighterBody3_;
	std::unique_ptr<Model> modelFighterBody4_;

	float count = 0;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
