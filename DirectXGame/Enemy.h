#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "BaseCharacter.h"
#include "assert.h"
#include "Input.h"
#include <vector>
#include <list>


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
	void OnCollision();
	bool isDead() const
	{ 

		return isdead_;

	}


private:

	// ワールド変換データ
	WorldTransform worldTransformBase_;
	WorldTransform worldTransformBody_;
	WorldTransform worldTransformHead_;
	WorldTransform worldTransformL_arm_;
	WorldTransform worldTransformR_arm_;

	// カメラのビュープロジェクション
	const ViewProjection* viewprojection_ = nullptr;

	// 3Dモデル
	Model* enemyFighterBody_ = nullptr;
	Model* enemyFighterL_arm_ = nullptr;
	Model* enemyFighterR_arm_ = nullptr;
	Model* enemyFighterHead_ = nullptr; 
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// カメラのビュープロジェクション
	const ViewProjection* viewProjection_ = nullptr;

	bool isdead_ = false;

};
