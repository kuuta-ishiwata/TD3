#include "Enemy.h"
#include "MATHEX.h"
#include <cassert>
#include "ImGuiManager.h"
#define _USE_MATH_DEFINES
#include <math.h>

#include "Player.h"
#include "GameScene.h"

void Enemy::OnCollision() { isDead_ = true; }

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
	// ワールドトランスフォームの初期化

	worldTransformBase_.Initialize();
	worldTransformBody_.Initialize();

	worldTransformBody_.parent_ = &worldTransformBase_;

	// X,Y,Z方向のスケーリングを設定
	worldTransformBase_.scale_ = {1.0f, 1.0f, 1.0f};
	worldTransformBase_.translation_ = {0.0f, 2.0f, 10.0f};

	// 腕の座標指定
	worldTransformBody_.translation_.x = 4.0f;
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
}

void Enemy::BehaviorRootInitialize() {
	
	// 浮遊初期化
	InitializeFloatingGimmick();

	worldTransformBody_.Initialize();
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
	//worldTransformBase_.translation_ = Add(worldTransformBase_.translation_, velocity);

	UpdateFloatingGimmick();

#ifdef _DEBUG

	ImGui::Begin("window");
	if (ImGui::TreeNode("Enemy")) {
	    ImGui::SliderFloat3("translation", &worldTransformBody_.translation_.x, -10.0f, 10.0f);
		ImGui::TreePop();
	}
	ImGui::End();

#endif // _DEBUG

	// 行列を定数バッファに転送
	BaseCharacter::Update();
	worldTransformBody_.UpdateMatrix();
	worldTransformBase_.UpdateMatrix();
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	if (!isDead_){
		models_[0]->Draw(worldTransformBody_, viewProjection);
	}
}