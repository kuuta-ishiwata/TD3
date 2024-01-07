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
#include"Player.h"
#include<memory>


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
	/// 敵発生データの書き込み
	/// </summary>
	void EnemyPop(Vector3 pos);

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	void SetEnemyPopPos(Vector3 pos);
	void LoadEnemyPopData();

	void CheckAllCollisions();

	void UpdateEnemyPopCommands();

	

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	//void EnemySpawn(Vector3& Position);
	//void EnemyObjUpdate();
	//void EnemyObjDraw();


		
	std::unique_ptr<Model> model_;
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

	// 敵キャラ
	std::list<std::unique_ptr<Enemy>> enemies_;
	

	// 3Dモデル
	std::unique_ptr<Model> modelFighterBody_;
	std::unique_ptr<Model> modelFighterBody2_;
	std::unique_ptr<Model> modelFighterBody3_;
	std::unique_ptr<Model> modelFighterBody4_;

	float count = 0;
	
	bool isWait = true;
	
	// 待機タイマ
	int32_t waitTimer = 0;
	std::unique_ptr<Player> player_;

	uint32_t textureHandle_ = 0u;

	// 敵発生コマンド
	std::stringstream enemyPopCommands;
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
