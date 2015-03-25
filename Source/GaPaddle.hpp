#ifndef GAPADDLE_HPP
#define GAPADDLE_HPP

#include "Bubblewrap/Base/Defines.hpp"
#include "Bubblewrap/Base/Component.hpp"
#include "Bubblewrap/Base/Base.hpp"
#include "Bubblewrap/Math/Vector2.hpp"
#include "Bubblewrap/Events/Events.hpp"

class GaPaddle : public Bubblewrap::Base::Component
{ 
public:
	GaPaddle();
	void Initialise( Json::Value Params );

	void Update( float dt );
	CREATE_REGISTER( GaPaddle );

	virtual void OnAttach();
	virtual void OnDetach();
	void InputFunction( Bubblewrap::Events::Event* Event );

	Bubblewrap::Math::Vector2f GetSize();
private:
	bool IsPlayer_;
	unsigned int InputIdx_;

	bool UpKeyDown_;
	bool DownKeyDown_;
	float MovementSpeed_;

	float MinLocation_;
	float MaxLocation_;
	float XPosition_;

	Bubblewrap::Math::Vector2f SpriteSize_;
};


#endif