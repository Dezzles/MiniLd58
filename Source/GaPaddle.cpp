#include "GaPaddle.hpp"
#include "Bubblewrap/Base/Entity.hpp"
#include "Bubblewrap/Events/EventKeyInput.hpp"
#include "Bubblewrap/Managers/Managers.hpp"
#include "Bubblewrap/Render/Sprite.hpp"
GaPaddle::GaPaddle()
{
	UpKeyDown_ = false;
	DownKeyDown_ = false;
}

void GaPaddle::Initialise( Json::Value Params )
{
	IsPlayer_ = Params[ "isPlayer" ].asBool();
	MovementSpeed_ = Params[ "movementSpeed" ].asFloat();
	MinLocation_ = Params[ "minLocation" ].asFloat();
	MaxLocation_ = Params[ "maxLocation" ].asFloat();
	XPosition_ = Params[ "xPosition" ].asFloat();
}

void GaPaddle::Update( float dt )
{
	Bubblewrap::Math::Vector2f pos = GetParentEntity()->LocalPosition();

	float moveSpeed = 0.0f;
	if ( UpKeyDown_ )
		moveSpeed -= 1.0f;
	if ( DownKeyDown_ )
		moveSpeed += 1.0f;

	pos = pos + Bubblewrap::Math::Vector2f(0.0f, moveSpeed * dt * MovementSpeed_);

	if ( pos.Y() - SpriteSize_.Y() * .5f <= MinLocation_ )
		pos = Bubblewrap::Math::Vector2f( pos.X(), MinLocation_ + SpriteSize_.Y() / 2.0f );
	if ( pos.Y() + SpriteSize_.Y() * .5f >= MaxLocation_ )
		pos = Bubblewrap::Math::Vector2f( pos.X(), MaxLocation_ - SpriteSize_.Y() / 2.0f );

	GetParentEntity()->SetLocalPosition(pos);
}

void GaPaddle::Copy( GaPaddle* Target, GaPaddle* Base )
{	
	Target->IsPlayer_ = Base->IsPlayer_;
	Target->MovementSpeed_ = Base->MovementSpeed_;
	Target->MaxLocation_ = Base->MaxLocation_;
	Target->MinLocation_ = Base->MinLocation_;
	Target->XPosition_ = Base->XPosition_;
}

void GaPaddle::InputFunction( Bubblewrap::Events::Event* Event )
{
	Bubblewrap::Events::InputData data = *( Bubblewrap::Events::InputData* )Event->GetData();
	if ( data.Key_ == Bubblewrap::Events::Key::W )
	{
		UpKeyDown_ = ( data.InputType_ != Bubblewrap::Events::InputData::InputType::KeyUp );
	}
	if ( data.Key_ == Bubblewrap::Events::Key::S )
	{
		DownKeyDown_ = ( data.InputType_ != Bubblewrap::Events::InputData::InputType::KeyUp );
	}
}


void GaPaddle::OnAttach()
{
	InputIdx_ = GetManager().GetEventManager().RegisterEvent(Bubblewrap::Events::EventTypes::Input, 
		std::bind( &GaPaddle::InputFunction, this, std::placeholders::_1 ) );

	SpriteSize_ = GetParentEntity()->GetComponentsByType<Bubblewrap::Render::Sprite>()[ 0 ]->GetSize();

	GetParentEntity()->SetLocalPosition(Bubblewrap::Math::Vector2f(XPosition_, (MaxLocation_ + MinLocation_) * 0.5f));
}

void GaPaddle::OnDetach()
{
	GetManager().GetEventManager().DeregisterEvent( InputIdx_ );
}