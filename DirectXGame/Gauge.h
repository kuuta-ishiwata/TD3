#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"



class Gauge {

public:


	void Initialize();

	void Update();

	void Draw(ViewProjection* viewprojection_);




private:


	// ワールド変換データ
	WorldTransform worldTransform_;

	const ViewProjection* viewProjection_ = nullptr;





};
