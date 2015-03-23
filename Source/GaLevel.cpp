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

}

void GaLevel::Update( float dt )
{
	Bubblewrap::Math::Vector2f pos = GetParentEntity()->LocalPosition();

	float moveSpeed = 0.0f;

	GetParentEntity()->SetLocalPosition(pos);
}

void GaLevel::Copy( GaLevel* Target, GaLevel* Base )
{	

}

void GaLevel::InputFunction( Bubblewrap::Events::Event* Event )
{

}


void GaLevel::OnAttach()
{

}

void GaLevel::OnDetach()
{

}