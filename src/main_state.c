#include <main_state.h>
#include <glad/glad.h>
#include <math.h>

#include <game_constants.h>
#include <rafgl.h>

static int w,h;
static rafgl_raster_t raster;
static rafgl_texture_t tex;


static rafgl_spritesheet_t mapa,hrana,zmija,zmijaSmrt,gameOverSlika,SnakeOverlay;

#define MAX_BROJ 189

struct hranaStruktura{
int x;
int y;
int oblikHrane;
int daLiJePojedena;
int prviUlaz;
}nizHrana[MAX_BROJ];
int brojacZaHranu = 0;


//ovo se ne koristi ali moze i na taj nacin
struct zmijaStruktura{

int glavaX;
int glavaY;
int repX;
int repY;
int teloX[MAX_BROJ];
int teloY[MAX_BROJ];
}zmijaStru;



void main_state_init(GLFWwindow *window, void *args, int width, int height)
{
    w = width;
    h = height;
    rafgl_raster_init(&raster, w, h);
    rafgl_texture_init(&tex);

    for(int i = 0; i<MAX_BROJ;i++){
    nizHrana[i].daLiJePojedena = 0;
    nizHrana[i].x =-1;
    nizHrana[i].y =-1;
    nizHrana[i].oblikHrane=-1;
    nizHrana[i].prviUlaz=1;
}

    //rafgl_raster_load_from_image(&mapa,);

    rafgl_spritesheet_init(&mapa, "res/spriteMapa/mapa5050.png", 4, 5);
    rafgl_spritesheet_init(&hrana, "res/spriteHrana/hrana5050.png", 6, 4);
    rafgl_spritesheet_init(&zmija, "res/spriteZmija/Zmija5050.png", 4, 6);
    rafgl_spritesheet_init(&zmijaSmrt, "res/spriteZmijaSmrt/zmijaSmrt5050.png", 4, 2);
    rafgl_spritesheet_init(&gameOverSlika, "res/spriteGameOver/gameOverSprite150100.png",1,1);
    rafgl_spritesheet_init(&SnakeOverlay, "res/spriteSnakeOverlay/snakeOverlay350100.png",1,1);

}
int brojacZaHuver = 0;
int gameEnd = 0;
//int prvi = 1;
int mapaMatrica[14][18] ={
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 1, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,-1,
-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};

