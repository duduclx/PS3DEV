//this was written by DigiBen
//http://www.gametutorials.com/

// This is our 3D point and vector class
struct CVector3{
public:
	//A default constructor
	CVector3() {}
	//This is our constructor that allows us to initialize our data upon creating an instance
	CVector3(float X, float Y, float Z) { 
		x = X; y = Y; z = Z;
	}
	//Here we overload the + operator so we can add vectors together 
	CVector3 operator+(CVector3 vVector){
		//Return the added vectors result.
		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}
	//Here we overload the - operator so we can subtract vectors 
	CVector3 operator-(CVector3 vVector){
		//Return the subtracted vectors result
		return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
	}
	//Here we overload the - operator so we can subtract vectors 
	CVector3 operator*(float num){
		//Return the subtracted vectors result
		return CVector3(x * num, y * num, z * num);
	}
	float x, y, z;						
};

/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns a perpendicular vector from 2 given vectors by taking the cross product.
/////
/////////////////////////////////////// CROSS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
CVector3 Cross(CVector3 vVector1, CVector3 vVector2){
	//The vector to hold the cross product
	CVector3 vNormal;
	//The X value for the vector is:  (V1.y * V2.z) - (V1.z * V2.y)
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
	//The Y value for the vector is:  (V1.z * V2.x) - (V1.x * V2.z)
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
	//The Z value for the vector is:  (V1.x * V2.y) - (V1.y * V2.x)
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));
	//Return the cross product (Direction the polygon is facing - Normal)
	return vNormal;
}

/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the magnitude of a normal (or any other vector)
/////
/////////////////////////////////////// MAGNITUDE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
float Magnitude(CVector3 vNormal){
	//This will give us the magnitude or "Norm" as some say, of our normal.
	//Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)  Where V is the vector
	return (float)sqrt( (vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z) );
}

/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns a normalize vector (A vector exactly of length 1)
/////
/////////////////////////////////////// NORMALIZE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
CVector3 Normalize(CVector3 vNormal){
	//Get the magnitude of our normal
	float magnitude = Magnitude(vNormal);
	//Now that we have the magnitude, we can divide our normal by that magnitude.
	//That will make our normal a total length of 1.  This makes it easier to work with too.
	vNormal.x /= magnitude;		//Divide the X value of our normal by it's magnitude
	vNormal.y /= magnitude;		//Divide the Y value of our normal by it's magnitude
	vNormal.z /= magnitude;		//Divide the Z value of our normal by it's magnitude
	//Finally, return our normalized normal.
	return vNormal;				//Return the new normal of length 1.
}

/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the normal of a polygon (The direction the polygon is facing)
/////
/////////////////////////////////////// NORMAL \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
CVector3 Normal(CVector3 vPolygon[]){					//Get 2 vectors from the polygon (2 sides), Remember the order!
	CVector3 vVector1 = vPolygon[2] - vPolygon[0];
	CVector3 vVector2 = vPolygon[1] - vPolygon[0];

	CVector3 vNormal = Cross(vVector1, vVector2);		//Take the cross product of our 2 vectors to get a perpendicular vector

	//Now we have a normal, but it's at a strange length, so let's make it length 1.

	vNormal = Normalize(vNormal);						//Use our function we created to normalize the normal (Makes it a length of one)

	return vNormal;										//Return our normal at our desired length
}

/////////////////////////////////// PLANE DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the distance between a plane and the origin
/////
/////////////////////////////////// PLANE DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
float PlaneDistance(CVector3 Normal, CVector3 Point){	
	float distance = 0;									//This variable holds the distance from the plane tot he origin

	//Use the plane equation to find the distance (Ax + By + Cz + D = 0)  We want to find D.
	//So, we come up with D = -(Ax + By + Cz)
														//Basically, the negated dot product of the normal of the plane and the point. (More about the dot product in another tutorial)
	distance = - ((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));

	return distance;									//Return the distance
}

