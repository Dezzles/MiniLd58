#ifndef GAPONG_HPP
#define GAPONG_HPP

#include "Bubblewrap/Base/Defines.hpp"
#include "Bubblewrap/Base/Component.hpp"
#include "Bubblewrap/Base/Base.hpp"
#include "Bubblewrap/Math/Vector2.hpp"
#include "Bubblewrap/Events/Events.hpp"

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

	float MovementSpeed_;

	float MinLocation_;
	float MaxLocation_;
	float XPosition_;

	Bubblewrap::Math::Vector2f SpriteSize_;
};


#endif