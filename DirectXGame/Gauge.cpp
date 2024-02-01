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

		size_.y -= speed_;
		GaugeSprite_->SetSize(size_);

	}


	if (flag == true)
	{
		ImGuiflag = 1;
	}
	else
	{
		ImGuiflag = 0;
	}

	if (flag == true) {
		speed_ = 0;
	} else {
		speed_ = 0.4f;
	}

#ifdef _DEBUG
	ImGui::Begin("window");

	ImGui::DragInt("flag", &ImGuiflag);

	
	ImGui::End();

#endif // _DEBUG

}


void Gauge::Draw()
{

	
	GaugeSprite_->Draw();

	
}


void Gauge::Incorrect() { size_.y -= 10.0f; }

void Gauge::flagOnCollision() { flag = true; }

void Gauge::flagOnCollision2() {flag = false;}

