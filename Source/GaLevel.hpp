#ifndef GALEVEL_HPP
#define GALEVEL_HPP

#include "Bubblewrap/Base/Defines.hpp"
#include "Bubblewrap/Base/Component.hpp"
#include "Bubblewrap/Base/Base.hpp"
#include "Bubblewrap/Math/Vector2.hpp"
#include "Bubblewrap/Events/Events.hpp"
#include "Bubblewrap/Math/Bounds1.hpp"
#include "Bubblewrap/Render/Vertices.hpp"

class GaLevel : public Bubblewrap::Base::Component
{ 
public:
	GaLevel();
	void Initialise( Json::Value Params );

	void Update( float dt );
	CREATE_REGISTER( GaLevel );

	virtual void OnAttach();
	virtual void OnDetach();
	void InputFunction( Bubblewrap::Events::Event* Event );
	Bubblewrap::Math::Bounds1f GetBounds( float Position );
	Bubblewrap::Math::Bounds1f GetSideBounds( );
	Bubblewrap::Math::Vector2f GetCentre();
private:

	float DefaultLeft_;
	float DefaultRight_;
	float DefaultTop_;
	float DefaultBottom_;

	Bubblewrap::Math::Bounds1f LeftBounds_;
	Bubblewrap::Math::Bounds1f RightBounds_;

	Bubblewrap::Render::Vertices* BorderRender_;

	unsigned int InputIdx_;

	void RegenerateGeometry();

};


#endif