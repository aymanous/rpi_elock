#include "utils.h"

int main (void)
{
	init();
	void thrdMode(){
		for(;;){
			int temp = getCurrentMode();
			if(temp != mode){
				mode = temp;
				switch(mode){
					case 1:
						printf("\n[AJOUT] - VEUILLEZ PRESENTER VOTRE BADGE !\n");
						strcpy(modeApiRoute,ADD_ROUTE);
						break;
		
					case 2:			
						printf("\n[SUPPRESSION] - VEUILLEZ PRESENTER VOTRE BADGE !\n");
						strcpy(modeApiRoute,DELETE_ROUTE);
						break;
		
					default:
						printf("\n[DEVEROUILLAGE] - VEUILLEZ PRESENTER VOTRE BADGE !\n");
						strcpy(modeApiRoute,STATUS_ROUTE);
				}
			}
			 
		}		
	}	

	void thrdMain(){
		for(;;){
			manageBadge();
		}	
	}	


	pthread_t thrd_mode;
	pthread_t thrd_main;

	pthread_create(&thrd_mode,NULL,(void*)thrdMain,NULL);
	pthread_create(&thrd_mode,NULL,(void*)thrdMode,NULL);


	pthread_join(thrd_main,NULL);
	pthread_join(thrd_mode,NULL);

	curl_global_cleanup();

  	return 0 ;
}
