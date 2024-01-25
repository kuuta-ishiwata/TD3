#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Skydome.h"
#include "Ground.h"
#include "Load.h"
#include "Tree.h"

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
	// 敵発生コマンドの更新
	/// </summary>
	
	void LoadEnemyPopData();

	void UpdateEnemyPopCommands();

	/// <summary>
	/// 敵発生コマンドの更新
	/// </summary>
	//void EnemyPop(Vector3 pos);

	/// <summary>
	// 敵発生関数
	/// </summary>
	void EnemyPop(Vector3 pos);

	Vector3 GetEnemyPopPos() { return enemyPopPos; }
	void SetEnemyPopPos(Vector3 pos) { enemyPopPos = pos; }

	// 衝突判定
	void CheckAllCollisions();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	std::unique_ptr<Model> model_;
	WorldTransform worldTransform_;
	ViewProjection viewProjection_;

	uint32_t textureHandle_ = 0u;

	uint32_t treetextureHandle_ = 0u;

	uint32_t loadtextureHandle_ = 0u;
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

	// 敵キャラ
	std::list<std::unique_ptr<Enemy>> enemies_;
	
	//プレイヤー
	std::unique_ptr<Player> player_;

	//道
	std::unique_ptr<Load> road_;
	std::unique_ptr<Model> loadModel_;

	// 木
	std::unique_ptr<Tree> tree_[80];
	std::unique_ptr<Model> treeModel_;

	//コマンド
	GameInput* gameInput_ = nullptr;

	int enemyKillCount_ = 0;

	// エネミー
	//std::list<std::unique_ptr<Enemy>> enemies_;
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

	bool isTimeStop_ = false;

	int commandCount_ = 0;

	int isCommandCount_ = 0;
	bool isCoomand_ = false;
	uint32_t isCommandTex_ = 0u;
	// スプライト
	std::unique_ptr<Sprite> isCommandSprite_ = {};
};