/////////////////////////////////// INTERSECTED PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a line intersects a plane
/////
/////////////////////////////////// INTERSECTED PLANE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
bool IntersectedPlane(CVector3 vPoly[], CVector3 vLine[], CVector3 &vNormal, float &originDistance){
	float distance1=0, distance2=0;						//The distances from the 2 points of the line from the plane
			
	vNormal = Normal(vPoly);							//We need to get the normal of our plane to go any further

	//Let's find the distance our plane is from the origin.  We can find this value
	//from the normal to the plane (polygon) and any point that lies on that plane (Any vertex)
	originDistance = PlaneDistance(vNormal, vPoly[0]);

	//Get the distance from point1 from the plane using: Ax + By + Cz + D = (The distance from the plane)

	distance1 = ((vNormal.x * vLine[0].x)  +					// Ax +
		         (vNormal.y * vLine[0].y)  +					// Bx +
				 (vNormal.z * vLine[0].z)) + originDistance;	// Cz + D
	
	//Get the distance from point2 from the plane using Ax + By + Cz + D = (The distance from the plane)
	
	distance2 = ((vNormal.x * vLine[1].x)  +					// Ax +
		         (vNormal.y * vLine[1].y)  +					// Bx +
				 (vNormal.z * vLine[1].z)) + originDistance;	// Cz + D

	//Now that we have 2 distances from the plane, if we times them together we either
	//get a positive or negative number.  If it's a negative number, that means we collided!
	//This is because the 2 points must be on either side of the plane (IE. -1 * 1 = -1).

	if(distance1 * distance2 >= 0)			//Check to see if both point's distances are both negative or both positive
	   return false;						//Return false if each point has the same sign.  -1 and 1 would mean each point is on either side of the plane.  -1 -2 or 3 4 wouldn't...
					
	return true;							//The line intersected the plane, Return TRUE
}

/////////////////////////////////// DOT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This computers the dot product of 2 vectors
/////
/////////////////////////////////// DOT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
float Dot(CVector3 vVector1, CVector3 vVector2){
	//The dot product is this equation: V1.V2 = (V1.x * V2.x  +  V1.y * V2.y  +  V1.z * V2.z)
	//In math terms, it looks like this:  V1.V2 = ||V1|| ||V2|| cos(theta)
	
			 //    (V1.x * V2.x        +        V1.y * V2.y        +        V1.z * V2.z)
	return ( (vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z) );
}

/////////////////////////////////// ANGLE BETWEEN VECTORS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a point is inside the ranges of a polygon
/////
/////////////////////////////////// ANGLE BETWEEN VECTORS \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
double AngleBetweenVectors(CVector3 Vector1, CVector3 Vector2){							
	//Get the dot product of the vectors
	double dotProduct = Dot(Vector1, Vector2);				


	//Get the product of both of the vectors magnitudes
	double vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2) ;

	//Get the angle in radians between the 2 vectors
	double angle = acos( dotProduct / vectorsMagnitude );
	
	//Return the angle in radians
	return( angle );
}

/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the intersection point of the line that intersects the plane
/////
/////////////////////////////////// INTERSECTION POINT \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*								
CVector3 IntersectionPoint(CVector3 vNormal, CVector3 vLine[], double distance){
	CVector3 vPoint, vLineDir;					//Variables to hold the point and the line's direction
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	//1) First we need to get the vector of our line, Then normalize it so it's a length of 1
	vLineDir = vLine[1] - vLine[0];		//Get the Vector of the line
	vLineDir = Normalize(vLineDir);		//Normalize the lines vector


	//2) Use the plane equation (distance = Ax + By + Cz + D) to find the 
	//distance from one of our points to the plane.
	Numerator = - (vNormal.x * vLine[0].x +		//Use the plane equation with the normal and the line
				   vNormal.y * vLine[0].y +
				   vNormal.z * vLine[0].z + distance);

	//3) If we take the dot product between our line vector and the normal of the polygon,
	Denominator = Dot(vNormal, vLineDir);		//Get the dot product of the line's vector and the normal of the plane
				  
	//Since we are using division, we need to make sure we don't get a divide by zero error
	//If we do get a 0, that means that there are INFINATE points because the the line is
	//on the plane (the normal is perpendicular to the line - (Normal.Vector = 0)).  
	//In this case, we should just return any point on the line.

	if( Denominator == 0.0)						//Check so we don't divide by zero
		return vLine[0];						//Return an arbitrary point on the line

	dist = Numerator / Denominator;				//Divide to get the multiplying (percentage) factor
	
	//Now, like we said above, we times the dist by the vector, then add our arbitrary point.
	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;								//Return the intersection point
}

