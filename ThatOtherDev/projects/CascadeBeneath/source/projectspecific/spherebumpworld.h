//void spherebumpworld(float &posx,float &posy,float radius){

void spherebumpworld(){

	float posx=youx;
	float posy=youy;
	float radius=yousize;

	float dist,impactx,impacty;

	for(int a=0; a<wallcount; a++)
	if(posx+radius>walllist[a].x && posx-radius<walllist[a].x+walllist[a].w
	&& posy+radius>walllist[a].y && posy-radius<walllist[a].y+walllist[a].h){
		if(posx>walllist[a].x+walllist[a].w){
			impactx=walllist[a].x+walllist[a].w;
		}else if(posx<walllist[a].x){
			impactx=walllist[a].x;
		}else{
			impactx=posx;
		}
		if(posy>walllist[a].y+walllist[a].h){
			impacty=walllist[a].y+walllist[a].h;
		}else if(posy<walllist[a].y){
			impacty=walllist[a].y;
		}else{
			impacty=posy;
		}
		dist=dist2d(posx,posy,impactx,impacty);
		if(dist<radius){
			float percentx=(posx-impactx)/dist;
			float percenty=(posy-impacty)/dist;
			posx=impactx+percentx*radius;
			posy=impacty+percenty*radius;
		}
	}

	if(posx<radius-1+0.1)posx=radius-1+0.1;
	if(posx>1-radius-0.1)posx=1-radius-0.1;
	if(posy<radius-1+0.1)posy=radius-1+0.1;

	youx=posx;
	youy=posy;

}
