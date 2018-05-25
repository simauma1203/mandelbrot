//川合さんのblaライブラリを使用したマンデルブロー集合描画プログラム
#include<stdio.h>
#include<math.h>
#include<conio.h>
#include "bla.h"

const int WIDTH=1024;
const long double DIFF=0.5;

void drawRect(int,int,int,int,int);

bla_Window *win;

int main(int argc, const char **argv)
{
	win = bla_openWin(WIDTH, WIDTH, "kireikana");
    
    //-----
    int pixSiz=1;
    int ix,iy;
    long double x,y;
    long double re,im,re_,im_;
    int pix=WIDTH;
    long double dx=0.48,dy=-0.53;
    long double clipMaxY=0.1+dy,clipMinY=-0.4+dy;//+-1.6
    long double clipMaxX=-0.5+dx,clipMinX=-1.0+dx;
    int tm,maxTm=100,devJg=1000;//devergence
    int ch;//input

    draw:

    for(ix=0;ix<WIDTH;ix+=pixSiz){
        for(iy=0;iy<WIDTH;iy+=pixSiz){
            
            x=clipMinX+ix*(clipMaxX-clipMinX)/WIDTH;
            y=clipMinY+iy*(clipMaxY-clipMinY)/WIDTH;
            
            re=0;
            im=0;
            for(tm=0;tm<maxTm;tm++){
                re_=re*re-im*im+x;
                im_=2*re*im+y; 
                re=re_;
                im=im_;

                if(abs(re)+abs(im)>devJg){
                    
                    //bla_setPix(win,ix,iy,bla_rgb(0,255,255));
                    tm+=35;
                    //if(tm>maxTm)tm=maxTm;
                    //maxTm-=30;
                    int col=floor((254*(tm)/maxTm)/10)*10;
                    drawRect(pixSiz,pixSiz,ix,iy,bla_rgb(col,0,255-col));
                    break;
                }

            }
        }
    }
/*
    for(;;){
        if(kbhit()){
            ch=getch();
            break;
        }
    }*/

    bla_setPix(win,500,500,bla_rgb(255,255,255));
    switch(ch){
        case '1':
            //up
            clipMaxY-=DIFF;
            clipMinY-=DIFF;
            break;
        case 6:
            //down
            clipMaxY+=DIFF;
            clipMinY+=DIFF;
            break;
        case 7:
            //left
            clipMaxX-=DIFF;
            clipMinX-=DIFF;
            break;
        case 8:
            //right
            clipMaxX+=DIFF;
            clipMinX+=DIFF;
            break;   
        case '0':
            return 0; 
    }    
    
    //-----
    bla_flushAll(win);
	bla_wait(10);
	if (win->phase == 2) return 0;
    
    goto draw;
	
	return 0;
}

void drawRect(int xsiz, int ysiz, int x0, int y0, int c){
    for(int i=0;i<xsiz;i++){
        for(int j=0;j<ysiz;j++){
            bla_setPix(win,x0+i,y0+j,c);
        }
    }
    return;
}