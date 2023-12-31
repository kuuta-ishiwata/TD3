#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "AxisIndicator.h"


GameScene::GameScene() {}

GameScene::~GameScene() {}



void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	model_.reset(Model::Create());
	worldTransform_.Initialize();
	viewProjection_.Initialize();

	//// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//skydome
	viewProjection_.farZ = 1400.0f;


	skydomeModel_.reset(Model::CreateFromOBJ("skydome", true));

	skydome_ = std::make_unique<Skydome>();

	skydome_->Initialize(skydomeModel_.get());


	// グラウンド
	groundModel_.reset(Model::CreateFromOBJ("ground", true));

	// グラウンド
	ground_ = std::make_unique<Ground>();

	ground_->Initialize(groundModel_.get());

	//敵
	modelFighterBody_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterBody2_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterBody3_.reset(Model::CreateFromOBJ("float_Body", true));
	modelFighterBody4_.reset(Model::CreateFromOBJ("float_Body", true));

	

	std::vector<Model*> enemyModels = {
	    modelFighterBody_.get(), modelFighterBody_.get(), modelFighterBody_.get(),
	    modelFighterBody_.get(),   

	
	};

	enemy_ = std::make_unique<Enemy>();

	enemy_->Initialize(enemyModels);
	

	
	
	// フォローカメラ
	followCamera_ = std::make_unique<FollowCamera>();
	followCamera_->Initialize();

	//敵キャラに追従カメラセット

	followCamera_->SetTarget(&enemy_->GetWorldTransform());
	enemy_->SetViewProjection(&followCamera_->GetViewProjection());


	//// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);
	//// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	textureHandle_ = TextureManager::Load("sample.png");

	player_ = std::make_unique<Player>();
	// 自キャラの初期化
	player_->Initialize(model_.get(), textureHandle_);

		

}

void GameScene::Update() {

	// 天球
	skydome_->Update();

	// グラウンド
	ground_->Update();

	player_->Update(viewProjection_);

	// 敵
	enemy_->Update();



	worldTransform_.TransferMatrix();
	viewProjection_.UpdateMatrix();

	

	if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == false) {
		isDebugCameraActive_ = true;

	} else if (input_->TriggerKey(DIK_K) == isDebugCameraActive_ == true) {
		isDebugCameraActive_ = false;
	}


	// カメラ処理
	if (isDebugCameraActive_) {
		// followCamera_->Update();

		debugCamera_->Update();

		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		
		

		// ビュープロジェクション行列の転送
		viewProjection_.TransferMatrix();
	} 
	else {

		
		followCamera_->Update();

		viewProjection_.matView = followCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

		// viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		// viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;

		// ビュープロジェクション行列の更新と転送
		viewProjection_.TransferMatrix();
	}

	//EnemyObjUpdate();

	// UpdateEnemyPopCommands();


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

	ground_->Draw(viewProjection_);

	skydome_->Draw(viewProjection_);

	enemy_->Draw(viewProjection_);

	//EnemyObjDraw();


	
	player_->Draw(viewProjection_);

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


//void GameScene::EnemySpawn(Vector3& Position) {
//
//	
//
//
//}
//void GameScene::CheckAllCollisions() {}


