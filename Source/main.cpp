#include "Bubblewrap/Base/Game.hpp"
#include "Bubblewrap/Managers/Container.hpp"
#include "Bubblewrap/Render/Window.hpp"
#include "Bubblewrap/Render/Types.hpp"
#include "GaMovement.hpp"
#include "Bubblewrap/Events/Event.hpp"

#include "Bubblewrap/Registers/BubblewrapSfmlGraphicsRegister.hpp"
#include "Bubblewrap/Registers/BubblewrapSfmlSoundRegister.hpp"

int main()
{
	Bubblewrap::Render::Colour Colour("255 255 255 128");
	Bubblewrap::Game::GoGameSettings settings;
	settings.WindowCount_ = 1;
	settings.WindowSettings_ = new Bubblewrap::Render::Window::WindowSettings[ 2 ];
	settings.WindowSettings_[ 0 ].Width_ = 800;
	settings.WindowSettings_[ 0 ].Height_ = 600;
	settings.WindowSettings_[ 0 ].Title_ = "POTATO";
	settings.WindowSettings_[ 0 ].Name_ = "Main";
	settings.Registers_.push_back( Bubblewrap::Registers::SfmlGraphicsRegister::Register );
	settings.Registers_.push_back( Bubblewrap::Registers::SfmlSoundRegister::Register );
	settings.TypeRegistration_ = ( [ ]( Bubblewrap::Base::ObjectRegister* Register )
	{
		Register->RegisterCreator( "GaMovement", GaMovement::Create, GaMovement::CreateJson, GaMovement::CopyDef );
	} );
	settings.Packages_.push_back( "basics.json" );
	settings.BaseObject_ = "basics:GameEntity";
	Bubblewrap::Game::Game Game;
	Game.Run( settings );
}