void pravi_mapu(void){ //crta mapu
    int par = 1;
    int par2 = 2;
    int broj = 0;
    for(int x = 0; x<=w -50; x+=50){
            if(broj == 0){
                broj = 1;
            }
            else
                broj = 0;
            for(int y = 0; y<=h -50;y+=50){
                    if(x==0 || y == 0 || x == w -50 || y == h - 50){
                        if(par ==2){
                            rafgl_raster_draw_spritesheet(&raster, &mapa, 2, 4, x, y);
                            par = 0;
                        }
                        else{
                            rafgl_raster_draw_spritesheet(&raster, &mapa, 3, 4, x, y);
                            par++;
                        }
                        if(par2==broj){
                                par2=broj-1;
                            }
                            else{
                                par2=broj;
                            }
                    }
                    else if(x==50 && y==50){
                        rafgl_raster_draw_spritesheet(&raster, &mapa, 3, 0, x, y);
                        if(par2==broj){
                                par2=broj-1;
                            }
                            else{
                                par2=broj;
                            }
                    }
                    else if (x==50 && y == h-100){
                        rafgl_raster_draw_spritesheet(&raster, &mapa, 1, 2, x, y);
                        if(par2==broj){
                                par2=broj-1;
                            }
                            else{
                                par2=broj;
                            }
                    }
                    else if(x==w -100 && y==h -100){
                        rafgl_raster_draw_spritesheet(&raster, &mapa, 0, 0, x, y);
                        if(par2==broj){
                                par2=broj-1;
                            }
                            else{
                                par2=broj;
                            }
                    }
                    else if(x==w - 100 && y==50){
                        rafgl_raster_draw_spritesheet(&raster, &mapa, 2, 2, x, y);
                        if(par2==broj){
                                par2=broj-1;
                            }
                            else{
                                par2=broj;
                            }
                    }
                    else if(x==50 && y>50 && y <h-50){
                            if(par2==broj){
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 1, 3, x, y);
                                par2=broj-1;
                            }
                            else{
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 1, 1, x, y);
                                par2=broj;
                            }
                    }
                    else if(x==w-100 && y>50 && y <h-50){
                            if(par2==broj){
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 3, 3, x, y);
                                par2=broj-1;
                            }
                            else{
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 3, 1, x, y);
                                par2=broj;
                            }
                    }
                    else if(y==50 && x>50 && x<w-50){
                            if(par2==broj){
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 2, 3, x, y);
                                par2=broj-1;
                            }
                            else{
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 2, 1, x, y);
                                par2=broj;
                            }
                    }
                    else if(y==h-100 && x>50 && x<w-50){
                            if(par2==broj){
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 0, 3, x, y);
                                par2=broj-1;
                            }
                            else{
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 0, 1, x, y);
                                par2=broj;
                            }
                    }
                    else{
                            if(par2==broj){
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 1, 4, x, y);
                                par2=broj-1;
                            }
                            else{
                                rafgl_raster_draw_spritesheet(&raster, &mapa, 0, 4, x, y);
                                par2=broj;
                            }

                    }

                  //  printf("0");
            }
            //printf("\n");
    }
    if(brojacZaHuver && !gameEnd){
        for(int x = 0;x<=200;x++){
            for(int y=0;y<=200;y++){
                if((x==y-1 || x==y || x==y+1 || x+10==y-1 || x+10==y || x+10==y+1 || x-10==y-1 || x-10==y || x-10==y+1
                   || x-1==y-10 || x+1==y-10 || x==y-10 || x-1==y+10 || x+1==y+10 || x==y+10
                   ) && (x < 200 && y < 200))
                pixel_at_m(raster,x,y).rgba = rafgl_RGB(255,250,147);


            }
            for(int y=500;y<=h;y++){
                if((h-y == x-1 || h-y == x || h-y == x+1 || h-y -10== x-1 || h-y-10 == x || h-y-10 == x+1 ||
                    h-y +10 == x-1 || h-y +10  == x || h-y +10== x+1 )&&(x<200 && y>500))
                    pixel_at_m(raster,x,y).rgba = rafgl_RGB(255,250,147);
            }
        }
        for(int x = 700;x<=w;x++){
            for(int y=500;y<=h;y++){

                if( (x-200 == y  || x-200 +1 == y  || x-200 -1 == y || x-200 -10 == y  || x-200 +1 -10 == y  || x-200 -11 == y
                     || x-200+10 == y  || x-200 +1 +10 == y  || x-200 -1 +10 == y) &&( x>700 && x<w && y<h && y>500 )){
                    pixel_at_m(raster,x,y).rgba = rafgl_RGB(255,250,147);
                }


            }
            for(int y=0;y<=200;y++){
                if((x+y == 900 || x+y+1 == 900 || x+y-1 == 900 || x+y +10 == 900 || x+y+11 == 900 || x+y-1+10 == 900
                     || x+y -10 == 900 || x+y+1-10 == 900 || x+y-11 == 900) &&(x>700 && x<w && y < 200)){
                    pixel_at_m(raster,x,y).rgba = rafgl_RGB(255,250,147);
                }
            }
        }
    }
}

