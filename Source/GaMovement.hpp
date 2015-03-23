#ifndef GAMOVEMENT_HPP
#define GAMOVEMENT_HPP

#include "Bubblewrap/Base/Defines.hpp"
#include "Bubblewrap/Base/Component.hpp"
#include "Bubblewrap/Base/Base.hpp"
#include "Bubblewrap/Math/Vector2.hpp"
#include "Bubblewrap/Events/Events.hpp"

class GaMovement : public Bubblewrap::Base::Component
{ 
public:
	GaMovement();
	void Initialise( Json::Value Params );

	void Update( float dt );
	CREATE_REGISTER( GaMovement );

	virtual void OnAttach();
	virtual void OnDetach();
	void InputFunction( Bubblewrap::Events::Event* Event );
private:
	Bubblewrap::Math::Vector2f Position_;
	float Direction_;
	float Radius_;
	float Theta_;
	
	Bubblewrap::Events::Key Key_;


	unsigned int InputIdx_;
};


#endif