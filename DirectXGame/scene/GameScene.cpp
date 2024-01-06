#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>

GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	worldTransform_.Initialize();

	viewProjection_.Initialize();
	viewProjection_.farZ = 1400.0f;

	// テクスチャ
	textureHandle_ = TextureManager::Load("sample.png");

	// モデル
	model_.reset(Model::Create());
	// スカイドーム
	skydomeModel_.reset(Model::CreateFromOBJ("skydome", true));
	// グラウンド
	groundModel_.reset(Model::CreateFromOBJ("ground", true));
	// 敵
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterBody2_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterBody3_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterBody4_.reset(Model::CreateFromOBJ("float_Body", true));

	// skydome
	skydome_ = std::make_unique<Skydome>();
	skydome_->Initialize(skydomeModel_.get());

	// グラウンド
	ground_ = std::make_unique<Ground>();
	ground_->Initialize(groundModel_.get());

	// フォローカメラ
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();

	//// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 自キャラの初期化
	player_ = std::make_unique<Player>();
	player_->Initialize(model_.get(), textureHandle_);
	// 自キャラに追従カメラセット
	followCamera_->SetTarget(&player_->GetWorldTransform());

	
	// 敵キャラの初期化
	//std::vector<Model*> enemyModels = {
	//    modelFighterBody_.get(),
	//    modelFighterBody_.get(),
	//    modelFighterBody_.get(),
	//    modelFighterBody_.get(),
	//};
	//enemy_ = std::make_unique<Enemy>();
	//enemy_->Initialize(enemyModels);

	//// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {

	// 天球
	skydome_->Update();

	// グラウンド
	ground_->Update();

	player_->Update(viewProjection_);

	worldTransform_.TransferMatrix();
	viewProjection_.UpdateMatrix();

	// if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == false) {
	//	isDebugCameraActive_ = true;
	//
	// } else if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == true) {
	//	isDebugCameraActive_ = false;
	// }

	// カメラ処理
	if (isDebugCameraActive_) {
		// followCamera_->Update();

		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} else {

		followCamera_->Update();

		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		// viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		// viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の更新と転送
		viewProjection_.TransferMatrix();
	}

	// 天球
	skydome_->Update();

	// グラウンド
	ground_->Update();

	// 敵
	//enemy_->Update();
}

void GameScene::Draw() {

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

	player_->Draw(viewProjection_);

	ground_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::EnemyPop(Vector3 pos)
{

	//敵キャラ初期化
	std::vector<Model*> enemyModels = {
	    modelFighterBody_.get(),
	    modelFighterBody_.get(),
	    modelFighterBody_.get(),
	    modelFighterBody_.get(),
	};


	//敵の生成処理
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();

	//初期化
	newEnemy->Initialize(enemyModels);
	// リストに敵を登録する, std::moveでユニークポインタの所有権移動
	enemy_.push_back(std::move(newEnemy));

	for (std::unique_ptr<Enemy>& enemy : enemy_)
	{
		SetEnemyPopPos(pos);
		enemy->SetViewProjection(&followCamera_->GetViewProjection());
		enemy->SetGameScene();
		// 更新
		enemy->Update();

	}

}