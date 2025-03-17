 
int ship ; 

struct buttonCordinate
{
	int x ; 
	int y ;
}bCordinate[4] ; 

int play ;
int scoreBtn ; 
int instruction ;
int aboutUs ; 

int button[4] ; 
int buttonsHover[4] ; 
int Menubg ; 
int back ; 
int resume ; 

int gameState = -1 ; 

int hoverIndex = -1 ; 
bool canHover = true ;
bool showBack = false ; 
bool pause = false ; 

void  Background();
void birdFigure();
void showScore() ;

void showMenu(){

    if (gameState == -1) {
        iShowImage(0, 0, 1000, 600, Menubg);

        for (int i = 0; i < 4; i++) {
            iShowImage(bCordinate[i].x, bCordinate[i].y, 200, 60, button[i]);
        }
	}

    else if (gameState == 0) {
        canHover = false;
        if (pause) {
            iShowImage(400, 400, 200, 60, resume);
        } 
		else {
            Background();
			birdFigure();
			showScore() ;
			drawHealthBar();

			if(e){
				explosion() ; 
			}
		  iShowImage(500, 0, 100, 100, ship);
          bullet();


        }
    }

	else if(gameState == 1){
		canHover = false ; 
		iShowImage(0, 0,1000,600, aboutUs) ; 
		showBack = true ; 
		iShowImage(0,500,150,80, back) ; 
	}

	else if(gameState == 2){
		canHover = false ; 
		iShowImage(0, 0,1000,600, scoreBtn) ; 
		FILE *fp;
		fp = fopen("Score.txt", "r");
		if (fp == '\0'){
			cout << "FILE NOT FOUND" << endl;
		}
		char showName[5][30], showScore[5][5];
		for (int i = 0; i < 5; i++){
			fscanf(fp, "%s %d\n", high_score[i].name, &high_score[i].score);
		}
		for (int i = 0; i < 5; i++){
			sprintf(showName[i], "%s", high_score[i].name);
			sprintf(showScore[i],"%d", high_score[i].score);
			iText(300, 400-80*i, showName[i], GLUT_BITMAP_HELVETICA_18);
			iText(600, 400-80*i, showScore[i], GLUT_BITMAP_HELVETICA_18);
		}
		fclose(fp);
		showBack = true ; 
		iShowImage(0,500,150,80, back) ; 
	}

	else if(gameState == 3){
		exit(0) ; 
	}

}


void hover()
{
    if (canHover==true && gameState == -1)
    {
        for (int i = 0; i < 4; i++)
        {
            if (hoverIndex == i)
            {
                iShowImage(bCordinate[i].x, bCordinate[i].y, 220, 80, buttonsHover[i]);
                iSetColor(255, 255, 0);
                iRectangle(bCordinate[i].x, bCordinate[i].y, 220, 80);
                iFilledRectangle(bCordinate[i].x - 20, bCordinate[i].y - 12, 260, 8);
				break ; 
            }
            else
            {
				iShowImage(bCordinate[i].x, bCordinate[i].y, 200, 60, button[i]);
            }
        }
    }

	if(gameState ==-1)
		canHover = true ; 
}