/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This checks to see if a point is inside the ranges of a polygon
/////
/////////////////////////////////// INSIDE POLYGON \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
bool InsidePolygon(CVector3 vIntersection, CVector3 Poly[], long verticeCount){
	const double MATCH_FACTOR = 0.99;		//Used to cover up the error in floating point
	double Angle = 0.0;						//Initialize the angle
	CVector3 vA, vB;						//Create temp vectors
	
	for (int i = 0; i < verticeCount; i++)		//Go in a circle to each vertex and get the angle between
	{	
		vA = Poly[i] - vIntersection;			//Subtract the intersection point from the current vertex
												//Subtract the point from the next vertex
		vB = Poly[(i + 1) % verticeCount] - vIntersection;
												
		Angle += AngleBetweenVectors(vA, vB);	//Find the angle between the 2 vectors and add them all up as we go along
	}
											
	if(Angle >= (MATCH_FACTOR * (2.0 * PI)) )	//If the angle is greater than 2 PI, (360 degrees)
		return true;							//The point is inside of the polygon
		
	return false;								//If you get here, it obviously wasn't inside the polygon, so Return FALSE
}

/////////////////////////////////// DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the distance between 2 3D points
/////
/////////////////////////////////// DISTANCE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
float Distance(CVector3 vPoint1, CVector3 vPoint2){
	//This is the classic formula used in beginning algebra to return the
	//distance between 2 points.  Since it's 3D, we just add the z dimension:
	// 
	//Distance = sqrt(  (P2.x - P1.x)^2 + (P2.y - P1.y)^2 + (P2.z - P1.z)^2 )
	//
	double distance = sqrt( (vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
						    (vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
						    (vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z) );

	//Return the distance between the 2 points
	return (float)distance;
}

////////////////////////////// CLOSEST POINT ON LINE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
/////
/////	This returns the point on the line vA_vB that is closest to the point vPoint
/////
////////////////////////////// CLOSEST POINT ON LINE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*
CVector3 ClosestPointOnLine(CVector3 vA, CVector3 vB, CVector3 vPoint){
	//Create the vector from end point vA to our point vPoint.
	CVector3 vVector1 = vPoint - vA;
	//Create a normalized direction vector from end point vA to end point vB
	CVector3 vVector2 = Normalize(vB - vA);
	//Use the distance formula to find the distance of the line segment (or magnitude)
	float d = Distance(vA, vB);
	//Using the dot product, we project the vVector1 onto the vector vVector2.
	//This essentially gives us the distance from our projected vector from vA.
	float t = Dot(vVector2, vVector1);
	//If our projected distance from vA, "t", is less than or equal to 0, it must
	//be closest to the end point vA.  We want to return this end point.
	if(t <= 0)return vA;
	//If our projected distance from vA, "t", is greater than or equal to the magnitude
	//or distance of the line segment, it must be closest to the end point vB.  So, return vB.
	if(t >= d)return vB;
	//Here we create a vector that is of length t and in the direction of vVector2
    CVector3 vVector3 = vVector2 * t;
	//To find the closest point on the line segment, we just add vVector3 to the original
	//end point vA.  
	CVector3 vClosestPoint = vA + vVector3;
	//Return the closest point on the line segment
	return vClosestPoint;
}
