#include "Enemy.h"
#include "MATHEX.h"
#include <cassert>
#include "ImGuiManager.h"
#define _USE_MATH_DEFINES
#include <math.h>

Vector3 Enemy::GetWorldPosition() {
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得
	worldPos.x = worldTransformBase_.matWorld_.m[3][0];
	worldPos.y = worldTransformBase_.matWorld_.m[3][1];
	worldPos.z = worldTransformBase_.matWorld_.m[3][2];

	return worldPos;
}

void Enemy::Initialize(const std::vector<Model*>& models) {

	//input_ = Input::GetInstance();

	// 基底クラスの初期化
	BaseCharacter::Initialize(models);

	worldTransformBase_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformBody_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();

	worldTransformBody_.parent_ = &worldTransformBase_;
	worldTransformHead_.parent_ = &worldTransformBody_;
	worldTransformL_arm_.parent_ = &worldTransformBody_;
	worldTransformR_arm_.parent_ = &worldTransformBody_;

	// ワールドトランスフォームの初期化
	worldTransformBase_.Initialize();

	// X,Y,Z方向のスケーリングを設定
	worldTransformBase_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformBase_.translation_ = {0.0f, 2.0f, -5.0f};

	

	// 腕の座標指定
	worldTransformHead_.translation_.y = 1.5f;
	worldTransformL_arm_.translation_.x = -0.5f;
	worldTransformR_arm_.translation_.x = 0.5f;
	worldTransformL_arm_.translation_.y = 1.3f;
	worldTransformR_arm_.translation_.y = 1.3f;

	//
			

}


void Enemy::Update()
{
	BaseCharacter::Update();

	// 行列を定数バッファに転送
	worldTransformBody_.UpdateMatrix();
	worldTransformBase_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();


}


void Enemy::Draw(const ViewProjection& viewProjection)
{
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);


}