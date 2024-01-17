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
					// 自弾の衝突時コールバックを呼び出す
					player_->OnCollision();
					// 敵キャラの衝突時コールバックを呼び出す
					enemy->OnCollision();
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

	// エネミー
	LoadEnemyPopData();
	UpdateEnemyPopCommands();



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

	// 天球
	skydome_->Update();

	// グラウンド
	ground_->Update();

	CheckAllCollisions();

	//プレイヤー
	player_->Update(viewProjection_);

	// 敵の発生と更新
	UpdateEnemyPopCommands();
	for (std::unique_ptr<Enemy>& enemy : enemies_) {
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
void GameScene::UpdateEnemyPopCommands() {
	// 待機処理
	if (isWait) {
		waitTimer--;
		if (waitTimer <= 0) {
			// 待機完了
			isWait = false;
		}
		return;
	}

	// 1行文の文字列を入れる変数
	std::string line;

	// コマンド実行ループ
	while (getline(enemyPopCommands, line)) {
		// 1行文分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		std::string word;
		//,区切りで行の先頭文字列を取得
		getline(line_stream, word, ',');
		//"//"から始まる行はコメント
		if (word.find("//") == 0) {
			// コメント行を飛ばす
			continue;
		}
		// POPコマンド
		if (word.find("POP") == 0) {
			// X座標
			getline(line_stream, word, ',');
			float x = (float)std::atof(word.c_str());

			// Y座標
			getline(line_stream, word, ',');
			float y = (float)std::atof(word.c_str());

			// Z座標
			getline(line_stream, word, ',');
			float z = (float)std::atof(word.c_str());

			// 敵を発生させる
			EnemyPop(Vector3(x, y, z));
		}
		// WAITコマンド
		else if (word.find("WAIT") == 0) {
			getline(line_stream, word, ',');

			// 待ち時間
			int32_t waitTime = atoi(word.c_str());

			// 待機開始
			isWait = true;
			waitTimer = waitTime;

			// コマンドループを抜ける
			break; // 重要
		}
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

	// 敵の生成
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();

	// 初期化
	newEnemy->Initialize(enemyModels);
	// リストに敵を登録する, std::moveでユニークポインタの所有権移動
	enemies_.push_back(std::move(newEnemy));

	// イテレータ
	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		// 各セッターに値を代入
		SetEnemyPopPos(pos);
		enemy->GetViewProjection(&followCamera_->GetViewProjection());
		enemy->SetGameScene(this);
		// 更新
		enemy->Update();
	}
}