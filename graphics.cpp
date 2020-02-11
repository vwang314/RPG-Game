#include "graphics.h"
#include "hardware.h"
#include "globals.h"



void draw_player(int u, int v, int key)
{
    //uLCD.filled_rectangle(u, v, u+11, v+11, RED);
    if (key==1){
        char pikachu[122] ="xxxxxxxxxxxxxxYxYxxYxxYxYxxxYxxxxxxxYxxxxxYxYxYxPYPxxxYxYxxYYYYYxxxxxxPYPxxYxxYxxxxxYxxYxxYxYxYxYxxxYxxxxxxxxxxYxYxxxxxxx";
        draw_img(u,v,pikachu);//test drawing image
    }
    else {
        char pikachu[122] ="XXxxxxxxxXXxYYxxxxxYYxxxYYxxxYYxxxYYYYYYYYYxYYYXYYYXYYYYYYXYYYXYYYYYYYYYYYYYYYRYYYYYYYRYYRYXYYYXYRYxYYYXXXYYYxxxYYYYYYYxx";
        draw_img(u,v,pikachu);//test drawing image
    }
}

#define YELLOW   0xFFFF00
#define PBLUE    0x4B73FF
#define BROWN    0xD2691E
#define DIRT     BROWN
#define WHITE    0xFFFFFF
#define TREE1    0x9EE177
#define TREE2    0x7FC25B
#define TREE3    0x6AA443
#define GROUND   0xFFCFB2
#define FACE     0xFFFF82
#define HAIR     0xBBA26D
#define EYEBROW  0x423D37
#define PURPLE   0x603B89
#define PINK     0xB32758
void draw_img(int u, int v, const char* img)
{
    int colors[11*11];
    for (int i = 0; i < 11*11; i++)
    {
        if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'Y') colors[i] = YELLOW;
        else if (img[i] == 'G') colors[i] = GREEN;
        else if (img[i] == 'D') colors[i] = DIRT;
        else if (img[i] == '5') colors[i] = LGREY;
        else if (img[i] == '3') colors[i] = DGREY;
        else if (img[i] == 'A') colors[i] = TREE1;
        else if (img[i] == 'B') colors[i] = TREE2;
        else if (img[i] == 'C') colors[i] = TREE3;
        else if (img[i] == 'X') colors[i] = BLACK;
        else if (img[i] == 'F') colors[i] = FACE;
        else if (img[i] == 'H') colors[i] = HAIR;
        else if (img[i] == '1') colors[i] = EYEBROW;
        else if (img[i] == 'W') colors[i] = WHITE;
        else if (img[i] == 'R') colors[i] = RED;
        else if (img[i] == 'P') colors[i] = PURPLE;
        else if (img[i] == 'K') colors[i] = PINK;
        else colors[i] = BLACK;
    }
    uLCD.BLIT(u, v, 11, 11, colors);
    wait_us(250); // Recovery time!
}

void draw_Start()
{
    char screen[1666]="xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxPPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxPPPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxPPYPPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxPPPPxxxxxxxxxxxxPxPxxxxxPPYYPPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxPPPPPPPPPxxxxxxxPPPPPPPxxxxPPPPxxxxxxxPPPPPxxxxxxxxxxxxxxxxxxxPPPPPYYYYPPPxxxxxPPPPPPPPPxxPPPPPPPxPPPPPPPPPxxxxPPPxxxxxxxxxxPPPPYYYYYYYYYPPxxxPPYYYYPYYYPPPYYYYPPPPYYYPYYYPxxxxPPPPPPPxxxxxxxPPYYYYYYYYYYYPxxxPPPYYYYYYYPPYYYYYYYPPYYYYYYYPxxxxPPYYYPPPPPPPxxPPYYYYYYPPYYYPxxxxPPYYYYYYYPYYPxPYYPPPYYYYYYYPxxxPPPYYYYPPYPPPPxPPYYYYYYPxPYYPPPPPPPYYYYYYPYYYPPYYPPPPYYYYYYYPPPPPPPYYYYPPYYYPxxxPPPYYYYPPPYYPPPYYPPYYYYYPPYYYPYYPPPPYYYYYYYYYPYYYYYPYYYPPYYYPxxxxxPYYYYPPPYPPYPYYYPYYYYYPPPYYYYYYYYPPYYYYYYYPYYPYYYYPYYYYYYYPxxxxxPPYYYYPYPPYPPYYYYPYYYYYYPYYYYYYYYPPYYYYYYYPYYPYYYYPYYYYYYPxxxxxxxPYYYYYPPPYYPPPYYPYYYYYYYPYYYYYYPPPYYPYYYYYYYPPPYYPYYYYYYPxxxxxxxPPYYYPPxYYYYYYYYPYYPPYYYYPPPPPPxPYYYPYYYYPYYYYYYYPYYYYYYPxxxxxxxPPYYYPPPYYYYYYYPYYYPxPPYYYYPxxxxPYYYPPPYYPYYYYYYPYYYYYYPPxxxxxxxxPYYYYPPYYYYYYPxYYYPxxxPPYYPxxxxPPPPPPPYYPPYYYYPPYPYYYYPxxxxxxxxxPPYYYPxPPYYYPxPYYYPxxxxxPPPxxxxxxxxxxPPYYPPPPPPYYPYYYYPxxxxxxxxxPPYYYPxxPPPPxxPPPPxxxxxxxxPxxxxxxxxxxxPPPPPxxPPYYPYYYYPxxxxxxxxxxPYYYPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxPPxxxPPPPYYYPxxxxxxxxxxxPPYPPPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxPYYYPxxxxxxxxxxxPPPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxPPPPPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx ";
    pc.printf("load colors \r\n");
    int colors[26*64];
    pc.printf("pre loop \r\n");
    for (int i = 0; i <26*64 ; i++)
    {
        if (screen[i] == 'Y') colors[i] = YELLOW;
        else if (screen[i] == 'P') colors[i] = PBLUE;
        else colors[i] = BLACK;
    }
    pc.printf("post loop \r\n");
    uLCD.BLIT(32, 51, 64, 26, colors);
    wait_us(250); // Recovery time!     
}

