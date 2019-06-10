#include <stdio.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <pthread.h>

#define	GACHE	0
#define LED 2
#define BASE_URL "http://172.20.10.2:8080/"
#define STATUS_ROUTE "status/"
#define ADD_ROUTE "add/"
#define DELETE_ROUTE "delete/"
#define MODE_ROUTE "mode"

int mode;
char modeApiRoute[15];
char badgeCode[25];
char URL[40];

void init();
void manageBadge();
void readRFID();
long makeRequest(char*);
int getCurrentMode();
void readBehaviour(int);
void addBehaviour(int);
void deleteBehaviour(int);