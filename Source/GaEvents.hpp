#ifndef GAEVENTS_HPP
#define GAEVENTS_HPP

#include "Bubblewrap/Events/EventKeyInput.hpp"
#include "Bubblewrap/Events/Events.hpp"
#include "Bubblewrap/Base/Entity.hpp"

enum GaEvents
{
	GaCollissionEvent = Bubblewrap::Events::EventTypes::LastEvent,
	GaScoreEvent
};

class GaCollisionEvent 
	: public Bubblewrap::Events::EventData
{
public :
	GaCollisionEvent( Bubblewrap::Base::Entity* Target )
		: Target_( Target )
	{

	}
	Bubblewrap::Base::Entity* Target_;
};

#endif