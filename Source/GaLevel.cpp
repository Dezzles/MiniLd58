#include "GaLevel.hpp"
#include "Bubblewrap/Base/Entity.hpp"
#include "Bubblewrap/Events/EventKeyInput.hpp"
#include "Bubblewrap/Managers/Managers.hpp"
#include "Bubblewrap/Render/Sprite.hpp"
GaLevel::GaLevel()
{
}

void GaLevel::Initialise( Json::Value Params )
{
	DefaultBottom_ = Params[ "bottom" ].asFloat();
	DefaultRight_ = Params[ "right" ].asFloat();
	DefaultLeft_ = Params[ "left" ].asFloat();
	DefaultTop_ = Params[ "top" ].asFloat();
}

void GaLevel::Update( float dt )
{
	Bubblewrap::Math::Vector3f pos = GetParentEntity()->LocalPosition();

	float moveSpeed = 0.0f;

	GetParentEntity()->SetLocalPosition(pos);
}

void GaLevel::Copy( GaLevel* Target, GaLevel* Base )
{	
	Target->DefaultBottom_ = Base->DefaultBottom_;
	Target->DefaultLeft_ = Base->DefaultLeft_;
	Target->DefaultRight_ = Base->DefaultRight_;
	Target->DefaultTop_= Base->DefaultTop_;
}

void GaLevel::InputFunction( Bubblewrap::Events::Event* Event )
{
	Bubblewrap::Events::InputData data = *( Bubblewrap::Events::InputData* )Event->GetData();
	if ( ( data.Key_ == Bubblewrap::Events::Key::Space ) && ( data.InputType_ == Bubblewrap::Events::InputData::InputType::KeyUp ) )
	{
		LeftBounds_.ShrinkBounds( 50.0f );
		RegenerateGeometry();
	}
}

void GaLevel::RegenerateGeometry()
{
	if ( BorderRender_ == nullptr )
		return;
	BorderRender_->EditVertex( 0 ).Position_ = Bubblewrap::Math::Vector3f( DefaultLeft_, LeftBounds_.Lower(), 0.0f );

	BorderRender_->EditVertex( 1 ).Position_ = Bubblewrap::Math::Vector3f( DefaultRight_, RightBounds_.Lower(), 0.0f );
	BorderRender_->EditVertex( 2 ).Position_ = Bubblewrap::Math::Vector3f( DefaultRight_, RightBounds_.Upper(), 0.0f );

	BorderRender_->EditVertex( 3 ).Position_ = Bubblewrap::Math::Vector3f( DefaultLeft_, LeftBounds_.Upper(), 0.0f );
	BorderRender_->EditVertex( 4 ).Position_ = Bubblewrap::Math::Vector3f( DefaultLeft_, LeftBounds_.Lower(), 0.0f );

	BorderRender_->Refresh();
}


void GaLevel::OnAttach()
{
	LeftBounds_.SetBounds(DefaultTop_, DefaultBottom_);
	RightBounds_.SetBounds(DefaultTop_, DefaultBottom_);

	BorderRender_ = GetParentEntity()->GetComponentsByType<Bubblewrap::Render::Vertices>()[ 0 ];

/*	InputIdx_ = GetManager().GetEventManager().RegisterEvent( Bubblewrap::Events::EventTypes::Input,
		std::bind( &GaLevel::InputFunction, this, std::placeholders::_1 ) );/**/

}

void GaLevel::OnDetach()
{
//	GetManager().GetEventManager().DeregisterEvent(InputIdx_);
}

Bubblewrap::Math::Bounds1f GaLevel::GetBounds( float Position )
{
	float U = ( Position - DefaultLeft_ ) / ( DefaultRight_ - DefaultLeft_ );

	float MidLower = LeftBounds_.Lower() * ( 1.0f - U ) + RightBounds_.Lower() * U;
	float MidUpper = LeftBounds_.Upper() * ( 1.0f - U ) + RightBounds_.Upper() * U;

	return Bubblewrap::Math::Bounds1f(MidLower, MidUpper);
}

Bubblewrap::Math::Vector3f GaLevel::GetCentre()
{
	return Bubblewrap::Math::Vector3f( ( DefaultRight_ + DefaultLeft_ ) * 0.5f, ( DefaultBottom_ + DefaultTop_ ) * 0.5f, 0.0f );
}

Bubblewrap::Math::Bounds1f GaLevel::GetSideBounds()
{
	return Bubblewrap::Math::Bounds1f( DefaultLeft_, DefaultRight_ );
}
