#ifndef GATEXTCONTROLLER_HPP
#define GATEXTCONTROLLER_HPP

#include "Bubblewrap/Base/Defines.hpp"
#include "Bubblewrap/Base/Component.hpp"
#include "Bubblewrap/Base/Base.hpp"
#include "Bubblewrap/Events/Event.hpp"
#include "Bubblewrap/Events/EventHandle.hpp"
#include "Bubblewrap/Render/Text.hpp"
#include "Bubblewrap/Data/StringList.hpp"

class GaTextController : public Bubblewrap::Base::Component
{ 
public:
	GaTextController();
	void Initialise( Json::Value Params );

	void Update( float dt );
	CREATE_REGISTER( GaTextController );

	virtual void OnAttach();
	virtual void OnDetach();
	void OnCollision( Bubblewrap::Events::Event* Event );
private:

	Bubblewrap::Events::EventHandle CollisionHandle_;

	std::string StringListName_;
	float DisplayTime_;
	Bubblewrap::Render::Text* MyText_;
	Bubblewrap::Data::StringList* AllStrings_;


	float TimeLeftToDisplay_;
	bool Visible_;
	static int PreviousItem_;
};


#endif