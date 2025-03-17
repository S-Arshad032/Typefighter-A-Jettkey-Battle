

bool e = false ; 
int ex[7];
int expIndex = 0; 
int expX , expY ; 

void explosion() {
		iShowImage(expX , expY, 200, 200, ex[expIndex]); 
	}


void ExpControl(){
	expIndex ++ ; 
	if(expIndex>=7){
		expIndex = 0 ; 
		e = false ; 
	}

}
