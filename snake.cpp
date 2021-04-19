#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

bool gameOver,print;
const int width = 20;
const int height = 20;
int x,y,fruitX,fruitY,score;
int tailX[100], tailY[100];
int nTail=0;
enum eDirection{ STOP = 0 , LEFT, RIGHT, UP, DOWN };
eDirection dir;

void setUp(){

    gameOver = false;
    dir = STOP;
    x = width/2;
    y = height/2;
    fruitX = rand()%width;
    fruitY = rand()%height;

}

void draw(){

    system("cls");
    for(int i=0; i<width+2; ++i)
        cout << "#";
    cout << endl;
    
    for(int i=0; i<height; ++i){
        for(int j=0; j<width+2; ++j){
            
            if(j==0)
                cout << "#";
            if(i==y && j==x)
                cout << "O";
            else if (i==fruitY && j==fruitX)
                cout << "F";    
            else{

                print = false;                

                for(int k=0; k<nTail; ++k){
                    
                    if( tailX[k]==j && tailY[k]==i){
                     
                        print = true;
                        cout << "o";
                    
                    }
                
                }
                
                if(!print)
                    cout << " ";

            }

            if (j == width-1)
                cout << "#";

        }

        cout << endl;

    }    

    for(int i=0; i<width+2; ++i)
        cout << "#";
    cout << endl;

    cout << "Score: " << score << endl;

}

void input(){

    if(kbhit()){

        switch (getch()){

            case 'a':
                dir = LEFT;
                break;
            
            case 'd':
                dir = RIGHT;
                break;

            case 'w':
                dir = UP;
                break;

            case 's':
                dir = DOWN;
                break;

            case 'x':
                gameOver = true;
                break;

        }
    
    }
}

void logic(){

    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    
    for(int i=1; i<nTail; ++i){
            
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
        
    }
    
    switch(dir){

        case LEFT:
            --x;
            break;
        case RIGHT:
            ++x;
            break;
        case DOWN:   
            ++y;
            break;
        case UP:
            --y;
            break;    
        default:
            break;
    
    }

    if( x>width-1 || x<0 || y>height-1 || y<0 )
        gameOver = true;
    for(int i=0; i<nTail ;++i)
        if(tailX[i]==x && tailY[i]==y)
            gameOver = true;
    if( x==fruitX && y==fruitY ){
        
        score += 10;
        fruitX = rand()%width;
        fruitY = rand()%height;    
        ++nTail;

    }

}

int main(){
    
    srand(time(NULL));

    setUp();
    
    while(!gameOver){
        
        draw();
        input();
        logic();
        Sleep(1000);
    
    }
    // can add sleep functions to slow down game
    return 0;

}