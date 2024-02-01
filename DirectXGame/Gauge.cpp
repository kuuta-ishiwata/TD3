#include "Gauge.h"

Gauge::Gauge() {}

Gauge::~Gauge() { delete GaugeSprite_; }

void Gauge::Initialize() 
{
	
	GaugeSprite = TextureManager::Load("Gauge.png");

	GaugeSprite_ = Sprite::Create(GaugeSprite, {1150, 600}, {1, 1, 1, 1}, {1,1});

	worldTransform_.Initialize();

	GaugeSprite_->SetSize(size_);

	size_ = {100,400};

}

void Gauge::Update() 
{ 

	
	if (size_.y >= 0)
	{
		size_.y -= 0.4f;
		GaugeSprite_->SetSize(size_);
	}


}


void Gauge::Draw()
{

	
	GaugeSprite_->Draw();

	
}