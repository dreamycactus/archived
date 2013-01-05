Game Components Library

Instruction
-----------
Need to compile the latest build of SDL-1.3 (and SDL_image) from the SDL Mercurial Repo

Linker options:
-lmingw32 (for windows) -lSDL2main -lSDL2 -lopengl32 -lSDL2_image
HI!

Currently an older version of SDL image is used because I can't get sdl2_image to support pngs for some reason.


GAME COMPONENTS

Progress so far
---------------
CORE
{
	iApplication
	cGame
}
STATE
{
	cGameStateManager
	cGameTransition
	iGameState
}

Misc:
	cGenericFactory
	
Next Steps:
	Maths
	Sprites, Alpha, & Sprite Batch
	Animation
	Shaders?

	
	
	
Main Components:
Application
Containers
Maths
Text Processing
Graphics
Collision
Resources
Physics
Networking
Audio
Input




Containers:
Tree class?

Maths:
Vectors
Matricies
Plane
Polygon
Quaternion
Interpolators
Integrators
Geometry

Graphics:
Scene/Model/Renderer?
Primitives
Cameras
Texture
Image
Graphics2D:
	sprite
	animation
	texture atlas
	sprite batch
	tiles
	
