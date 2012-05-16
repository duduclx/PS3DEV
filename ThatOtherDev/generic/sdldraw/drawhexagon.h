void drawhexagon(SDL_Surface *dest,int x,int y,int sides,float radius,float angle,Uint32 color){
	//int *verts = new int[sides+10];
	int verts[100];
	verts[0]=x;
	verts[1]=y;
	int i=2;
	for(float a=0.f; a<=360.f*radiansindegree; a+=360.f*radiansindegree/(float)sides){
		verts[i]=x+(int)(cos(a+angle)*radius);i++;
		verts[i]=y+(int)(sin(a+angle)*radius);i++;
	}
	verts[i]=verts[2];i++;
	verts[i]=verts[3];i++;
	for(int a=0;a<sides;a++){
		drawpolygon(dest,
			verts[0],verts[1],
			verts[a*2+2],verts[a*2+3],
			verts[a*2+4],verts[a*2+5],
			color);
		//it doesnt seem to always work without this second draw...
		drawpolygon(dest,
			verts[0],verts[1],
			verts[a*2+4],verts[a*2+5],
			verts[a*2+2],verts[a*2+3],
			color);
	}
	//delete verts;
}
