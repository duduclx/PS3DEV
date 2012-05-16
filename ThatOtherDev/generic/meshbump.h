//calculate the normal from a triangle polygon
void calculatetrianglenormal(
	float vx0, float vy0, float vz0,
	float vx1, float vy1, float vz1,
	float vx2, float vy2, float vz2,
	float &nx, float &ny, float &nz){
		//subtract vectors
		float ax=vx1-vx0;
		float ay=vy1-vy0;
		float az=vz1-vz0;
		float bx=vx2-vx1;
		float by=vy2-vy1;
		float bz=vz2-vz1;
		//calculate face normal using cross product
		nx=ay*bz-az*by;
		ny=az*bx-ax*bz;
		nz=ax*by-ay*bx;
		//normalize it 
		float l=sqrt(nx*nx+ny*ny+nz*nz);
		nx=-nx/l;
		ny=-ny/l;
		nz=-nz/l;
}

//struct info for a collision mesh
typedef struct polygoncollisionmesh{
	int polygoncount;
	CVector3 *polygonvertex1;
	CVector3 *polygonvertex2;
	CVector3 *polygonvertex3;
	CVector3 *polygonnormal;
}polygoncollisionmesh;

//generate the collision mesh for triangle polygons
polygoncollisionmesh* maketrianglepolygoncollisionmesh(
	int vertexcount,float *vertexarray,polygoncollisionmesh *oldmesh){
	polygoncollisionmesh *newmesh = NULL;
	if(oldmesh!=NULL){
		newmesh=oldmesh;
	}else{
		newmesh=new polygoncollisionmesh;
	}
	int polygoncount=vertexcount/3;
	if(oldmesh==NULL || oldmesh->polygoncount != polygoncount){
		if(oldmesh!=NULL){
			free(oldmesh->polygonvertex1);
			free(oldmesh->polygonvertex2);
			free(oldmesh->polygonvertex3);
			free(oldmesh->polygonnormal);
		}
		newmesh->polygoncount = polygoncount;
		newmesh->polygonvertex1=(CVector3*)malloc(newmesh->polygoncount*sizeof(CVector3));
		newmesh->polygonvertex2=(CVector3*)malloc(newmesh->polygoncount*sizeof(CVector3));
		newmesh->polygonvertex3=(CVector3*)malloc(newmesh->polygoncount*sizeof(CVector3));
		newmesh->polygonnormal=(CVector3*)malloc(newmesh->polygoncount*sizeof(CVector3));
	}
	for(int a=0; a<newmesh->polygoncount; a++){
		newmesh->polygonvertex1[a].x=vertexarray[a*9+0];
		newmesh->polygonvertex1[a].y=vertexarray[a*9+1];
		newmesh->polygonvertex1[a].z=vertexarray[a*9+2];
		newmesh->polygonvertex2[a].x=vertexarray[a*9+3];
		newmesh->polygonvertex2[a].y=vertexarray[a*9+4];
		newmesh->polygonvertex2[a].z=vertexarray[a*9+5];
		newmesh->polygonvertex3[a].x=vertexarray[a*9+6];
		newmesh->polygonvertex3[a].y=vertexarray[a*9+7];
		newmesh->polygonvertex3[a].z=vertexarray[a*9+8];
		calculatetrianglenormal(
			newmesh->polygonvertex1[a].x,newmesh->polygonvertex1[a].y,newmesh->polygonvertex1[a].z,
			newmesh->polygonvertex2[a].x,newmesh->polygonvertex2[a].y,newmesh->polygonvertex2[a].z,
			newmesh->polygonvertex3[a].x,newmesh->polygonvertex3[a].y,newmesh->polygonvertex3[a].z,
			newmesh->polygonnormal[a].x,newmesh->polygonnormal[a].y,newmesh->polygonnormal[a].z);
	}
	return newmesh;
}

//generate the collision mesh for quad polygons
polygoncollisionmesh* makequadpolygoncollisionmesh(
	int vertexcount,float *vertexarray,polygoncollisionmesh *oldmesh){
	polygoncollisionmesh *newmesh = NULL;
	if(oldmesh!=NULL){
		newmesh=oldmesh;
	}else{
		newmesh=new polygoncollisionmesh;
	}
	int polygoncount=vertexcount/4*2;
	if(oldmesh==NULL || oldmesh->polygoncount != polygoncount){
		if(oldmesh!=NULL){
			free(oldmesh->polygonvertex1);
			free(oldmesh->polygonvertex2);
			free(oldmesh->polygonvertex3);
			free(oldmesh->polygonnormal);
		}
		newmesh->polygoncount = polygoncount;
		newmesh->polygonvertex1=(CVector3*)malloc(newmesh->polygoncount*sizeof(CVector3));
		newmesh->polygonvertex2=(CVector3*)malloc(newmesh->polygoncount*sizeof(CVector3));
		newmesh->polygonvertex3=(CVector3*)malloc(newmesh->polygoncount*sizeof(CVector3));
		newmesh->polygonnormal=(CVector3*)malloc(newmesh->polygoncount*sizeof(CVector3));
	}
	for(int a=0; a<newmesh->polygoncount; a++){
		if(a-(int)floor((float)a*0.5f)*2==0){
			newmesh->polygonvertex1[a].x=vertexarray[a*6+0];
			newmesh->polygonvertex1[a].y=vertexarray[a*6+1];
			newmesh->polygonvertex1[a].z=vertexarray[a*6+2];
			newmesh->polygonvertex2[a].x=vertexarray[a*6+3];
			newmesh->polygonvertex2[a].y=vertexarray[a*6+4];
			newmesh->polygonvertex2[a].z=vertexarray[a*6+5];
			newmesh->polygonvertex3[a].x=vertexarray[a*6+6];
			newmesh->polygonvertex3[a].y=vertexarray[a*6+7];
			newmesh->polygonvertex3[a].z=vertexarray[a*6+8];
		}else{
			newmesh->polygonvertex1[a].x=vertexarray[a*6-6+9];
			newmesh->polygonvertex1[a].y=vertexarray[a*6-6+10];
			newmesh->polygonvertex1[a].z=vertexarray[a*6-6+11];
			newmesh->polygonvertex2[a].x=vertexarray[a*6-6+0];
			newmesh->polygonvertex2[a].y=vertexarray[a*6-6+1];
			newmesh->polygonvertex2[a].z=vertexarray[a*6-6+2];
			newmesh->polygonvertex3[a].x=vertexarray[a*6-6+6];
			newmesh->polygonvertex3[a].y=vertexarray[a*6-6+7];
			newmesh->polygonvertex3[a].z=vertexarray[a*6-6+8];
		}
		calculatetrianglenormal(
			newmesh->polygonvertex1[a].x,newmesh->polygonvertex1[a].y,newmesh->polygonvertex1[a].z,
			newmesh->polygonvertex2[a].x,newmesh->polygonvertex2[a].y,newmesh->polygonvertex2[a].z,
			newmesh->polygonvertex3[a].x,newmesh->polygonvertex3[a].y,newmesh->polygonvertex3[a].z,
			newmesh->polygonnormal[a].x,newmesh->polygonnormal[a].y,newmesh->polygonnormal[a].z);
	}
	return newmesh;
}

