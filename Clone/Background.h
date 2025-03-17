
int bgdy = 1;
 
static int bg1Y = 0, bg1X = 0;
static int bg2Y = screenHeight - 40, bg2X = 0;
int bg1, bg2 , bg3 , bg4,bg5;

static int bg3Y = 0, bg3X = 0;
static int bg4Y = screenHeight - 40, bg4X = 0;

void Background()
{
    if(score >= 0 && score <= 70)
    {
        bg1Y -= bgdy;
        if (bg1Y <= -screenHeight)
        {
            bg1Y = screenHeight;
        }
        iShowImage(bg1X, bg1Y, screenWidth, screenHeight, bg1);

        bg2Y -= bgdy;
        if (bg2Y <= -screenHeight)
        {
            bg2Y = screenHeight;
        }
        iShowImage(bg2X, bg2Y, screenWidth, screenHeight, bg2);
    }

	else if (score > 70 && score <= 140)
    {
        bg3Y -= bgdy;
        if (bg3Y <= -screenHeight)
        {
            bg3Y = screenHeight;
        }
        iShowImage(bg3X, bg3Y, screenWidth, screenHeight, bg3);

        bg4Y -= bgdy;
        if (bg4Y <= -screenHeight)
        {
            bg4Y = screenHeight;
        }
        iShowImage(bg4X, bg4Y, screenWidth, screenHeight, bg4);
    }


	else
	{
		bg1Y -= bgdy;
        if (bg1Y <= -screenHeight)
        {
            bg1Y = screenHeight;
        }
        iShowImage(bg1X, bg1Y, screenWidth, screenHeight, bg1);

        bg2Y -= bgdy;
        if (bg2Y <= -screenHeight)
        {
            bg2Y = screenHeight;
        }
        iShowImage(bg2X, bg2Y, screenWidth, screenHeight, bg2);
	}
}