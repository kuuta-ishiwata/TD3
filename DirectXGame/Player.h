#pragma once
#include "ImGuiManager.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <Sprite.h>
#include <WinApp.h>
#include"MATHEX.h"
#include"ViewProjection.h"
#include"TextureManager.h"
class Player {
public:
	~Player();

	void Initialize(Model* model, uint32_t textureHandle);

	void Update(ViewProjection& viewProjection);

	void Draw(ViewProjection& viewProjection);

	void ScreenWorldTransformation(ViewProjection& viewProjection);

	void Attack();

	

	Vector3 GetWorldPosition3DReticle();

	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// キーボード入力
	Input* input_ = nullptr;

	// 速度
	Vector3 velocity_;

	// 3Dレティクル用ワールドトランスフォーム
	WorldTransform worldTransform3DReticle_;

	

	bool isSpeed = false;
};