int hover_frames =0;
int animation_frame=0;
int eaten =1;
int ranx,rany,ranVocka;
int glava =3;
int direction =1;
/*
1 desno
2 gore
3 levo
4 dole
*/
void odrediPozicijuVocke(void){ // generise lokaciju

    if(nizHrana[brojacZaHranu].prviUlaz){

        int xp = (rand() % 14);
        int yp = (rand() % 18);
            while(mapaMatrica[xp][yp] != 0 ){
                xp = (rand() % 14);
                yp = (rand() % 18);
            }
        mapaMatrica[xp][yp] = -2;
        nizHrana[brojacZaHranu].x = yp*50;
        nizHrana[brojacZaHranu].y = xp*50;
        //printf("%d ,%d",nizHrana[brojacZaHranu].x,nizHrana[brojacZaHranu].y);
        nizHrana[brojacZaHranu].oblikHrane = rand() % 4;
        nizHrana[brojacZaHranu].prviUlaz =0;
    }
}


void generisi_vocku(void){ //generise vocku i dodeljuje lokaciju

        if(nizHrana[brojacZaHranu].daLiJePojedena){
            brojacZaHranu++;
        }
        if(!nizHrana[brojacZaHranu].daLiJePojedena){

            odrediPozicijuVocke();
        }
        if(hover_frames == 0)
        {
            animation_frame = (animation_frame + 1) % 6;
            hover_frames = 25;
        }
        else
        {
            hover_frames--;
        }
    rafgl_raster_draw_spritesheet(&raster, &hrana, animation_frame, nizHrana[brojacZaHranu].oblikHrane, nizHrana[brojacZaHranu].x, nizHrana[brojacZaHranu].y);
}

int huuver = 0;
int gameover = 0;
int proso = 0;

int tu=1;

int seterZaSmer = 1;
int seterZaHuver = 30;
int gameStart = 0;
int brojPoena = 0;


void gameKraj(void){ // ispisuje broj poena moze i bez toga
    printf("%d duzina i %d coina",glava-3,brojPoena);
    //implementirati brisanje zmije
    gameEnd=1;
}
int xLinija=-201;
int yLinija=0;

float aps(float i){
    //printf("%f",i);
    if(i<0){
        i*= -1;
        return i;
    }
    return i;
}

int odrediParabolu(int x){ // funkcije parabola ga gameOver tekts
        /*if(x < 900/4) {

        float a = (8.0*700.0)/(900.0*900.0);
        //int b = 0;
        //int c = 0;
        //printf("%d %d %d %d \n",a,x , w,h);
        return a*(x*x)-50;
    }
        else if(x>=900/4 && x < 2*900/4-50)
        {
        float p = 900.0/4.0;
        float q = 900.0/2.0-50.0;
        float a = -0.92;
        float b = -1.0*a*(p+q);
        int c = 90300;

        printf("%d \n",a*x*x + b*x +c );
        return a*x*x + b*x +c;

        }/*
        else if(x>= 900/2){
            xLinija=2*900/4 -50;
            yLinija=700/2-50;
            return yLinija;
        }*/
        //return aps((1/(100*x))*sinf(2*x*1.0))*450;
        //printf("%d\n ", x );
        /*printf("%f %d \n",-4500*aps((5.0/x) * sinf(x/50.0))+450.0 , x );
        float my_var = -4500.0*aps((5.0/x) * sinf(x/50.0))+450.0;
        my_var = (int)my_var;
        return -4500.0*aps((5.0/x) * sinf(x/50.0))+450.0;*/

        /*printf("%d %f \n",x ,200 * sinf(x/50.0));
        x+=70;
        return -3500 * aps(5.0/x * sinf(x/50.0)) +350.0 -50;
        */
        x+=70;
        return -2200 * aps(10.0/x * sinf(x/30.0)) +350.0 -50;
}

void gameOverOverlay(void){ //prikaz gameOver teksta
    /*for(int i = 0;i<w;i++){
        for(int j = 0; j<h;j++){
            rafgl_raster_draw_spritesheet(&raster, &gameOverSlika, 0 ,0 ,i,j);
        }
    }*/
    if(xLinija< 3*w/4){
    rafgl_raster_draw_spritesheet(&raster, &gameOverSlika, 0 ,0 ,xLinija,yLinija);
    if(xLinija < 900/2-50-1){
    xLinija++;
    yLinija=odrediParabolu(xLinija);
    }
    else{
        xLinija = 900/2-50;
        yLinija = 700/2-50;
    }
    //printf("%d",yLinija);
    }
}


