#include "GameClearScene.h"
#include <TextureManager.h>
GameClearScene::GameClearScene() {}

GameClearScene::~GameClearScene(){

};

void GameClearScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	uint32_t textureTitle = TextureManager::Load("finish.png");

	titlesprite_ =
	    Sprite::Create(textureTitle, {640.0f, 360.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.5f, 0.5f});

	score_ = std::make_unique<Score>();
	score_->Initialize();
	

	/*pos_[0] = {650.0f, 360.0f};
	pos_[1] = {630.0f, 360.0f};
	pos_[0] = score_->GetPos();
	pos_[1] = score_->GetPos2();
	pos_[0].x++;

	score_->SetPos(pos_[0]);
	score_->SetPos2(pos_[1]);*/


}

void GameClearScene::Update() {


	
	isClear_ = true;
	if (input_->PushKey(DIK_SPACE)) {
		isSceneEnd_ = true;
	}
	score_->Update();
}

void GameClearScene::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	score_->Draw();
	titlesprite_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameClearScene::Reset() 
{ isSceneEnd_ = false; }
