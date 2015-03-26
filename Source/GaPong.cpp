#include "GaPong.hpp"
#include "Bubblewrap/Base/Entity.hpp"
#include "Bubblewrap/Events/EventKeyInput.hpp"
#include "Bubblewrap/Managers/Managers.hpp"
#include "Bubblewrap/Render/Sprite.hpp"
#include "GaEvents.hpp"
GaPong::GaPong()
{
}

void GaPong::Initialise( Json::Value Params )
{
	Multiplier_ = Params[ "multiplier" ].asFloat();
	float lowerSpeed = Params[ "minSpeed" ].asFloat();
	float upperSpeed = Params[ "maxSpeed" ].asFloat();
	SpeedBounds_.SetBounds( lowerSpeed, upperSpeed );
	CurrentSpeed_ = SpeedBounds_.Lower();
}

void GaPong::Update( float dt )
{
	Bubblewrap::Math::Vector2f StartPos = GetParentEntity()->WorldPosition();
	Bubblewrap::Math::Vector2f pos = GetParentEntity()->LocalPosition();

	pos = pos + MoveDirection_ * CurrentSpeed_ * dt;

	Bubblewrap::Math::Bounds1f bounds = Level_->GetBounds( pos.X() );
	Bubblewrap::Math::Bounds1f sideBounds = Level_->GetSideBounds( );
	float halfSprite = SpriteSize_.Y() * 0.5f;
	float halfSpriteX = SpriteSize_.X() * 0.5f;
	if ( pos.Y() - halfSprite < bounds.Lower() )
	{
		MoveDirection_.SetY( -MoveDirection_.Y() );
		pos.SetY( bounds.Lower() + halfSprite );
	}
	if ( bounds.Upper() - halfSprite < pos.Y() )
	{
		MoveDirection_.SetY( -MoveDirection_.Y() );
		pos.SetY( bounds.Upper() - halfSprite );

	}/**/


	if ( !sideBounds.IsInside<float, float>( pos.X() - halfSpriteX, pos.X() + halfSpriteX ) )
	{
		MoveDirection_.SetX( -MoveDirection_.X() );

	}/**/

	GaPaddle* Hit = ( CheckForCollisions() );
	// Lets check if we've collided with anything yet...
	if ( Hit != nullptr )
	{
		
		// MoveDirection_.SetX( -MoveDirection_.X() );
		MoveDirection_ = ( GetParentEntity()->WorldPosition() - Hit->GetParentEntity()->WorldPosition() ).Normalised();
		CurrentSpeed_ = SpeedBounds_.Restrict( CurrentSpeed_ * Multiplier_ );
		pos = pos + 2.0f * MoveDirection_ * CurrentSpeed_ * dt;
		Bubblewrap::Events::Event evt( GaCollissionEvent, new GaCollisionEvent( Hit->GetParentEntity() ) );
		GetManager().GetEventManager().SendMessage(evt);
		printf("Current Speed: %f\n", CurrentSpeed_);
		GetParentEntity()->Destroy();
	}

	GetParentEntity()->SetLocalPosition( pos );
	Bubblewrap::Math::Vector2f EndPos = GetParentEntity()->WorldPosition();
}

void GaPong::Copy( GaPong* Target, GaPong* Base )
{	
	Target->SpeedBounds_ = Base->SpeedBounds_;
	Target->Multiplier_ = Base->Multiplier_;
	Target->CurrentSpeed_ = Base->CurrentSpeed_;
}

void GaPong::InputFunction( Bubblewrap::Events::Event* Event )
{

}


void GaPong::OnAttach()
{
	Level_ = GetParentEntity()->GetRootEntity()->GetComponentsByType<GaLevel>()[ 0 ];
	GetParentEntity()->SetLocalPosition( Level_->GetCentre() );

	SpriteSize_ = GetParentEntity()->GetComponentsByType<Bubblewrap::Render::Sprite>()[ 0 ]->GetSize();

	MoveDirection_ = Bubblewrap::Math::Vector2f(3000 - rand() % 6000, 1000 - rand() % 2000 ).Normalised();
	Paddles_ = GetParentEntity()->GetRootEntity()->GetComponentsByTypeAnyChild<GaPaddle>();
}

void GaPong::OnDetach()
{

}

GaPaddle* GaPong::CheckForCollisions()
{
	Bubblewrap::Math::Vector2f pos = GetParentEntity()->WorldPosition();
	float myX1 = pos.X() - SpriteSize_.X() * 0.5f;
	float myX2 = pos.X() + SpriteSize_.X() * 0.5f;
	float myY1 = pos.Y() - SpriteSize_.Y() * 0.5f;
	float myY2 = pos.Y() + SpriteSize_.Y() * 0.5f;

	for ( unsigned int Idx = 0; Idx < Paddles_.size(); ++Idx )
	{
		pos = Paddles_[ Idx ]->GetParentEntity()->WorldPosition();
		Bubblewrap::Math::Vector2f size = Paddles_[ Idx ]->GetSize();
		float othX1 = pos.X() - size.X() * 0.5f;
		float othX2 = pos.X() + size.X() * 0.5f;
		float othY1 = pos.Y() - size.Y() * 0.5f;
		float othY2 = pos.Y() + size.Y() * 0.5f;

		if ( ( myX1 < othX2 ) && ( myX2 > othX1 ) &&
			( myY1 < othY2 ) && ( myY2 > othY1 ) )
		{
			return Paddles_[ Idx ];
		}

	}
	return nullptr;
}