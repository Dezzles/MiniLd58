#ifndef GAPONG_HPP
#define GAPONG_HPP

#include "Bubblewrap/Base/Defines.hpp"
#include "Bubblewrap/Base/Component.hpp"
#include "Bubblewrap/Base/Base.hpp"
#include "Bubblewrap/Math/Vector2.hpp"
#include "Bubblewrap/Events/Events.hpp"
#include "Bubblewrap/Math/Bounds1.hpp"
#include "Bubblewrap/Audio/Sound.hpp"
#include "GaLevel.hpp"
#include "GaPaddle.hpp"
class GaPong : public Bubblewrap::Base::Component
{ 
public:
	GaPong();
	void Initialise( Json::Value Params );

	void Update( float dt );
	CREATE_REGISTER( GaPong );

	virtual void OnAttach();
	virtual void OnDetach();
	void InputFunction( Bubblewrap::Events::Event* Event );
private:
	float Multiplier_;
	float CurrentSpeed_;
	Bubblewrap::Math::Bounds1f SpeedBounds_;


	Bubblewrap::Math::Vector2f SpriteSize_;
	GaLevel* Level_;

	Bubblewrap::Math::Vector3f MoveDirection_;

	std::vector<GaPaddle*> Paddles_;

	GaPaddle* CheckForCollisions();

	Bubblewrap::Audio::Sound* Sound_;
};


#endif