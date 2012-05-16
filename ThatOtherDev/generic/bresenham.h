#ifndef PS3
signed char Bresenhamix;
signed char Bresenhamiy;
int Bresenhamdelta_x;
int Bresenhamdelta_y;
int Bresenhamerror;
	
void BresenhamStart(int &x1,int &y1,int x2,int y2){
	Bresenhamdelta_x = (x2 > x1?(Bresenhamix = 1, x2 - x1):(Bresenhamix = -1, x1 - x2)) << 1;
	Bresenhamdelta_y = (y2 > y1?(Bresenhamiy = 1, y2 - y1):(Bresenhamiy = -1, y1 - y2)) << 1;
	if(Bresenhamdelta_x >= Bresenhamdelta_y){
		Bresenhamerror = Bresenhamdelta_y - (Bresenhamdelta_x >> 1);
	}else{
		Bresenhamerror = Bresenhamdelta_x - (Bresenhamdelta_y >> 1);
	}
}

bool Bresenham(int &x1,int &y1,int &x2,int &y2){
	bool incomplete=0;
	if(Bresenhamdelta_x >= Bresenhamdelta_y){
		if(x1 != x2){
			if(Bresenhamerror >= 0){
				if(Bresenhamerror || (Bresenhamix > 0)){
					y1 += Bresenhamiy;
					Bresenhamerror -= Bresenhamdelta_x;
				}
			}
			x1 += Bresenhamix;
			Bresenhamerror += Bresenhamdelta_y;
			incomplete=1;
		}
	}else{
		if(y1 != y2){
			if(Bresenhamerror >= 0){
				if(Bresenhamerror || (Bresenhamiy > 0)){
					x1 += Bresenhamix;
					Bresenhamerror -= Bresenhamdelta_y;
				}
			}
			y1 += Bresenhamiy;
			Bresenhamerror += Bresenhamdelta_x;
			incomplete=1;
		}
	}
	return incomplete;
}
#endif
