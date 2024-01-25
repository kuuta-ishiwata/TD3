#pragma once
#include "GameInput.h"

// 自機クラスの前方宣言
class Player;

// GameSceneクラスの前方宣言
class GameScene;

class Enemy : public BaseCharacter {

	public:
	Vector3 GetWorldPosition();

	const WorldTransform& GetWorldTransform() { return worldTransformBase_; }

	void SetViewProjection(const ViewProjection* viewprojection) {
		viewProjection_ = viewprojection;
	}

	// 初期化
	void Initialize(const std::vector<Model*>& models) override;

	// 更新
	void Update() override;

	// 描画
	void Draw(const ViewProjection& viewProjection) override;

	// 浮遊ギミック初期化
	void InitializeFloatingGimmick();
	// 浮遊ギミック更新
	void UpdateFloatingGimmick();

	void BehaviorRootInitialize();

	// 浮遊ギミックの媒介変数
	float floatingParameter_ = 0.0f;

	//敵死ぬ
	bool IsDead() const	{ return isDead_;}

	void GetViewProjection(const ViewProjection* viewProjection) {
		viewProjection_ = viewProjection;
	}
	void SetGameScene(GameScene* gameScene) { gameScene_ = gameScene; }

	// 衝突を検出したら呼び出されるコールバック関数
	void OnCollision();

	void SetPos(Vector3 pos) { worldTransformBase_.translation_ = pos; }

private:

	// ワールド変換データ
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;

	// カメラのビュープロジェクション
	//const ViewProjection* viewprojection_ = nullptr;


	// 3Dモデル
	Model* enemyFighterBody_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	bool isDead_ = false;

	// ゲームシーン
	GameScene* gameScene_ = nullptr;
};
