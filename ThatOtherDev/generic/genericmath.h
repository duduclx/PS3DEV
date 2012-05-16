#define PI					(3.14159265)
#define degreesinradian		(57.2957795)
#define radiansindegree		(0.0174532925)

int rounduptopowof2(int num){
	int powof2=2;
	while(powof2<num)powof2*=2;
	return powof2;
}

int lowint(int a,int b){
	if(a<b){return a;}else{return b;}
}

int highint(int a,int b){
	if(a>b){return a;}else{return b;}
}

float lowfloat(float a,float b){
	if(a<b){return a;}else{return b;}
}

float highfloat(float a,float b){
	if(a>b){return a;}else{return b;}
}

int posint(int num){
	if(num<0){return -num;}else{return num;}
}

float posfloat(float num){
	if(num<0){return -num;}else{return num;}
}

int negint(int num){
	if(num>0){return -num;}else{return num;}
}

float negfloat(float num){
	if(num>0){return -num;}else{return num;}
}

int inintrange(int num,int high,int low){
	if(num>high)num=high;
	if(num<low)num=low;
	return num;
}

float infloatrange(float num,float high,float low){
	if(num>high)num=high;
	if(num<low)num=low;
	return num;
}

#ifdef SDL
Uint8 in8bitrange(int num){
	if(num<=0) return 0;
	else if(num>=255) return 255;
	else return num;
}
#endif

#ifndef PS3
void movein2dspace(float &posx,float &posy,float ang,float speed){
	posx+=speed*cos(ang);
	posy+=speed*sin(ang);
}
#endif

#ifndef PS3
void movein3dspace(float &posx,float &posy,float &posz,float yang,float xang,float speed){
	posy+=speed*sin(xang);
	posx+=speed*cos(xang)*cos(yang);
	posz+=speed*cos(xang)*sin(yang);
}
#endif

#ifndef PS3
void rotatearoundxaxis(float &posx,float &posy,float &posz,float angle){
	float tempposy=posy,tempposz=posz;
	posy=tempposz*sin(angle)+tempposy*cos(angle);
	posz=tempposz*cos(angle)-tempposy*sin(angle);
}
#endif

#ifndef PS3
void rotatearoundyaxis(float &posx,float &posy,float &posz,float angle){
	float tempposx=posx,tempposz=posz;
	posx=tempposz*sin(angle)+tempposx*cos(angle);
	posz=tempposz*cos(angle)-tempposx*sin(angle);
}
#endif

#ifndef PS3
void rotatearoundzaxis(float &posx,float &posy,float &posz,float angle){
	float tempposx=posx,tempposy=posy;
	posx=tempposy*sin(angle)+tempposx*cos(angle);
	posy=tempposy*cos(angle)-tempposx*sin(angle);
}
#endif

float dist2d(float x,float y,float x2,float y2){
	x-=x2;
	y-=y2;
	return sqrt(x*x+y*y);
}

float dist3d(float x,float y,float z,float x2,float y2,float z2){
	x-=x2;
	y-=y2;
	z-=z2;
	return sqrt(x*x+y*y+z*z);
}

float mindist2d(float x,float y,float x2,float y2,float minimumdistance){
	if(x<x2+minimumdistance && y<y2+minimumdistance
	&& x>x2-minimumdistance && y>y2-minimumdistance){
		x-=x2;
		y-=y2;
		return sqrt(x*x+y*y);
	}else{
		return minimumdistance;
	}
}

float mindist3d(float x,float y,float z,float x2,float y2,float z2,float minimumdistance){
	if(x<x2+minimumdistance && y<y2+minimumdistance && z<z2+minimumdistance
	&& x>x2-minimumdistance && y>y2-minimumdistance && z>z2-minimumdistance){
		x-=x2;
		y-=y2;
		z-=z2;
		return sqrt(x*x+y*y+z*z);
	}else{
		return minimumdistance;
	}
}

float angledifference(float startangle,float endangle){
	while(startangle<endangle-180*radiansindegree)startangle+=360*radiansindegree;
	while(startangle>endangle+180*radiansindegree)startangle-=360*radiansindegree;
	return (endangle-startangle);
}

float turntoangle(float startangle,float endangle,float speed){
	return startangle+angledifference(startangle,endangle)*speed;
}

float randangle(){
	float angle=(float)(rand()%(360*100))*0.01f*radiansindegree;
	return angle;
}
