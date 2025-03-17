
int dy = 1; 
int score = 0 ; 
int hp = 10 ; 
char scoreText[100];
void showScore(){

	 iSetColor(255, 255, 255);

   
    sprintf(scoreText, "Score: %d", score);
    iText(20, screenHeight - 50, scoreText, GLUT_BITMAP_TIMES_ROMAN_24);


	if(score>=0 && score<70) dy = 1 ;
	if(score>=70 && score<140) dy = 2 ;
	if(score>=140 && score<180) dy = 3 ; 

}

//--------------------- highscore --------------------------
int len = 0;
char str1[100];
bool newscore = true;

struct hscore{
	char name[30];
	int score ;
}high_score[5];


//in order to take input after a player finishes the game or dies
void drawTextBox()
{
	iSetColor(255, 255, 255);
	iText(700, 200 , scoreText, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(300, 220 , "Enter name:", GLUT_BITMAP_TIMES_ROMAN_24);
	iSetColor(150, 140, 150);
	iRectangle(300, 190 , 180, 25);
	iSetColor(255, 255, 255);
	iText(320 , 195 , str1, GLUT_BITMAP_TIMES_ROMAN_24);
}
//will be added after a player dies or finishes the game
void newHighscore(){
	FILE *fp;
	fp = fopen("Score.txt", "r");
	for (int i = 0; i < 5; i++){
		fscanf(fp, "%s %d\n", high_score[i].name, &high_score[i].score);
	}
	int t; // temp score for s
	char n[30];//temp name for s
	//might need to add a bool
	if (newscore) {
		printf("%d\n", score);
		for (int i = 0; i < 5; i++) {
			if (high_score[i].score < score) {
				high_score[4].score = score;
				strcpy(high_score[4].name, str1);

				for (int j = 0; j < 5; j++) { // Fix the condition here
					for (int k = 5; k > j; k--) {
						if (high_score[k].score > high_score[k - 1].score) {
							// Sorting logic
							int t = high_score[k - 1].score;
							high_score[k - 1].score = high_score[k].score;
							high_score[k].score = t;

							char n[50]; // Declare n here
							strcpy(n, high_score[k - 1].name);
							strcpy(high_score[k - 1].name, high_score[k].name);
							strcpy(high_score[k].name, n);
						}
					}
				}

				// Write the sorted scores to the file
				FILE* fp = fopen("Score.txt", "w");
				for (int i = 0; i < 5; i++) {
					fprintf(fp, "%s %d\n", high_score[i].name, high_score[i].score);
				}
				fclose(fp);

				newscore = false; // Reset newscore
				break; // Exit the loop since sorting is done
			}
		}
	}
}