//sphere bumps into collision mesh
bool spherebumppolygoncollisionmesh(
	float &sphereposx,float &sphereposy,float &sphereposz,float radius,
	polygoncollisionmesh* mesh,bool hitifinside,bool hitifonedge){

	bool bumped=0;

	//reusable variables
	CVector3 g_vPosition;
	CVector3 g_vTriangle[3];
	CVector3 vNormal;
	float distance = 0.0f;
	//get track of the spheres position
	g_vPosition = CVector3(sphereposx,sphereposy,sphereposz);
	//check each polygon
	for(int a=0; a<mesh->polygoncount; a++){
		//get the polygon info
		g_vTriangle[0]=mesh->polygonvertex1[a];
		g_vTriangle[1]=mesh->polygonvertex2[a];
		g_vTriangle[2]=mesh->polygonvertex3[a];
		vNormal=mesh->polygonnormal[a];
		//distance from the sphere to the polygons plane
		distance=
			vNormal.x*(g_vPosition.x-g_vTriangle[0].x)+
			vNormal.y*(g_vPosition.y-g_vTriangle[0].y)+
			vNormal.z*(g_vPosition.z-g_vTriangle[0].z);
		//check if the sphere is in front and in range of the polygon
		if(distance<=0.f && -distance<radius){
			CVector3 vOffset = vNormal * distance;
			CVector3 vPosition = g_vPosition - vOffset;
			if(InsidePolygon(vPosition,g_vTriangle,3)){
				if(hitifinside){
					sphereposx-=vNormal.x*(radius+distance);
					sphereposy-=vNormal.y*(radius+distance);
					sphereposz-=vNormal.z*(radius+distance);
					g_vPosition = CVector3(sphereposx,sphereposy,sphereposz);
					bumped=1;
				}
			}else{
				if(hitifonedge){
					CVector3 vPoint;
					for(int i = 0; i < 3; i++){
						vPoint = ClosestPointOnLine(g_vTriangle[i],g_vTriangle[(i+1)%3],g_vPosition);
						distance = Distance(vPoint,g_vPosition);
						if(distance < radius){
							//float speed=1.f/distance*radius;
							float speed=radius/distance;
							sphereposx=vPoint.x+(g_vPosition.x-vPoint.x)*speed;
							sphereposy=vPoint.y+(g_vPosition.y-vPoint.y)*speed;
							sphereposz=vPoint.z+(g_vPosition.z-vPoint.z)*speed;
							g_vPosition = CVector3(sphereposx,sphereposy,sphereposz);
							bumped=1;
						}
					}
				}
			}
		}
	}

	return bumped;

}

//line bumps into collision mesh
bool linebumppolygoncollisionmesh(
	float x1,float y1,float z1,float &x2,float &y2,float &z2,
	polygoncollisionmesh* mesh){

	bool bumped=0;

	CVector3 vLine[2];
	vLine[0].x=x1;
	vLine[0].y=y1;
	vLine[0].z=z1;
	vLine[1].x=x2;
	vLine[1].y=y2;
	vLine[1].z=z2;

	CVector3 vTriangle[3];
	CVector3 vNormal;

	float originDistance = 0.f;

	for(int a=0; a<mesh->polygoncount; a++){
		vTriangle[0]=mesh->polygonvertex1[a];
		vTriangle[1]=mesh->polygonvertex2[a];
		vTriangle[2]=mesh->polygonvertex3[a];
		// First, make sure our line intersects the plane
		if(IntersectedPlane(vTriangle,vLine,vNormal,originDistance)){
			// Now that we have our normal and distance passed back from IntersectedPlane(), 
			// we can use it to calculate the intersection point.  
			CVector3 vIntersection = IntersectionPoint(vNormal,vLine,originDistance);
			// Now that we have the intersection point, we need to test if it's inside the polygon.
			if(InsidePolygon(vIntersection,vTriangle,3)){
				x2=vIntersection.x;
				y2=vIntersection.y;
				z2=vIntersection.z;
				vLine[1].x=x2;
				vLine[1].y=y2;
				vLine[1].z=z2;
				bumped=1;
			}
		}

	}

	return bumped;

}
