#include "GaPaddle.hpp"
#include "GaPong.hpp"
#include "GaTextController.hpp"
#include "GaLevel.hpp"
#include "Bubblewrap/Bubblewrap.hpp"
#include "Bubblewrap/Registers/BubblewrapRegister.hpp"
#include "Bubblewrap/Registers/SfmlRegisters.hpp"

int main()
{
	Bubblewrap::Math::Bounds1f test( 0.0f, 1.0f );
	Bubblewrap::Math::Bounds2f test1( 0.0f, 1.0f, 1.0f, 3.0f );
	Bubblewrap::Math::Bounds3f test2( 0.0f, 1.0f, 1.0f, 2.0f, -1.0f, 0.0f );
	Bubblewrap::Render::Colour Colour("255 255 255 128");
	Bubblewrap::Game::GameSettings settings;
	settings.WindowCount_ = 1;
	settings.WindowSettings_ = new Bubblewrap::Render::Window::WindowSettings[ 2 ];
	settings.WindowSettings_[ 0 ].Width_ = 800;
	settings.WindowSettings_[ 0 ].Height_ = 600;
	settings.WindowSettings_[ 0 ].Title_ = "POTATO";
	settings.WindowSettings_[ 0 ].Name_ = "Main";
	Bubblewrap::Logs::StaticLog::Instance()->SetLogLevel( Bubblewrap::Logs::StaticLog::VERBOSE );
	settings.Registers_.push_back( Bubblewrap::Registers::SfmlRegisters::RegisterUtilities );
	settings.Registers_.push_back( Bubblewrap::Registers::SfmlRegisters::RegisterGraphics );
	settings.Registers_.push_back( Bubblewrap::Registers::SfmlRegisters::RegisterAudio );
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