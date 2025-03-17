

#define MAX_BULLETS 5

int temX , temY ; 
int b ;

double difx =0 , dify = 0 ;  
double ship_distance = 0 ; 
int speed = 40 ;

struct Bullet {
    double x ;
    double y ;
    double moveX ;
    double moveY ;
    bool active ;
};

Bullet rocket[MAX_BULLETS];

void bullet()
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (rocket[i].active)
        {
            if (rocket[i].y <= temY)
            {
                iShowImage(rocket[i].x, rocket[i].y , 80, 80, b);
            }

            rocket[i].x += rocket[i].moveX;
            rocket[i].y += rocket[i].moveY;

            if (rocket[i].y >= temY)
            {
                rocket[i].active = false;
            }
        }
    }
}


void fireRocket(int Rx, int Ry)
{
    for (int i = 0; i < MAX_BULLETS; i++)
    {
        if (!rocket[i].active)
        {
            rocket[i].active = true;
            rocket[i].x = 500;
            rocket[i].y = 0;

            difx = Rx - rocket[i].x;
            dify = Ry - rocket[i].y;

            ship_distance = sqrt(difx * difx + dify * dify);

            rocket[i].moveX = speed * (difx / ship_distance);
            rocket[i].moveY = speed * (dify / ship_distance);

            break;
        }
    }
}
