#include "GaTextController.hpp"
#include "Bubblewrap/Base/Entity.hpp"
#include "Bubblewrap/Base/ObjectRegister.hpp"
#include "Bubblewrap/Events/EventKeyInput.hpp"
#include "Bubblewrap/Managers/Managers.hpp"
#include "Bubblewrap/Render/Sprite.hpp"
#include "GaEvents.hpp"

int GaTextController::PreviousItem_ = -1;

GaTextController::GaTextController()
{
	Visible_ = false;
	TimeLeftToDisplay_ = 0.0f;
}

void GaTextController::Initialise( Json::Value Params )
{
	StringListName_ = Params[ "stringList" ].asString();
	DisplayTime_ = Params[ "displayTime" ].asFloat();
}

void GaTextController::Update( float dt )
{
	if ( Visible_ )
	{
		TimeLeftToDisplay_ -= dt;
		if ( TimeLeftToDisplay_ < 0.0f )
		{
			Visible_ = false;
			MyText_->SetVisible( false );
		}
	}
}

void GaTextController::Copy( GaTextController* Target, GaTextController* Base )
{
	Target->StringListName_ = Base->StringListName_;
	Target->DisplayTime_ = Base->DisplayTime_;
}

void GaTextController::OnCollision( Bubblewrap::Events::Event* Event )
{
	GaCollisionEvent* evt = ( GaCollisionEvent* )Event->GetData();
	if ( evt->Target_ != GetParentEntity() )
		return;
	int num = rand() % AllStrings_->Size();
	while ( num == PreviousItem_ )
	{
		num = rand() % AllStrings_->Size();
	}
	PreviousItem_ = num;
	MyText_->SetText(AllStrings_->GetItem( num ));
	TimeLeftToDisplay_ = DisplayTime_;
	Visible_  = true;
	MyText_->SetVisible( Visible_ );
}

void GaTextController::OnAttach()
{

	InputIdx_ = GetManager().GetEventManager().RegisterEvent( GaCollissionEvent,
		std::bind( &GaTextController::OnCollision, this, std::placeholders::_1 ) );
	AllStrings_ = (Bubblewrap::Data::StringList*)GetRegister().GetResource(StringListName_);
	MyText_ = GetParentEntity()->GetComponentsByType<Bubblewrap::Render::Text>()[0];
	MyText_->SetVisible(false);
}

void GaTextController::OnDetach()
{
	GetManager().GetEventManager().DeregisterEvent(InputIdx_);
}