int hoverZaKraj = 50;
int randomBrojac = 0;
void kretnjaZmije(void){ // milion ifova za smer zmije

    //int strana =0;
   // if(!gameEnd){
    for(int i=0;i<14;i++){
        for(int j=0;j<18; j++){

            if(mapaMatrica[i][j] == glava){//glava
                if(!gameEnd){
                    if(mapaMatrica[i-1][j] == glava-1 && glava != 1){
                        if(direction == 1){
                            rafgl_raster_draw_spritesheet(&raster, &zmijaSmrt, 3, 1, j*50, i*50);
                        }
                        else if(direction ==3){
                            rafgl_raster_draw_spritesheet(&raster, &zmijaSmrt, 3, 0, j*50, i*50);
                        }
                        else
                            rafgl_raster_draw_spritesheet(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                    }
                    else if(mapaMatrica[i+1][j] == glava-1 && glava != 1){
                        if(direction == 1){
                            rafgl_raster_draw_spritesheet(&raster, &zmijaSmrt, 1, 0, j*50, i*50);
                        }
                        else if(direction ==3){
                            rafgl_raster_draw_spritesheet(&raster, &zmijaSmrt, 1, 1, j*50, i*50);
                        }
                        else
                            rafgl_raster_draw_spritesheet(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                    }
                    else if(mapaMatrica[i][j+1] == glava-1 && glava != 1){
                        if(direction == 2){
                            rafgl_raster_draw_spritesheet(&raster, &zmijaSmrt, 2, 0, j*50, i*50);
                        }
                        else if(direction ==4){
                            rafgl_raster_draw_spritesheet(&raster, &zmijaSmrt, 2, 1, j*50, i*50);
                        }
                        else
                            rafgl_raster_draw_spritesheet(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                    }
                    else if(mapaMatrica[i][j-1] == glava-1 && glava != 1){
                        if(direction == 2){
                            rafgl_raster_draw_spritesheet(&raster, &zmijaSmrt, 0, 1, j*50, i*50);
                        }
                        else if(direction ==4){
                            rafgl_raster_draw_spritesheet(&raster, &zmijaSmrt, 0, 0, j*50, i*50);
                        }
                        else
                            rafgl_raster_draw_spritesheet(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                    }
                    else if(glava != 1)
                    rafgl_raster_draw_spritesheet(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                }else{
                    if(mapaMatrica[i-1][j] == glava-1 && glava != 1){
                        if(direction == 1){
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmijaSmrt, 3, 1, j*50, i*50);
                        }
                        else if(direction ==3){
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmijaSmrt, 3, 0, j*50, i*50);
                        }
                        else
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                    }
                    else if(mapaMatrica[i+1][j] == glava-1 && glava != 1){
                        if(direction == 1){
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmijaSmrt, 1, 0, j*50, i*50);
                        }
                        else if(direction ==3){
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmijaSmrt, 1, 1, j*50, i*50);
                        }
                        else
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                    }
                    else if(mapaMatrica[i][j+1] == glava-1 && glava != 1){
                        if(direction == 2){
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmijaSmrt, 2, 0, j*50, i*50);
                        }
                        else if(direction ==4){
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmijaSmrt, 2, 1, j*50, i*50);
                        }
                        else
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                    }
                    else if(mapaMatrica[i][j-1] == glava-1 && glava != 1){
                        if(direction == 2){
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmijaSmrt, 0, 1, j*50, i*50);
                        }
                        else if(direction ==4){
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmijaSmrt, 0, 0, j*50, i*50);
                        }
                        else
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                    }
                    else if(glava != 1)
                    rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, direction-1, (randomBrojac)%2, j*50, i*50);
                }

            }
            else if(mapaMatrica[i][j] >= 1){
                if(mapaMatrica[i][j] == 1){//rep
                        if(!gameEnd){
                    if(mapaMatrica[i][j]+1 == mapaMatrica[i][j+1])
                    rafgl_raster_draw_spritesheet(&raster, &zmija, 0, 3, j*50, i*50);//desno
                    if(mapaMatrica[i][j]+1 == mapaMatrica[i][j-1])
                    rafgl_raster_draw_spritesheet(&raster, &zmija, 2, 3, j*50, i*50);//levo
                    if(mapaMatrica[i][j]+1 == mapaMatrica[i+1][j])
                    rafgl_raster_draw_spritesheet(&raster, &zmija, 3, 3, j*50, i*50);//dole
                    if(mapaMatrica[i][j]+1 == mapaMatrica[i-1][j])
                    rafgl_raster_draw_spritesheet(&raster, &zmija, 1, 3, j*50, i*50);//gore
                        }
                        else{
                    if(mapaMatrica[i][j]+1 == mapaMatrica[i][j+1])
                    rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 0, 3, j*50, i*50);//desno
                    if(mapaMatrica[i][j]+1 == mapaMatrica[i][j-1])
                    rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 2, 3, j*50, i*50);//levo
                    if(mapaMatrica[i][j]+1 == mapaMatrica[i+1][j])
                    rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 3, 3, j*50, i*50);//dole
                    if(mapaMatrica[i][j]+1 == mapaMatrica[i-1][j])
                    rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 1, 3, j*50, i*50);//gore
                        }
                }
                else{//telo
                    if(mapaMatrica[i][j]+1 == mapaMatrica[i][j+1])
                    {
                        if(!gameEnd){
                        if(mapaMatrica[i][j]-1 == mapaMatrica[i][j-1])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 0, 2, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i+1][j])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 1, 4, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i-1][j])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 2, 5, j*50, i*50);
                        }
                        else{

                        if(mapaMatrica[i][j]-1 == mapaMatrica[i][j-1])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 0, 2, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i+1][j])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 1, 4, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i-1][j])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 2, 5, j*50, i*50);
                        }
                    }
                    else if(mapaMatrica[i][j]+1 == mapaMatrica[i][j-1])
                    {
                        if(!gameEnd){
                        if(mapaMatrica[i][j]-1 == mapaMatrica[i][j+1])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 2, 2, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i+1][j])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 0, 5, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i-1][j])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 3, 4, j*50, i*50);
                        }else{
                        if(mapaMatrica[i][j]-1 == mapaMatrica[i][j+1])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 2, 2, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i+1][j])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 0, 5, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i-1][j])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 3, 4, j*50, i*50);
                        }
                    }
                    else if(mapaMatrica[i][j]+1 == mapaMatrica[i+1][j])
                    {
                        if(!gameEnd){
                        if(mapaMatrica[i][j]-1 == mapaMatrica[i][j+1])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 1, 4, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i][j-1])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 0, 4, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i-1][j])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 3, 2, j*50, i*50);
                        }
                        else{
                            if(mapaMatrica[i][j]-1 == mapaMatrica[i][j+1])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 1, 4, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i][j-1])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 0, 4, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i-1][j])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 3, 2, j*50, i*50);
                        }
                    }
                    else if(mapaMatrica[i][j]+1 == mapaMatrica[i-1][j])
                    {
                        if(!gameEnd){
                        if(mapaMatrica[i][j]-1 == mapaMatrica[i][j+1])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 2, 4, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i][j-1])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 3, 5, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i+1][j])
                            rafgl_raster_draw_spritesheet(&raster, &zmija, 1, 2, j*50, i*50);
                        }else{
                        if(mapaMatrica[i][j]-1 == mapaMatrica[i][j+1])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 2, 4, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i][j-1])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 3, 5, j*50, i*50);
                        else if(mapaMatrica[i][j]-1 == mapaMatrica[i+1][j])
                            rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 1, 2, j*50, i*50);
                        }
                    }
                }
            }
        }

    }
    /*}
    else{
        thanosSnap();
    }*/
    //rafgl_raster_draw_spritesheet_smrt_zmije(&raster, &zmija, 1, 2, 150, 150);

}


