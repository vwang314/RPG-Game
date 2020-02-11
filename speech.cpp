#include "speech.h"

#include "globals.h"
#include "graphics.h"
#include "hardware.h"

#define YELLOW 0xFFFF00

/**
 * Draw the speech bubble background.
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0
#define BOTTOM 1
static void draw_speech_line(const char* line, int which);

/**
 * Delay until it is time to scroll.
 */
static void speech_bubble_wait();

void draw_speech_bubble()
{
    uLCD.rectangle(0, 93, 127, 115, YELLOW);
    uLCD.filled_rectangle(1, 94, 126, 114, BLACK);
}

void erase_speech_bubble()
{
    uLCD.filled_rectangle(0, 93, 127, 115, BLACK);
    draw_border();
}

void draw_speech_line(const char* line, int which)
{
    uLCD.text_string((char*) line, 1, 12 + which, FONT_5X7, YELLOW);
}

void speech_bubble_wait()
{
    GameInputs in;

    Timer c; c.start();

    // Get inputs and display a flashing button
    // while waiting for action button to be pressed
    do {
        Timer t; t.start();

        int dc = c.read_ms();
        if (dc > 1000) {
            uLCD.filled_circle(120, 114, 3, DGREY);
            c.reset();
        }
        else if (dc > 500)
            uLCD.filled_circle(120, 114, 3, LGREY);

        in = read_inputs();

        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }while(in.b1);
}

void speech(const char* line1, const char* line2)
{
    draw_speech_bubble();
    draw_speech_line(line1, TOP);
    draw_speech_line(line2, BOTTOM);
    speech_bubble_wait();
    erase_speech_bubble();
}

void long_speech(const char* lines[], int n)
{
     int i;
    int length = (n % 2) ? n-1 : n;
    for(i = 0; i < length; i++)
        speech(lines[i++], lines[i]);
    if(length == n-1) speech(lines[n-1], "");
}
