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

	
	

}


void Enemy::Update()
{

	// enemy速さ
	const float kSpeed = 0.1f;

	Vector3 velocity{0.0f, 0.0f, kSpeed};

	Matrix4x4 rotateMatrix = MakeRotateMatrix(worldTransformBase_.rotation_);

	//worldTransformBase_.translation_.y += 0.02f;
	// 移動ベクトルを敵の角度だけ回転
	velocity = TransformNormal(velocity, worldTransformBase_.matWorld_);

	// 移動量
	worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, velocity);

	// 行列を定数バッファに転送
	worldTransformBody_.UpdateMatrix();
	worldTransformBase_.UpdateMatrix();
	worldTransformHead_.UpdateMatrix();
	worldTransformL_arm_.UpdateMatrix();
	worldTransformR_arm_.UpdateMatrix();

	BaseCharacter::Update();

}


void Enemy::Draw(const ViewProjection& viewProjection)
{
	models_[0]->Draw(worldTransformBody_, viewProjection);
	models_[1]->Draw(worldTransformHead_, viewProjection);
	models_[2]->Draw(worldTransformL_arm_, viewProjection);
	models_[3]->Draw(worldTransformR_arm_, viewProjection);


}


void Enemy::InitializeFloatingGimmick() { floatingParameter_ = 0.0f; }

void Enemy::UpdateFloatingGimmick() {
	// 浮遊移動のサイクル<frame>
	const uint16_t period = 120;

	// 1フレームでのパラメーター加算値
	const float step = 2.0f * (float)M_PI / period;

	// パラメーターを1ステップ分加算
	floatingParameter_ += step;

	// 2πを超えたら0に戻す
	floatingParameter_ = (float)std::fmod(floatingParameter_, 2.0f * M_PI);

	// 浮遊の振幅<m>
	const float floatingAmplitude = 0.5f;

	// 浮遊を座標に反映
	worldTransformBody_.translation_.y = std::sin(floatingParameter_) * floatingAmplitude;

	// 腕の動き
	worldTransformL_arm_.rotation_.x = std::sin(floatingParameter_) * 0.75f;
	worldTransformR_arm_.rotation_.x = std::sin(floatingParameter_) * 0.75f;
}

void Enemy::BehaviorRootInitialize() {
	worldTransformL_arm_.rotation_.x = 0.0f;
	worldTransformR_arm_.rotation_.x = 0.0f;
	
	// 浮遊初期化
	InitializeFloatingGimmick();

	worldTransformBody_.Initialize();
	worldTransformHead_.Initialize();
	worldTransformL_arm_.Initialize();
	worldTransformR_arm_.Initialize();
}