void draw_NPC(int u, int v)
{
    char NPC[122]="xxxxxxxHHxxxHHHHHHHHHHxHFFFHFFFHxxH11FFF11HxFFFFFFFFFFFFFFXFFFXFFFxFFFFFFFFFxxFFXFFFXFFxxFFFXXXFFFxxxxFFFFFxxxxxxxFFFxxxx";  //prof oak
    draw_img(u,v,NPC);
}

void draw_exclMark(int u, int v)
{
    char excl[122]="xxxxxxxxxxxxxxxRRRxxxxxxxRRRRRxxxxxxRRRRRxxxxxxRRRRRxxxxxxxRRRxxxxxxxxRRRxxxxxxxxxxxxxxxxxxxRRRxxxxxxxxRRRxxxxxxxxxxxxxxx";  
    draw_img(u,v,excl);
    speaker.period(1.0/3000.0);
    speaker = 0.3; //50% duty cycle - max volume
    wait(.1);
    speaker=0.0; // turn off audio    
    wait_ms(150);
    draw_nothing(u,v);      
}

void draw_stairs(int u, int v)
{
    char stairs[122]="5xxxxxxxxxx5xxxxxxxxxx555xxxxxxxx555xxxxxxxx55555xxxxxx55555xxxxxx5555555xxxx5555555xxxx555555555xx555555555xx55555555555";
    draw_img(u,v,stairs);
}

void draw_mball(int u, int v)
{
    char mball[122]="xxxKPPPKxxxxxKPWPWPKxxxPPWPWPWPPxPPPPPPPPPPPPPPP555PPPP5555WWW5555WWWW5W5WWWWWWWWW5WWWWWxWWWWWWWWWxxxWWWWWWWxxxxxWWWWWxxx";
    draw_img(u,v,mball);
}

void draw_treasure(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
}

void draw_found(int u, int v)
{
    char found[122]="xxxxRRRxxxxxxxRRRRRxxxxxRRRxRRRxx33FxFFFxF33x3FFFFFFF3xxxxFFxFFxxxxxxxFFFxxxxxxxxxxxxxxxxxxxxxxxxxxBBBBBBBBBBBBBBBBBBBBBB";
    draw_img(u,v,found);
}

void draw_nothing(int u, int v)
{
    // Fill a tile with blackness
    uLCD.filled_rectangle(u, v, u+10, v+10, BLACK);
}

void draw_wall(int u, int v)
{
    uLCD.filled_rectangle(u, v, u+10, v+10, BROWN);
}

void draw_plant(int u, int v)
{
    //uLCD.filled_rectangle(u, v, u+10, v+10, GREEN);
    char tree[122] = "xxxxxAxxxxxxxxxAAAxxxxxxxxAAAxxxxxxxBAAABxxxxxBBBBBBBxxxxCBBBBBCxxxxCCBBBCCxxxxxCCCCCxxxxxxxx3xxxxxxxxxx3xxxxxxxxxxxxxxxx";
    draw_img(u,v,tree);
}

void draw_upper_status(int player_x, int player_y)
{
    // Draw bottom border of status bar
    uLCD.line(0, 9, 127, 9, GREEN);
    
    // Add other status info drawing code here
    char posString[16];
    sprintf(posString, "Position: %u, %u ", player_x, player_y);
    uLCD.text_string(posString, 0, 0, FONT_5X7, YELLOW);
}

void draw_lower_status(int hasKey)
{
    // Draw top border of status bar
    uLCD.line(0, 118, 127, 118, GREEN);
    
    // Add other status info drawing code here
    if(hasKey)
        draw_mball(5, 119);
}

void draw_border()
{
    uLCD.filled_rectangle(0,     9, 127,  14, WHITE); // Top
    uLCD.filled_rectangle(0,    13,   2, 114, WHITE); // Left
    uLCD.filled_rectangle(0,   114, 127, 117, WHITE); // Bottom
    uLCD.filled_rectangle(124,  14, 127, 117, WHITE); // Right
}

void draw_game_over(int u)
{
    // Cover map
    uLCD.filled_rectangle(3, 15, 126, 113, BLACK);

    // Write message
    uLCD.text_string("GAME", 7, 5, FONT_12X16, YELLOW);
    uLCD.text_string("OVER", 7, 6, FONT_12X16, YELLOW);
    if (u){
        uLCD.text_string("You win!", 6, 8, FONT_5X7, YELLOW);
        uLCD.text_string("Congratulations!", 2, 9, FONT_5X7, YELLOW);
    }
}


