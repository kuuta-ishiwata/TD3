#include "Enemy.h"

#include "GameScene.h"
#include "Player.h"

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
	// 基底クラスの初期化
	BaseCharacter::Initialize(models);

	worldTransformBase_.Initialize();
	worldTransformBase_.scale_ = {1.0f, 1.0f, 1.0f};
	
	worldTransformBody_.Initialize();
	worldTransformBody_.parent_ = &worldTransformBase_;

	/*worldTransformBody2_.Initialize();
	worldTransformBody2_.parent_ = &worldTransformBody_;

	worldTransformBody3_.Initialize();
	worldTransformBody3_.parent_ = &worldTransformBody_;

	worldTransformBody4_.Initialize();
	worldTransformBody4_.parent_ = &worldTransformBody_;*/

	

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

void Enemy::BehaviorRootInitialize() {}

void Enemy::Update() {
	BaseCharacter::Update();

	/*
#ifdef _DEBUG

	ImGui::Begin("window");
	if (ImGui::TreeNode("Enemy")) {
	    ImGui::SliderFloat3("translation", &worldTransformBody_.translation_.x, -10.0f, 10.0f);
	    ImGui::TreePop();
	}
	ImGui::End();

#endif // _DEBUGmodelFighterBody_
*/

	// 行列を定数バッファに転送
	worldTransformBase_.UpdateMatrix();
	worldTransformBody_.UpdateMatrix();
	/*worldTransformBody2_.UpdateMatrix();
	worldTransformBody3_.UpdateMatrix();
	worldTransformBody4_.UpdateMatrix();*/
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	if (!isDead_) {
		models_[0]->Draw(worldTransformBase_, viewProjection);

		/*models_[1]->Draw(worldTransformBody2_, viewProjection);
		models_[2]->Draw(worldTransformBody3_, viewProjection);
		models_[3]->Draw(worldTransformBody4_, viewProjection);*/
	}
}