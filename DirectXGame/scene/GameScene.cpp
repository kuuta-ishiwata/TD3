#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <map>


GameScene::GameScene() {}

GameScene::~GameScene() {}


void GameScene::CheckAllCollisions() {

	// 判定対象AとBの座標
	Vector3 posA, posB;
#pragma region 自キャラと敵キャラの当たり判定
	// 自キャラの座標
	posA = player_->GetWorldPosition();

	// 敵キャラの座標
	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		posB = enemy->GetWorldPosition();

		// 座標AとBの距離を求める
		// 交差判定
		if (posA.z + 1.0f >= posB.z && posA.z <= posB.z + 1.0f) {
			if (posA.y + 1.0f >= posB.y && posA.y <= posB.y + 1.0f) {
				if (posA.x + 1.0f >= posB.x && posA.x <= posB.x + 1.0f) {

					gameInput_->Upadte();
					// 自弾の衝突時コールバックを呼び出す
					player_->OnCollision();
					// 敵キャラの衝突時コールバックを呼び出す
					enemy->OnCollision();
					enemyCount--;
				}
			}
		}
	}
#pragma endregion
}


void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	worldTransform_.Initialize();

	viewProjection_.Initialize();
	viewProjection_.farZ = 1400.0f;

	// テクスチャ
	textureHandle_ = TextureManager::Load("inoshishi/tex.png");
	//木
	treetextureHandle_ = TextureManager::Load("tree/treecolor.png");
	//道
	loadtextureHandle_ = TextureManager::Load("straightroad/road.png");

	// モデル
	model_.reset(Model::CreateFromOBJ("inoshishi",true));

	// スカイドーム
	skydomeModel_.reset(Model::CreateFromOBJ("skydome", true));
	// グラウンド
	groundModel_.reset(Model::CreateFromOBJ("ground", true));

	//道
	loadModel_.reset(Model::CreateFromOBJ("straightroad", true));


	//木
	treeModel_.reset(Model::CreateFromOBJ("tree", true));


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

	//道
	load_ = std::make_unique<Load>();
	load_->Initialize(loadModel_.get(),loadtextureHandle_);

	//木
	for (int i = 0; i < 80; i++)
	{
		tree_[i] = std::make_unique<Tree>();
		tree_[i]->Initialize(treeModel_.get(), treetextureHandle_);
	}

	//コマンド
	gameInput_->GetInstance();

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

	// エネミー
	UpdateEnemyPopCommands();
	enemyCount = 0;


	//// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {

	// ビュープロジェクション行列の更新と転送
	viewProjection_.UpdateMatrix();

	followCamera_->Update();
	viewProjection_.matView = followCamera_->GetViewProjection().matView;
	viewProjection_.matProjection = followCamera_->GetViewProjection().matProjection;

	viewProjection_.TransferMatrix();

	// コマンド
	

	// 天球
	skydome_->Update();

	// グラウンド
	ground_->Update();

	CheckAllCollisions();

	load_->Update();

	for (int i = 0; i < 80; i++) 
	{
		tree_[i]->Update();
	}
	

	//プレイヤー
	player_->Update(viewProjection_);

	// 敵の発生と更新
	UpdateEnemyPopCommands();
	for (std::unique_ptr<Enemy>& enemy : enemies_) 
	{
		enemy->Update();
	}
	// デスフラグの立った敵を削除
	enemies_.remove_if([](std::unique_ptr<Enemy>& enemy) {
		if (enemy->IsDead()) {
			delete enemy.release();
			return true;
		}
		return false;
	});

	worldTransform_.UpdateMatrix();

	#ifdef _DEBUG

	    ImGui::Begin("window");
	if (ImGui::TreeNode("Enemy")) {
		ImGui::Text("count %d", enemyCount);
		ImGui::TreePop();
	}
	ImGui::End();

#endif // _DEBUG

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

	skydome_->Draw(viewProjection_);

	ground_->Draw(viewProjection_);

	load_->Draw(viewProjection_);
	
	for (int i = 0; i < 40; ++i)
	{
		
			tree_[i]->Draw(viewProjection_, Vector3{5.4f, 0, float(i * 10)});
		
			
	}

	for (int i = 0; i < 40; ++i) {

		tree_[i +40]->Draw(viewProjection_, Vector3{-5.4f, 0, float(i  * 10)});

	}

	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		enemy->Draw(viewProjection_);
	}

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


//void GameScene::EnemyPop(Vector3 pos)
//{

	//敵キャラ初期化
// void GameScene::CheckAllCollisions() {}

// 敵発生データの読み込み
void GameScene::LoadEnemyPopData() {
	// ファイルを開く
	std::ifstream file;
	file.open("./Resources/enemyPop.csv");
	assert(file.is_open());

	// ファイルの内容を文字列ストリームにコピー
	enemyPopCommands << file.rdbuf();

	// ファイルを閉じる
	file.close();

}

// 敵発生コマンドの更新
void GameScene::UpdateEnemyPopCommands() 
{


	
	
		if (enemyCount < 40)
		{
		
			// 敵を発生させる
			EnemyPop(Vector3(0, 0, 0 * 10.0f));
		


		}
	
}

// 敵発生関数
void GameScene::EnemyPop(Vector3 pos) {
	// 敵キャラの初期化
	std::vector<Model*> enemyModels = {
	    modelFighterBody_.get(),
	    modelFighterBody_.get(),
	    modelFighterBody_.get(),
	    modelFighterBody_.get(),

	};

	enemyCount++;

	// 敵の生成
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();

	// 初期化
	newEnemy->Initialize(enemyModels);

	newEnemy->SetPos(Vector3{pos.x, pos.y, float(enemyCount * 10)});
	// リストに敵を登録する, std::moveでユニークポインタの所有権移動
	enemies_.push_back(std::move(newEnemy));

	// イテレータ
	for (std::unique_ptr<Enemy>& enemy : enemies_) 
	{
		// 各セッターに値を代入
	  
		    
		enemy->GetViewProjection(&followCamera_->GetViewProjection());
		enemy->SetGameScene(this);
		// 更新
		enemy->Update();
	}


}