void igrica(rafgl_game_data_t *game_data){ //kontrola za kretnju i instanciranja
    generisi_vocku();
    if(game_data->keys_pressed[RAFGL_KEY_W] || game_data->keys_pressed[RAFGL_KEY_UP])
    {
            if(direction != 2 && direction != 4){
                //direction = 2;
                seterZaSmer =2;
            }
    }
    else if(game_data->keys_pressed[RAFGL_KEY_S] || game_data->keys_pressed[RAFGL_KEY_DOWN])
    {
            if(direction != 2 && direction != 4){
               // direction = 4;
                seterZaSmer = 4;
            }
    }
    else if(game_data->keys_pressed[RAFGL_KEY_A] || game_data->keys_pressed[RAFGL_KEY_LEFT])
    {
            if(direction != 3 && direction != 1){
                //direction = 3;
                seterZaSmer = 3;
            }
    }
    else if(game_data->keys_pressed[RAFGL_KEY_D] || game_data->keys_pressed[RAFGL_KEY_RIGHT])
    {
            if(direction != 3 && direction != 1){
                //direction = 1;
                seterZaSmer =1;
            }
    }

    if(tu){

        //sleep(0,7);
        if(huuver == 0){
        int novaGlavaI = 0 ,novaGlavaJ = 0;
        for(int i = 0; i<14;i++){
            for(int j = 0; j<18; j++){
                direction = seterZaSmer;
               /* if(mapaMatrica[i][j] == glava && mapaMatrica[i][j+1] != -1){
                    mapaMatrica[i][j+1] = glava;
                }*/
                if(mapaMatrica[i][j] > 0){
                    if(mapaMatrica[i][j] == glava){
                        if(direction ==1 && mapaMatrica[i][j+1] == 0){
                        novaGlavaI=i;
                        novaGlavaJ=j+1;
                        proso = 1;
                        }else if(direction ==2 && mapaMatrica[i-1][j] == 0){
                        novaGlavaI=i-1;
                        novaGlavaJ=j;
                        proso = 1;
                        }else if(direction ==3 &&  mapaMatrica[i][j-1] == 0){
                        novaGlavaI=i;
                        novaGlavaJ=j-1;
                        proso = 1;
                        }else if(direction ==4 && mapaMatrica[i+1][j] == 0){
                        novaGlavaI=i+1;
                        novaGlavaJ=j;
                        proso = 1;
                        }
                        else if(direction ==1 && mapaMatrica[i][j+1] == -2){
                        novaGlavaI=i;
                        novaGlavaJ=j+1;
                        //generisi_vocku();
                        proso = 1;
                        nizHrana[brojacZaHranu].daLiJePojedena = 1;
                        }else if(direction ==2 && mapaMatrica[i-1][j] == -2){
                        novaGlavaI=i-1;
                        novaGlavaJ=j;
                        //generisi_vocku();
                        proso = 1;
                        nizHrana[brojacZaHranu].daLiJePojedena = 1;
                        }else if(direction ==3 &&  mapaMatrica[i][j-1] == -2){
                        novaGlavaI=i;
                        novaGlavaJ=j-1;
                        //generisi_vocku();
                        proso = 1;
                        nizHrana[brojacZaHranu].daLiJePojedena = 1;
                        }else if(direction ==4 && mapaMatrica[i+1][j] == -2){
                        novaGlavaI=i+1;
                        novaGlavaJ=j;
                        //generisi_vocku();
                        proso = 1;
                        nizHrana[brojacZaHranu].daLiJePojedena = 1;
                        }
                        else{
                            novaGlavaI=i;
                            novaGlavaJ=j;
                            gameStart=0;
                            gameKraj();
                        }

                        //mapaMatrica[i][j]--;
                    }
                    /*else if(mapaMatrica[i][j] == glava && mapaMatrica[i][j+1] == -1){
                        if(!gameover){
                        printf("game over");
                        //gameover=1;
                        }
                    }*/


                }

            }
        }
        int nemoj =1;
        for(int i = 0; i<14;i++){
            for(int j = 0; j<18; j++){
                if(mapaMatrica[i][j] == glava){
                        if(i == novaGlavaI && j == novaGlavaJ){
                            nemoj = 0;
                        }
                    //printf("%d,",mapaMatrica[][]);
                }
               // printf("%d,",mapaMatrica[i][j]);
            }
           // printf("\n");
        }
        if(nemoj){
        if(!nizHrana[brojacZaHranu].daLiJePojedena){
        for(int i = 0; i<14;i++){
            for(int j = 0; j<18; j++){
                if(mapaMatrica[i][j]>0 && proso){
                    mapaMatrica[i][j]--;
                    //printf("%d,",mapaMatrica[][]);
                }
               // printf("%d,",mapaMatrica[i][j]);
            }
           // printf("\n");
        }

        proso=0;
        }
        else{
            glava++;
        }
        if(novaGlavaI != 0 && novaGlavaJ != 0)
        mapaMatrica[novaGlavaI][novaGlavaJ] = glava;
       /* for(int i = 0; i<14;i++){
            for(int j = 0; j<18; j++){
                printf("%d,",mapaMatrica[i][j]);
            }
            printf("\n");
        }*/
    randomBrojac++;
    //kretnjaZmije();
    if(nizHrana[brojacZaHranu].oblikHrane == 1 && nizHrana[brojacZaHranu].daLiJePojedena) brojPoena++;
    if(nizHrana[brojacZaHranu].oblikHrane == 3 && nizHrana[brojacZaHranu].daLiJePojedena){
        brojacZaHuver = 10;
    }
    if(brojacZaHuver >0){
        huuver = 10;
        brojacZaHuver--;
    }
    else
        huuver = 40;
    }
    }
    else{
        huuver--;
    }
    }

}

