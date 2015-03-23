SFML2DIR = "D:/Projects/Libraries/SFML-2.2"
additionalIncludes = {}
additionalLibraries = {}

dofile ( "bubblewrap/Scripts/Bubblewrap_Scripts.lua" )

solution "BubbleWrap"
	configurations { "Debug", "Release" }
	location "build"


-- Build externals.
dofile ("bubblewrap/External/genie.lua")

loadLibrary( "bubblewrap_sfml" )

-- Build engine.
dofile ("bubblewrap/bubblewrap_genie.lua")

-- Build game source.
dofile ("./Source/genie.lua")

