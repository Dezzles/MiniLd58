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
}

void GaPong::Update( float dt )
{
	Bubblewrap::Math::Vector2f pos = GetParentEntity()->LocalPosition();

	pos = pos + MoveDirection_ * MovementSpeed_;

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
		MoveDirection_ = ( pos - Hit->GetParentEntity()->WorldPosition() ).Normalised();
		MovementSpeed_ *= 1.1f;
		pos = pos + 2.0f * MoveDirection_ * MovementSpeed_;
		printf("COLLISION DETECTED\n");
	}


	GetParentEntity()->SetLocalPosition(pos);
}

void GaPong::Copy( GaPong* Target, GaPong* Base )
{	
	Target->MovementSpeed_ = Base->MovementSpeed_;
}

void GaPong::InputFunction( Bubblewrap::Events::Event* Event )
{

}


void GaPong::OnAttach()
{
	Level_ = GetParentEntity()->GetRootEntity()->GetComponentsByType<GaLevel>()[ 0 ];
	GetParentEntity()->SetLocalPosition( Level_->GetCentre() );

	SpriteSize_ = GetParentEntity()->GetComponentsByType<Bubblewrap::Render::Sprite>()[ 0 ]->GetSize();

	MoveDirection_ = Bubblewrap::Math::Vector2f(1000 - rand() % 2000, 1000 - rand() % 2000 ).Normalised();
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