int prviUlazUIgricu =1;

void zmicaOver(void){
    rafgl_raster_draw_spritesheet(&raster,&SnakeOverlay,0,0,450-180,350-80);
}


void main_state_update(GLFWwindow *window, float delta_time, rafgl_game_data_t *game_data, void *args)
{
    pravi_mapu();
    kretnjaZmije();
    if(!gameStart && !gameEnd){
        zmicaOver();
    }
    if(game_data->keys_pressed[RAFGL_KEY_SPACE]){ //} || game_data->is_lmb_down){
        if(prviUlazUIgricu){
            gameStart=1;
            prviUlazUIgricu=0;
        }
    }
    if(gameStart){
            igrica(game_data);
    }
    if(gameEnd){

        if(glava>= 1){
        if(hoverZaKraj ==0){
                hoverZaKraj = 50;
                for(int i = 0; i<14;i++){
                    for(int j = 0; j<18; j++){
                        if(mapaMatrica[i][j]>0){
                            mapaMatrica[i][j]--;
                            if(mapaMatrica[i][j] == glava && glava==1){
                                mapaMatrica[i][j]-= 2;
                            }

                    //printf("%d,",mapaMatrica[][]);
                }
               // printf("%d,",mapaMatrica[i][j]);
            }
           // printf("\n");
        }
        if(glava >= 2)
        glava--;
        }
        else if(hoverZaKraj>0){

            hoverZaKraj--;
        }
        if(glava==1) glava=-3;
        }
        else{
                gameOverOverlay();
        }

    }
}

void main_state_render(GLFWwindow *window, void *args)
{

    rafgl_texture_load_from_raster(&tex, &raster);
    rafgl_texture_show(&tex, 0);


}

void main_state_cleanup(GLFWwindow *window, void *args)
{

}
