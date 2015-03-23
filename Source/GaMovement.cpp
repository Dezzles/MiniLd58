#include "GaMovement.hpp"
#include "Bubblewrap/Base/Entity.hpp"
#include "Bubblewrap/Events/EventKeyInput.hpp"
#include "Bubblewrap/Managers/Managers.hpp"
GaMovement::GaMovement()
{
	Theta_ = 0.0f;
}

void GaMovement::Initialise( Json::Value Params )
{
	Radius_ = Params[ "radius" ].asFloat();
	Direction_ = Params[ "direction" ].asFloat();
	Position_ = Bubblewrap::Math::Vector2f( Params[ "position" ][ "x" ].asFloat(), Params[ "position" ][ "y" ].asFloat() );
	if ( Params[ "key" ].asString()[ 0 ] == 'a' )
		Key_ = Bubblewrap::Events::Key::A;
	else 
		Key_ = Bubblewrap::Events::Key::D;
}

void GaMovement::Update( float dt )
{
	Theta_ += Direction_ * dt;
	GetParentEntity()->SetLocalPosition( Position_ + Bubblewrap::Math::Vector2f::FromPolarCoords( Theta_, Radius_ ) );
}

void GaMovement::Copy( GaMovement* Target, GaMovement* Base )
{	
	Target->Direction_ = Base->Direction_;
	Target->Radius_ = Base->Radius_;
	Target->Position_ = Base->Position_;
	Target->Theta_ = Base->Theta_ ;
	Target->Key_ = Base->Key_;
}

void GaMovement::InputFunction( Bubblewrap::Events::Event* Event )
{
	Bubblewrap::Events::InputData data = *( Bubblewrap::Events::InputData* )Event->GetData();
	if ( ( data.Key_ == Key_ ) && ( data.InputType_ == Bubblewrap::Events::InputData::InputType::KeyUp ) )
	{
		Direction_ = -Direction_;
	}
}


void GaMovement::OnAttach()
{
	InputIdx_ = GetManager().GetEventManager().RegisterEvent(Bubblewrap::Events::EventTypes::Input, 
 															  std::bind( &GaMovement::InputFunction, this, std::placeholders::_1 ) );
}

void GaMovement::OnDetach()
{

}