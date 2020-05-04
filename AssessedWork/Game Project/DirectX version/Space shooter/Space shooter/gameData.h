#pragma once
#include"SimpleMath.h"
#include"Singleton.h"
struct gameData : public Singleton<gameData> {
	const DirectX::SimpleMath::Vector2 MaxWindowSize = DirectX::SimpleMath::Vector2(1920, 1080);
	const DirectX::SimpleMath::Vector2 DefaultWindowSize = DirectX::SimpleMath::Vector2(1280, 720);
	DirectX::SimpleMath::Vector2 WindowSize = DefaultWindowSize;

};