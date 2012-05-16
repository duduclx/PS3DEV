struct tm *dash_time;
const char* dash_wday[]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
const char* dash_month[]={"January","February","March","April","May","June","July","August","September","October","November","December"};
const char* dash_day[]={"1st","2nd","3rd","4th","5th","6th","7th","8th","9th","10th","11th","12th","13th","14th","15th","16th","17th","18th","19th","20th","21st","22nd","23rd","24th","25th","26th","27th","28th","29th","30th","31st"};
char dash_composedtext_date[256];
char dash_composedtext_time[256];

int dash_gametime=0;
int dash_timehaspast=0;
float dash_framerate=0;
float dash_framecap=60;

void setupdashtime(){
}

void dashtime(){

	//get how much time has passed
	#ifdef SDL
	dash_timehaspast=SDL_GetTicks()-dash_gametime;
	#else
		#ifdef WIN
		dash_timehaspast=GetTickCount()-dash_gametime;
		#else
			#ifdef WII
			//http://forum.wiibrew.org/read.php?11,66351
			//Uint64 ticks = gettime();
			//Uint64 ms = ticks / TB_TIMER_CLOCK;
			int ticks = gettime();
			int ms = ticks / TB_TIMER_CLOCK;
			dash_timehaspast = ms - dash_gametime;
			#else
				//#ifdef PS3
				//dash_timehaspast = (int)(sys_time_get_system_time()/1000) - dash_gametime;
				//#else
				//???
				dash_timehaspast=1;
				//dash_timehaspast = (int)(clock()/CLOCKS_PER_SEC*1000) - dash_gametime;
				//#endif
			#endif
		#endif
	#endif

	//throttle the frame rate
	if(dash_framecap){
		#ifdef SDL
		if(dash_timehaspast<(int)(1000.f/dash_framecap)){
			int delay=(int)(1000.f/dash_framecap)-dash_timehaspast;
			SDL_Delay(delay);
			dash_timehaspast+=delay;
		}
		#endif
	}

	//calculate the new time
	dash_gametime+=dash_timehaspast;

	//calculate the frame rate
	dash_framerate=1000.f/(float)dash_timehaspast;

	//get the time and date
	time_t now;
	now = time(NULL);
	dash_time = localtime(&now);

	//get the date in a char array text format
	sprintf(dash_composedtext_date,"%s%s%s%s%s%s%d",
			dash_wday[dash_time->tm_wday],
			" ",
			dash_month[dash_time->tm_mon],
			" ",
			dash_day[dash_time->tm_mday-1],
			" ",
			1900+dash_time->tm_year
			);

	//get the time in a char array text format
	strcpy(dash_composedtext_time,"");
	if(dash_time->tm_hour>12){
		sprintf(dash_composedtext_time,"%s%d",dash_composedtext_time,dash_time->tm_hour-12);
	}else{
		if(dash_time->tm_hour==0){
			sprintf(dash_composedtext_time,"%s%d",dash_composedtext_time,12);
		}else{
			sprintf(dash_composedtext_time,"%s%d",dash_composedtext_time,dash_time->tm_hour);
		}
	}
	strcat(dash_composedtext_time,":");
	if(dash_time->tm_min<10)
		strcat(dash_composedtext_time,"0");
	sprintf(dash_composedtext_time,"%s%d",dash_composedtext_time,dash_time->tm_min);
	strcat(dash_composedtext_time,":");
	if(dash_time->tm_sec<10)
		strcat(dash_composedtext_time,"0");
	sprintf(dash_composedtext_time,"%s%d",dash_composedtext_time,dash_time->tm_sec);
	if(dash_time->tm_hour>11){
		strcat(dash_composedtext_time," PM");
	}else{
		strcat(dash_composedtext_time," AM");
	}

}
