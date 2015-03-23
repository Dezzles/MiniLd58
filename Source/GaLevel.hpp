#ifndef GALEVEL_HPP
#define GALEVEL_HPP

#include "Bubblewrap/Base/Defines.hpp"
#include "Bubblewrap/Base/Component.hpp"
#include "Bubblewrap/Base/Base.hpp"
#include "Bubblewrap/Math/Vector2.hpp"
#include "Bubblewrap/Events/Events.hpp"

class GaLevel : public Bubblewrap::Base::Component
{ 
public:
	GaLevel();
	void Initialise( Json::Value Params );

	void Update( float dt );
	CREATE_REGISTER( GaLevel );

	virtual void OnAttach();
	virtual void OnDetach();
	void InputFunction( Bubblewrap::Events::Event* Event );
private:


};


#endif