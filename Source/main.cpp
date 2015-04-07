#include "Bubblewrap/Base/Game.hpp"
#include "Bubblewrap/Managers/Container.hpp"
#include "Bubblewrap/Render/Window.hpp"
#include "Bubblewrap/Render/Types.hpp"
#include "GaPaddle.hpp"
#include "GaPong.hpp"
#include "GaTextController.hpp"
#include "GaLevel.hpp"
#include "Bubblewrap/Events/Event.hpp"

#include "Bubblewrap/Registers/BubblewrapSfmlGraphicsRegister.hpp"
#include "Bubblewrap/Registers/BubblewrapSfmlSoundRegister.hpp"
#include "Bubblewrap/Math/Bounds1.hpp"
#include "Bubblewrap/Math/Bounds2.hpp"
#include "Bubblewrap/Math/Bounds3.hpp"
int main()
{
	Bubblewrap::Math::Bounds1f test( 0.0f, 1.0f );
	Bubblewrap::Math::Bounds2f test1( 0.0f, 1.0f, 1.0f, 3.0f );
	Bubblewrap::Math::Bounds3f test2( 0.0f, 1.0f, 1.0f, 2.0f, -1.0f, 0.0f );
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
	settings.Resources_.push_back( "textures" );
	settings.TypeRegistration_ = ( [ ]( Bubblewrap::Base::ObjectRegister* Register )
	{
		Register->RegisterCreator( "GaPaddle", GaPaddle::Create, GaPaddle::CopyDef );
		Register->RegisterCreator( "GaPong", GaPong::Create, GaPong::CopyDef );
		Register->RegisterCreator( "GaLevel", GaLevel::Create, GaLevel::CopyDef );
		Register->RegisterCreator( "GaTextController", GaTextController::Create, GaTextController::CopyDef );
	} );
	settings.Packages_.push_back( "basics.json" );
	settings.BaseObject_ = "basics:LevelEntity";
	Bubblewrap::Game::Game Game;
	Game.Run( settings );
}