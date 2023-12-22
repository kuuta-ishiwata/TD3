#include "RailCamera.h"
#include "MATHEX.h"
#include "ImGuiManager.h"

void RailCamera::Initialize() {

	worldTransform_.Initialize();

	// ビュープロジェクション初期化
	viewProjection_.Initialize();

	// ビュープロジェクションの初期化
	//viewProjection_.farZ = 3000.0f;

	//worldTransform_.translation_.y = 5.0f;
}

void RailCamera::Update() {

	// worldTransform_.translation_.z += 0.05f;

	worldTransform_.UpdateMatrix();

	// カメラオブジェクトのワールド行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);

	viewProjection_.UpdateMatrix();

	// カメラの座標を画面表示する処理
}