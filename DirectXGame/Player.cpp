#include "Player.h"

void Player::Initialize() { 
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 0.0f, 0.0f};
	worldTransform_.scale_ = {1.0f, 1.0f, 1.0f};
	
	model_ = Model::Create();

}

void Player::Update() { 
	worldTransform_.TransferMatrix();
	
		// ゲームパッド状態取得、ゲームパッドが有効の場合if文がを通る
	if (Input::GetInstance()->GetJoystickState(0, joyState)) {
		// 速さ
		const float speed = 0.3f;

		// 移動量
		Vector3 move2 = {
		    (float)joyState.Gamepad.sThumbLX / SHRT_MAX * speed, 0.0f,
		    (float)joyState.Gamepad.sThumbLY / SHRT_MAX * speed};

		// 移動量に速さを反映
		move2 = Normalize2(move2);
		move2 = Multiply(speed, move2);
		
		

		// 移動
		worldTransform_.translation_ = Add(worldTransform_.translation_, move2);
		
		

		
	}
	worldTransform_.UpdateMatrix();

	
	
	

	ImGui::Begin("Window");
	ImGui::DragFloat3("position", &worldTransform_.translation_.x, 1.0f);
	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) { 
	
	model_->Draw(worldTransform_, viewProjection); 
	
}

//void Player::ScreenWorldTransformation(ViewProjection& viewProjection) {
//	//POINT mousePosition;
//	//// マウス座標(スクリーン座標)を取得する
//	//GetCursorPos(&mousePosition);
//
//	//// クライアントエリア座標に変換する
//	//HWND hwnd = WinApp::GetInstance()->GetHwnd();
//	//ScreenToClient(hwnd, &mousePosition);
//
//	//// スプライトのレティクルに座標設定
//	//sprite2DReticle_->SetPosition(Vector2((float)mousePosition.x, (float)mousePosition.y));
//
//	//// ビューポート行列
//	//Matrix4x4 matViewport =
//	//    MakeViewportMatrix(0, 0, WinApp::kWindowWidth, WinApp::kWindowHeight, 0, 1);
//
//	//Matrix4x4 matInverseViewport = Inverse(matViewport);
//	//Matrix4x4 matInverseView = Inverse(viewProjection.matView);
//	//Matrix4x4 matInverseProjection = Inverse(viewProjection.matProjection);
//
//	//// ビュープロジェクションビューポート合成行列
//	//Matrix4x4 matInverseVPV =
//	//    Multiply(Multiply(matInverseViewport, matInverseProjection), matInverseView);
//
//	//// Matrix4x4 matVPV = Multiply(Multiply(viewProjection.matView, viewProjection.matProjection),
//	//// matViewport);
//	//// 合成行列の逆行列を計算する
//	//// Matrix4x4 matInverseVPV = Inverse(matVPV);
//
//	//// スクリーン座標
//	//Vector3 posNear = Vector3((float)mousePosition.x, (float)mousePosition.y, 0);
//	//Vector3 posFar = Vector3((float)mousePosition.x, (float)mousePosition.y, 1);
//
//	//// スクリーン座標系からワールド座標系へ
//	//posNear = Transform(posNear, matInverseVPV);
//	//posFar = Transform(posFar, matInverseVPV);
//
//	//// マウスレイの方向
//	//Vector3 mouseDirection = Subtract(posFar, posNear);
//	//mouseDirection = Normalize(mouseDirection);
//	//// カメラから照準オブジェクトの座標
//	//const float kDistanceTestobject = 100;
//
//	//mouseDirection = Multiply(kDistanceTestobject, mouseDirection);
//
//	//worldTransform3DReticle_.translation_ = Add(posNear, mouseDirection);
//	//worldTransform3DReticle_.UpdateMatrix();
//
//	//ImGui::Begin("Player");
//
//	//ImGui::Text("Near:(%.2f,%.2f,%.2f)", posNear.x, posNear.y, posNear.z);
//	//ImGui::Text("Far:(%.2f,%.2f,%.2f)", posFar.x, posFar.y, posFar.z);
//	//ImGui::Text(
//	//    "3DReticle:(%.2f,%.2f,%.2f)", worldTransform3DReticle_.translation_.x,
//	//    worldTransform3DReticle_.translation_.y, worldTransform3DReticle_.translation_.z);
//	//ImGui::End();
//}