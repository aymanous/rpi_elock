#include "utils.h"

void init(){
  	//PARAMETRAGE DES PINS GPIO
	wiringPiSetup();
  	pinMode(GACHE, OUTPUT);
	pinMode(LED, OUTPUT);

	//INITIALISATION LED + GACHE
	digitalWrite (LED, LOW) ;	// Off  
	digitalWrite (GACHE, LOW) ;	// Off
}

void manageBadge(){

	//APPEL DU PORGRAMME DE LECTURE DE BADGE EN PYTHON
	system("python libs/Read.py");
	readRFID();

	//PREPARATION DE L'URL A INTERROGER
	strcpy(URL,BASE_URL);
	strcat(URL,modeApiRoute);


	//REQUETE VERS L'API POUR VERIFIER LE CODE DU BADGE PRESENTE
	strcat(URL, badgeCode);

	long res = makeRequest(URL);

	//GESTION DES COMPORTEMENTS DE LA LED ET GACHE
	switch(getCurrentMode()){
		case 1:
			addBehaviour(res);
			break;
		
		case 2:			
			deleteBehaviour(res);
			break;
		
		default:
			readBehaviour(res);
	}
}

void addBehaviour(int res){
	if(res == 200){
		printf("Badge ajouté avec succès !\n\n\n");
	    	digitalWrite (LED, HIGH) ;	// On
	    	delay (1000);			// mS
	    	digitalWrite (LED, LOW) ;	// Off	
	} else {	
		printf("Badge déjà existant !\n\n");
		digitalWrite (LED, HIGH) ;	// On
	    	delay (500);			// mS
	    	digitalWrite (LED, LOW) ;	// Off
		delay (500);
		digitalWrite (LED, HIGH) ;	// On
	    	delay (500);			// mS
	    	digitalWrite (LED, LOW) ;	// Off  
	}
}

void deleteBehaviour(int res){
	if(res == 200){
		printf("Badge supprimé avec succès !\n\n\n");
	    	digitalWrite (LED, HIGH) ;	// On
	    	delay (1000);			// mS
	    	digitalWrite (LED, LOW) ;	// Off	
	} else {	
		printf("Problème lors de la suppression du badge !\n\n");
		digitalWrite (LED, HIGH) ;	// On
	    	delay (500);			// mS
	    	digitalWrite (LED, LOW) ;	// Off
		delay (500);
		digitalWrite (LED, HIGH) ;	// On
	    	delay (500);			// mS
	    	digitalWrite (LED, LOW) ;	// Off  
	}
}

void readBehaviour(int res){
	if(res == 200){
		printf("OK\n\n\n");
	    	digitalWrite (GACHE, HIGH) ;	// On
	    	delay (4000);			// mS
	    	digitalWrite (GACHE, LOW) ;	// Off	
	} else {		
		printf("NOK\n\n");
		digitalWrite (LED, HIGH) ;	// On
	    	delay (500);			// mS
	    	digitalWrite (LED, LOW) ;	// Off
		delay (500);
		digitalWrite (LED, HIGH) ;	// On
	    	delay (500);			// mS
	    	digitalWrite (LED, LOW) ;	// Off  
	}
}


long makeRequest(char* URL){
	CURL *curl;
	CURLcode res;
	long http_code;

	curl_global_init(CURL_GLOBAL_DEFAULT);	
	curl = curl_easy_init();

	if(curl) {
		FILE *tempbody = fopen("temp/curl_body.txt","w");

		curl_easy_setopt(curl, CURLOPT_URL, URL);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, tempbody);		
		res = curl_easy_perform(curl); 
	
	
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE,&http_code);
		//printf("\nStatus : %i\n", http_code);
	
		curl_easy_cleanup(curl);
	}
	
	return http_code;
}

void readRFID()
{
	char tmp[25];
	FILE * file;
	file = fopen( "temp/rfid_code.txt" , "r");
	if (file) {
	    while (fscanf(file, "%s", badgeCode)!=EOF)
	        printf("\nTag RFID lu : %s\n\n",badgeCode);
	    fclose(file);
	}
}

int getCurrentMode(){
	//PREPARATION DE L'URL A INTERROGER
	char URL[40];
	strcpy(URL,BASE_URL);
	strcat(URL,MODE_ROUTE);

	switch(makeRequest(URL)){
		case 201:
			return 1;
			break;
		
		case 202:			
			return 2;
			break;
		
		default:
			return -1;
	}	
}

