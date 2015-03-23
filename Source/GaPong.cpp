#include "GaPong.hpp"
#include "Bubblewrap/Base/Entity.hpp"
#include "Bubblewrap/Events/EventKeyInput.hpp"
#include "Bubblewrap/Managers/Managers.hpp"
#include "Bubblewrap/Render/Sprite.hpp"
GaPong::GaPong()
{
}

void GaPong::Initialise( Json::Value Params )
{
	MovementSpeed_ = Params[ "movementSpeed" ].asFloat();
	MinLocation_ = Params[ "minLocation" ].asFloat();
	MaxLocation_ = Params[ "maxLocation" ].asFloat();
	XPosition_ = Params[ "xPosition" ].asFloat();
}

void GaPong::Update( float dt )
{
	Bubblewrap::Math::Vector2f pos = GetParentEntity()->LocalPosition();

	float moveSpeed = 0.0f;

	pos = pos + Bubblewrap::Math::Vector2f(0.0f, moveSpeed * dt * MovementSpeed_);

	if ( pos.Y() - SpriteSize_.Y() * .5f <= MinLocation_ )
		pos = Bubblewrap::Math::Vector2f( pos.X(), MinLocation_ + SpriteSize_.Y() / 2.0f );
	if ( pos.Y() + SpriteSize_.Y() * .5f >= MaxLocation_ )
		pos = Bubblewrap::Math::Vector2f( pos.X(), MaxLocation_ - SpriteSize_.Y() / 2.0f );

	GetParentEntity()->SetLocalPosition(pos);
}

void GaPong::Copy( GaPong* Target, GaPong* Base )
{	
	Target->MovementSpeed_ = Base->MovementSpeed_;
	Target->MaxLocation_ = Base->MaxLocation_;
	Target->MinLocation_ = Base->MinLocation_;
	Target->XPosition_ = Base->XPosition_;
}

void GaPong::InputFunction( Bubblewrap::Events::Event* Event )
{

}


void GaPong::OnAttach()
{
	GetParentEntity()->SetLocalPosition(Bubblewrap::Math::Vector2f(XPosition_, (MaxLocation_ + MinLocation_) * 0.5f));
}

void GaPong::OnDetach()
{

}