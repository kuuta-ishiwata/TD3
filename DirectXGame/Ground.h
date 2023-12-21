#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"

class Ground {

public:

	void Initialize(Model* model);

	void Update();

	void Draw(ViewProjection& viewprojection);

private:

	
	// ワールド変更データ
	WorldTransform worldtransform_;

	// モデル
	Model* model_ = nullptr;

	//ViewProjection viewprojection_;






};
