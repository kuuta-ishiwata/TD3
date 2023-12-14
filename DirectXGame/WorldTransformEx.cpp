﻿#include "MATHEX.h"
#include "Model.h"
#include "WorldTransform.h"

void WorldTransform::UpdateMatrix() {

	// スケール、回転、平行移動
	matWorld_ = MakeAffineMatrix(scale_, rotation_, translation_);

	if (parent_) {

		matWorld_ = Multiply(matWorld_, parent_->matWorld_);
	}

	// 定数バッファに転送
	TransferMatrix();
}