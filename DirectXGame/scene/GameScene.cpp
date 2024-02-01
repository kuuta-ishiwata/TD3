#include "GameScene.h"

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
				if (posA.x + 1.0f >= posB.x && posA.x <= posB.x + 1.0f) 
				{

					player_->AttackOnCollision();

					// 攻撃している時
					if (player_->isAttack()) 
					{

						// コマンドリセット
						gameInput_->Reset();
						// コマンド決定
						gameInput_->Update();
						// 時間を止める処理
						isTimeStop_ = true;


					} else {
						// 自キャラの衝突時コールバックを呼び出す
						player_->OnCollision();
					
					}

					// 敵キャラの衝突時コールバックを呼び出す
					enemy->OnCollision();
					commandCount_ = 0;

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
	// コマンド
	isCommandTex_ = TextureManager::Load("commandSuccessOrFailure.png");
	isCommandSprite_.reset(Sprite::Create(isCommandTex_, {0.0f, 0.0f}));
	isCommandSprite_->SetSize({180.0f, 180.0f});
	isCommandSprite_->SetTextureRect(
	    {
	        0.0f,
	        0.0f,
	    },
	    {120.0f, 120.0f});
	isCommandSprite_->SetPosition({550.0f, 330.0f});
	// 木
	treetextureHandle_ = TextureManager::Load("tree/treecolor.png");
	// 道
	loadtextureHandle_ = TextureManager::Load("straightroad/road.png");

	// モデル
	model_.reset(Model::CreateFromOBJ("inoshishi", true));

	//人間モデル
   // model_.reset(Model::CreateFromOBJ("Human", true));



	// スカイドーム
	skydomeModel_.reset(Model::CreateFromOBJ("skydome", true));
	// グラウンド
	groundModel_.reset(Model::CreateFromOBJ("ground", true));

	// 道
	loadModel_.reset(Model::CreateFromOBJ("straightroad", true));

	// 木
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

	// 道
	road_ = std::make_unique<Load>();
	road_->Initialize(loadModel_.get(), loadtextureHandle_);

	// 木
	for (int i = 0; i < 80; i++) {
		tree_[i] = std::make_unique<Tree>();
		tree_[i]->Initialize(treeModel_.get(), treetextureHandle_);
	}

	// コマンド
	gameInput_ = GameInput::GetInstance();

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

	//// 軸方向表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(false);
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	isTimeStop_ = false;
	commandCount_ = 0;
	isCoomand_ = false;
	isCommandCount_ = 0;
	enemyKillCount_ = 0;
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

	// 道
	road_->Update();

	// 木
	for (int i = 0; i < 80; i++) {
		tree_[i]->Update();
	}
	// プレイヤー
	if (!isTimeStop_) {
		player_->Update(viewProjection_);
	}

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

	// 当たり判定
	CheckAllCollisions();
	// コマンド処理
	if (isTimeStop_) {
		// コマンド入力
		gameInput_->InputCommand();
		// コマンド成功
		if (gameInput_->CommandClear()) {
			isCoomand_ = true;
			isCommandSprite_->SetTextureRect({0.0f, 0.0f}, {120.0f, 120.0f});
			isTimeStop_ = false;
			commandCount_ = 0;
			enemyKillCount_++;
		}
		// 時間切れ
		else {
			if (++commandCount_ >= 120) {
				// 自キャラの衝突時コールバックを呼び出す
				player_->OnCollision();
				isTimeStop_ = false;
				commandCount_ = 0;
				isCoomand_ = true;
				isCommandSprite_->SetTextureRect({120.0f, 0.0f}, {120.0f, 120.0f});
			}
		}
	}

	if (isCoomand_) {
		if (++isCommandCount_ >= 20) {
			isCoomand_ = false;
			isCommandCount_ = 0;
		}
	}

#ifdef _DEBUG

	ImGui::Begin("window");
	if (ImGui::TreeNode("Enemy")) {
		ImGui::Text("kill count %d", enemyKillCount_);
		ImGui::TreePop();
	}
	ImGui::End();

#endif // _DEBUG

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

	road_->Draw(viewProjection_);

	for (int i = 0; i < 40; ++i)
	{
		if (player_->GetWorldPosition().y <= 5.0f) 
		{
			if (player_->GetWorldPosition().z - 15.0f <= float(i * 10.0f))
			{
				tree_[i]->Draw(viewProjection_, Vector3{5.4f, 0, float(i * 10)});
				tree_[i + 40]->Draw(viewProjection_, Vector3{-5.4f, 0, float(i * 10)});
			}
		}
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

	if (isTimeStop_) {
		gameInput_->GetInstance()->Draw();
	}
	if (isCoomand_) {
		isCommandSprite_->Draw();
	}

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

// 敵発生コマンドの更新
void GameScene::UpdateEnemyPopCommands() {
	if (player_->GetIsBack()) {
		// 敵を発生させる
		for (int i = 0; i < 40; ++i) {
			EnemyPop(Vector3(0.0f, 0.0f, float((i + 1) * 20.0f)));
		}
		player_->SetIsBack(false);
	}
}

// 敵発生関数
void GameScene::EnemyPop(Vector3 pos) {
	// 敵キャラの初期化
	std::vector<Model*> enemyModels = {
	    modelFighterBody_.get(),
	    modelFighterBody2_.get(),
	    modelFighterBody3_.get(),
	    modelFighterBody4_.get(),
	};

	// 敵の生成
	std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();

	// 初期化
	newEnemy->Initialize(enemyModels);
	newEnemy->SetPos(pos);

	// リストに敵を登録する, std::moveでユニークポインタの所有権移動
	enemies_.push_back(std::move(newEnemy));

	// イテレータ
	for (std::unique_ptr<Enemy>& enemy : enemies_) {
		// 各セッターに値を代入

		enemy->GetViewProjection(&followCamera_->GetViewProjection());
		enemy->SetGameScene(this);
		// 更新
		enemy->Update();
	}
}