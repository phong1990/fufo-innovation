#include "FUFO.h"

unsigned int mainState = 0;

int getState(){
	return mainState;
}

void setState(unsigned int State){
	mainState = State;
}