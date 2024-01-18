#include "Player.h"

#include <cassert>

Player::~Player() {}

void Player::OnCollision() 
{ 
	if (!isAttack_)
	{

		isHitBlock_ = true;
	}
	else {

		if (!GameInput::GetInstance()->Input())
		{
			isHitBlock_ = true;

	    }
	}

}

void Player::Initialize(Model* model, uint32_t textureHandle) {

	// NULLポインタチェック
	assert(model);

	model_ = model;

	textureHandle_ = textureHandle;

	worldTransform_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();

	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	velocity_ = {0.0f, 0.0f, startSpeed};
	isHitBlock_ = false;
	isAttack_ = false;
	hitDownTime_ = kHitDownTime_;
	attackDownTime_ = kAttackDownTime_;
}

void Player::Update(ViewProjection& viewProjection) {
	viewProjection;
	

	if (input_->IsTriggerMouse(WM_RBUTTONDOWN == 0)) {
		isAttack_ = true;
	}
	/*else if (input_->IsTriggerMouse(WM_LBUTTONDOWN != 0)) {
	    isHitBlock_ = true;
	}*/

	// 攻撃
	if (isAttack_) {
		Attack();
	}

	// 岩に当たったら
	if (isHitBlock_) {
		// 減速
		Deceleration();
	}

	/*if (input_->IsPressMouse(WM_LBUTTONDOWN != 0)) {
	    worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	}*/

	if (worldTransform_.translation_.z >= 400) {
		worldTransform_.translation_.z = 0;
	}

	// 座標を移動させる(1フレーム分の移動量を足し込む)
	 worldTransform_.translation_ = Add(worldTransform_.translation_, velocity_);

#ifdef _DEBUG

	ImGui::Begin("window");
	if (ImGui::TreeNode("Player")) {
		ImGui::SliderFloat3("translation", &worldTransform_.translation_.x, -10, 10);
		ImGui::SliderFloat3("rotation", &worldTransform_.rotation_.x, -10, 10);
		ImGui::SliderFloat3("speed", &velocity_.x, -10, 10);

		ImGui::TreePop();
	}
	ImGui::End();

	ImGui::Begin("A");
	ImGui::Text("%fl", sizeof(input_->GetAllKey()));
	ImGui::End();

#endif // _DEBUG
	worldTransform_.UpdateMatrix();
}

void Player::Draw(ViewProjection& viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Player::Attack() {
	// 加速度
	const float acceleration = 2.0f;
	Vector3 velocity = {0.0f, 0.0f, startSpeed};

	// 速度に加速度をかけあわせる
	velocity_ = Multiply(acceleration, velocity);

	// 攻撃終了
	if (++attackDownTime_ >= 5) {
		isAttack_ = false;
		velocity_.z = startSpeed;
		attackDownTime_ = kAttackDownTime_;
	}
}

void Player::Deceleration() {
	// 加速度
	const float acceleration = 0.25f;
	Vector3 velocity = {0.0f, 0.0f, startSpeed};

	// 速度に加速度をかけあわせる
	velocity_ = Multiply(acceleration, velocity);

	if (++hitDownTime_ >= 20) {
		isHitBlock_ = false;
		velocity_.z = startSpeed;
		hitDownTime_ = kHitDownTime_;
	}
}

Vector3 Player::GetWorldPosition() {
	// ワールド座標を入れる変数
	Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

// void Player::ScreenWorldTransformation(ViewProjection& viewProjection) {
//	POINT mousePosition;
//	// マウス座標(スクリーン座標)を取得する
//	GetCursorPos(&mousePosition);
//
//	// クライアントエリア座標に変換する
//	HWND hwnd = WinApp::GetInstance()->GetHwnd();
//	ScreenToClient(hwnd, &mousePosition);
//
//	// ビューポート行列
//	Matrix4x4 matViewport =
//	    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
//
//	Matrix4x4 matInverseViewport = Inverse(matViewport);
//	Matrix4x4 matInverseView = Inverse(viewProjection.matView);
//	Matrix4x4 matInverseProjection = Inverse(viewProjection.matProjection);
//
//	// ビュープロジェクションビューポート合成行列
//	Matrix4x4 matInverseVPV =
//	    Multiply(Multiply(matInverseViewport, matInverseProjection), matInverseView);
//
//	// Matrix4x4 matVPV = Multiply(Multiply(viewProjection.matView, viewProjection.matProjection),
//	// matViewport);
//	// 合成行列の逆行列を計算する
//	// Matrix4x4 matInverseVPV = Inverse(matVPV);
//
//	// スクリーン座標
//	Vector3 posNear = Vector3((float)mousePosition.x, 0, 0);
//	Vector3 posFar = Vector3((float)mousePosition.x, 1, 1);
//
//	// スクリーン座標系からワールド座標系へ
//	posNear = Transform(posNear, matInverseVPV);
//	posFar = Transform(posFar, matInverseVPV);
//
//	// マウスレイの方向
//	Vector3 mouseDirection = Subtract(posFar, posNear);
//	mouseDirection = Normalize(mouseDirection);
//	// カメラから照準オブジェクトの座標
//	const float kDistanceTestobject = 100;
//
//	mouseDirection = Multiply(kDistanceTestobject, mouseDirection);
//
//	worldTransform3DReticle_.translation_ = Add(posNear, mouseDirection);
//	worldTransform3DReticle_.translation_.y = 0.0f;
//	worldTransform3DReticle_.UpdateMatrix();
// }
