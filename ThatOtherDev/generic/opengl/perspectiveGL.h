//http://nehe.gamedev.net/data/articles/article.asp?article=11
//alternative to gluPerspective

/*
	Replaces gluPerspective. Sets the frustum to perspective mode.
	fovY	- Field of vision in degrees in the y direction
	aspect	- Aspect ratio of the viewport
	zNear	- The near clipping distance
	zFar	- The far clipping distance
*/

void perspectiveGL( double fovY, double aspect, double zNear, double zFar )
{
	//	Very long (& in theory accurate!) version of Pi. Hopefully an optimizing compiler
	//	will replace references to this with the value!
	const double pi = 3.1415926535897932384626433832795;

	//	Half of the size of the x and y clipping planes.
	double fW, fH;

	//	Calculate the distance from 0 of the y clipping plane. Basically trig to calculate
	//	position of clipper at zNear.

	//	Note:	tan( double ) uses radians but OpenGL works in degrees so we convert
	//			degrees to radians by dividing by 360 then multiplying by pi.
	fH = tan( (fovY / 2) / 180 * pi ) * zNear;	
	// Same as fH = tan( fovY / 360 * pi ) * zNear;
	
	//	Calculate the distance from 0 of the x clipping plane based on the aspect ratio.
	fW = fH * aspect;

	//	Finally call glFrustum, this is all gluPerspective does anyway!
	//	This is why we calculate half the distance between the clipping planes - glFrustum
	//	takes an offset from zero for each clipping planes distance. (Saves 2 divides)
	glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}
