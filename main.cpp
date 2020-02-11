// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"
#include <cstdlib>

int omni_pressed = 0;
int run = 0;
int difficulty;
int relocate;

#define START 1
#define GO    2
#define FOUND 3
#define END   4
static int state = START;

// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();
int main ();

/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
    int* state;
    // You can add other properties for the player here
} Player;

int next_to(int x, int y, int type)
{
    MapItem* up    = get_north(Player.x, Player.y);
    MapItem* left  = get_west(Player.x, Player.y);
    MapItem* right = get_east(Player.x, Player.y);
    MapItem* down  = get_south(Player.x, Player.y);
    MapItem* here  = get_here(Player.x, Player.y);
    int output = NULL; //if no tile exists, return null
    if(up->type == type)
        output = 1;
    else if(left->type == type)
        output = 2;
    else if(right->type == type)
        output = 3;
    else if(down->type == type)
        output = 4;
    return output;
}



/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define OMNI_MODE 7

int get_action(GameInputs inputs)
{
    if (!inputs.b2) {
        pc.printf("omni pressed \r\n");
        omni_pressed = !omni_pressed;
    }
    if (!inputs.b3) {
        pc.printf("run pressed \r\n");
        run = !run;
    }
    
    if (run){
        if (inputs.ay >= 0.05) return GO_LEFT;
        if (inputs.ay <= -0.05) return GO_RIGHT;
        if (inputs.ax <= -0.05) return GO_DOWN;
        if (inputs.ax >= 0.05) return GO_UP;
    }
    else {
        if (inputs.ay >= 0.15) return GO_LEFT;
        if (inputs.ay <= -0.15) return GO_RIGHT;
        if (inputs.ax <= -0.15) return GO_DOWN;
        if (inputs.ax >= 0.15) return GO_UP;
    }
    
    if (!inputs.b1) {
        pc.printf("action button \r\n");
        return ACTION_BUTTON;
    }
    
    if (!inputs.b4) {
        pc.printf("menu button \r\n");
        return MENU_BUTTON;
    }
        
    else return NO_ACTION;
}

/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define GAME_OVER 1
#define FULL_DRAW 2


int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    

    if (*((int*)Player.state) == END){
        Timer a; a.start();
    }    
    
    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    { 
        case GO_UP:
            MapItem* N=get_north(Player.px,Player.py); 
            if(N->type == STAIRS){
                pc.printf("stairs up \r\n");
                speaker.period(1.0/500.0);
                speaker = 0.15;
                wait(0.1);
                speaker = 0.0;
                wait(0.06);
                speaker.period(1.0/500.0);
                speaker = 0.15;
                wait(0.1);
                speaker = 0.0;
                int map_num = *((int*)N->data);
                set_active_map(map_num);
                if(map_num == 1) {
                    Player.x = 18;
                    Player.y = 9;
                }
                else if(map_num == 0) {
                    Player.x = 2;
                    Player.y = 12;
                }
                return FULL_DRAW;            
            }
            else if(N->walkable || omni_pressed){
                Player.y--;
                return FULL_DRAW;
            }
            else break;
        case GO_LEFT:   
            MapItem* W=get_west(Player.px, Player.py);
            if(W->type == STAIRS){
                speaker.period(1.0/500.0);
                speaker = 0.15;
                wait(0.1);
                speaker = 0.0;
                wait(0.06);
                speaker.period(1.0/500.0);
                speaker = 0.15;
                wait(0.1);
                speaker = 0.0;
                int map_num = *((int*)W->data);
                set_active_map(map_num);
                if(map_num == 1) {
                    Player.x = 18;
                    Player.y = 9;
                }
                else if(map_num == 0) {
                    Player.x = 2;
                    Player.y = 12;
                }
                return FULL_DRAW;          
            }
            else if(W->walkable || omni_pressed){
                Player.x--;
                return FULL_DRAW;
            }
            else break;           
        case GO_DOWN:   
            MapItem* S=get_south(Player.px,Player.py);
            if(S->type == STAIRS){
                speaker.period(1.0/500.0);
                speaker = 0.15;
                wait(0.1);
                speaker = 0.0;
                wait(0.06);
                speaker.period(1.0/500.0);
                speaker = 0.15;
                wait(0.1);
                speaker = 0.0;
                int map_num = *((int*)S->data);
                set_active_map(map_num);
                if(map_num == 1) {
                    Player.x = 18;
                    Player.y = 9;
                }
                else if(map_num == 0) {
                    Player.x = 2;
                    Player.y = 12;
                }
                return FULL_DRAW;        
            }
            else if(S->walkable || omni_pressed){
                Player.y++;
                return FULL_DRAW;
            }
            else break;
        case GO_RIGHT:  
            MapItem* E=get_east( Player.px, Player.py);
            if(E->type == STAIRS){
                speaker.period(1.0/500.0);
                speaker = 0.15;
                wait(0.1);
                speaker = 0.0;
                wait(0.06);
                speaker.period(1.0/500.0);
                speaker = 0.15;
                wait(0.1);
                speaker = 0.0;
                int map_num = *((int*)E->data);
                set_active_map(map_num);
                if(map_num == 1) {
                    Player.x = 18;
                    Player.y = 9;
                }
                else if(map_num == 0) {
                    Player.x = 2;
                    Player.y = 12;
                }
                return FULL_DRAW;      
            }
            else if(E->walkable || omni_pressed){
                Player.x++;
                return FULL_DRAW;
            }
            else break;
        case ACTION_BUTTON:   
            Timer t; t.start();          
            int npc = next_to(Player.x, Player.y, NPC);
            int mball = next_to(Player.x, Player.y, MBALL);
            int fake = next_to(Player.x, Player.y, FAKE);
            int treasure = next_to(Player.x, Player.y, TREASURE);
            int tX, tY;
                for(int c=0; c<50; c++){
                    for(int r=0; r<50; r++){
                        if( get_here(c,r)->type ==TREASURE){
                            tX=c;
                            tY=r;
                            break;
                        }
                    }
                }
            if( (get_here(tX,tY)->draw == draw_found) && (relocate>0) ){
                const char* lines[] = { "You found me     ",
                                        "Pikachu! And you ",
                                        "brought me the   ",
                                        "master ball!     "};
                long_speech(lines, 4);
                return GAME_OVER;
            }
            else if ( (get_here(tX,tY)->draw == draw_found) && (relocate<1) ){
                pc.printf("found first time \r\n");
                map_erase(tX,tY);
                const char* lines[] = { "Sorry buddy, I'm ",
                                        "still chasing    ",
                                        "this Pokemon.    "};
                long_speech(lines, 3);
                add_treasure(( rand()%48)+1, (rand()%48)+1);
                relocate++;
                return FULL_DRAW;
            }           
            else if (npc){
                MapItem* x;
                if(npc==1) {
                    pc.printf("NPC found up\r\n");
                    x = get_north(Player.x, Player.y);
                    draw_exclMark(59,35);
                }  
                if(npc==2) {
                    pc.printf("NPC found left\r\n");
                    x = get_west(Player.x, Player.y);
                    draw_exclMark(47,47);
                }
                if(npc==3) {
                    pc.printf("NPC found right\r\n");
                    x = get_east(Player.x, Player.y);
                    draw_exclMark(69,47);
                }
                if(npc==4) {
                    pc.printf("NPC found down\r\n");
                    x = get_south(Player.x, Player.y);
                    draw_exclMark(58,84);
                }
                if(x->data && Player.has_key == true && *((int*)x->data) == GO) {
                    state = FOUND;
                    x->data = &state;
                }
            
                if(x->data && *((int*)x->data) == START) {
                    const char* lines[] = { "Hi Pikachu, it's ",
                                            "me, Prof Oak.    ",
                                            "If you head down ",
                                            "from here, you   ",
                                            "should see stairs",
                                            "leading to a room",
                                            "with the item Ash",
                                            "wants.  "};
                    long_speech(lines, 8);

                    // set the NPC to say the next lines
                    state = GO;
                    x->data = &state;
                    Player.state = &state;
                    static int map2 = 1;
                    add_stairs(1,12, &map2);
                    return FULL_DRAW;
                }
                else if(x->data && *((int*)x->data) == GO) {
                    const char* lines[] = { "What are you     ",
                                            "waiting for?     ",
                                            "Ash really       ",
                                            "wants that item  "};
                    long_speech(lines, 4);

                    return FULL_DRAW;
                }
                else if(x->data && *((int*)x->data) == FOUND) {
                    const char* lines[] = { "You found it!    ",
                                            "Now go find Ash. ",
                                            "You know how he  ",
                                            "is, always off   ",
                                            "adventuring.     ",
                                            "He's in the grass",
                                            "catching them all"};
                    long_speech(lines, 7);
                    state = END;
                    x->data = &state;
                    Player.state = &state;
                    t.stop(); 
                    srand(t.read_ms());
                    add_treasure(( rand()%48)+1, (rand()%48)+1);
                    return FULL_DRAW;
                }
                
                else if(x->data && *((int*)x->data) == END) {
                    const char* lines[] = { "Hurry. Ash is    ",
                                            "counting on you! "};
                    long_speech(lines, 2);
                    return FULL_DRAW;
                }
            }
            else if(mball==2) {
                pc.printf("mball found left\r\n");
                map_erase(1,12);
                speaker.period(1.0/1500.0);
                speaker = 0.27;
                wait(0.06);
                speaker = 0.0;
                wait(0.06);
                speaker.period(1.0/1500.0);
                speaker = 0.27;
                wait(0.06);
                speaker = 0.0;
                wait(0.06);
                speaker.period(1.0/1500.0);
                speaker = 0.27;
                wait(0.06);
                speaker = 0.0;
                wait(0.06);
                speaker.period(1.0/3000.0);
                speaker = 0.3;
                wait(0.1);
                speaker = 0.0;
                Player.has_key=1;
                state = FOUND;
                Player.state = &state; 
                return FULL_DRAW;   
            }
            else if(fake){
                pc.printf("fake treasure \r\n");
                const char* lines[] = { "Ash isn't in here"};
                    long_speech(lines, 1);
                return FULL_DRAW;
            }
                        
            else if (treasure) {
                pc.printf("found treasure \r\n");
                get_here(tX,tY)->draw = draw_found;
                return FULL_DRAW;
            }    
                
            else if( (Player.has_key==1) && (*((int*)Player.state) == END) ){
                pc.printf("activate sonar \r\n");
                int dx = Player.x - tX;
                int dy = Player.y - tY;
                if( (dx>0) && (dy>0) ){
                    const char* lines[] = { "Ash is to the    ",
                                            "northwest        "};
                    long_speech(lines, 2);
                    return FULL_DRAW;
                }
                if( (dx>0) && (dy<0) ){
                    const char* lines[] = { "Ash is to the    ",
                                            "southwest        "};
                    long_speech(lines, 2);
                    return FULL_DRAW;
                }
                if( (dx<0) && (dy>0) ){
                    const char* lines[] = { "Ash is to the    ",
                                            "northeast        "};
                    long_speech(lines, 2);
                    return FULL_DRAW;
                }
                if( (dx<0) && (dy<0) ){
                    const char* lines[] = { "Ash is to the    ",
                                            "southeast        "};
                    long_speech(lines, 2);
                    return FULL_DRAW;
                }
                if( (dx==0) && (dy>0) ){
                    const char* lines[] = { "Ash is to the    ",
                                            "north        "};
                    long_speech(lines, 2);
                    return FULL_DRAW;
                }
                if( (dx==0) && (dy<0) ){
                    const char* lines[] = { "Ash is to the    ",
                                            "south        "};
                    long_speech(lines, 2);
                    return FULL_DRAW;
                }
                if( (dx>0) && (dy==0) ){
                    const char* lines[] = { "Ash is to the    ",
                                            "west        "};
                    long_speech(lines, 2);
                    return FULL_DRAW;
                }
                if( (dx<0) && (dy==0) ){
                    const char* lines[] = { "Ash is to the    ",
                                            "east        "};
                    long_speech(lines, 2);
                    return FULL_DRAW;
                }
                    
            }
            else break;
            
        case MENU_BUTTON: 
            GameInputs inputs;
                uLCD.filled_rectangle(0, 0, 128, 128, BLACK);
                if(*((int*)Player.state) == START){
                    uLCD.text_string("MENU: \n Status: \n Talk to \n Prof Oak \n ", 1, 4, FONT_7X8, WHITE);
                    uLCD.locate(0,2);
                    uLCD.printf("X:%d", Player.x);
                    uLCD.locate(4,2);
                    uLCD.printf("Y:%d", Player.y);
                    while(1){
                        inputs = read_inputs();
                        if (!inputs.b1){
                            return FULL_DRAW;    
                        }
                    }
                }
                if(*((int*)Player.state) == GO){
                    uLCD.text_string("MENU: \n STATUS: \n Find master ball \n ", 1, 4, FONT_7X8, WHITE);
                    uLCD.locate(0,2);
                    uLCD.printf("X:%d", Player.x);
                    uLCD.locate(4,2);
                    uLCD.printf("Y:%d", Player.y);
                    while(1){
                        inputs = read_inputs();
                        if (!inputs.b1){
                            return FULL_DRAW;    
                        }
                    }
                }
                if(*((int*)Player.state) == FOUND){
                    uLCD.text_string("MENU: \n STATUS: \n Talk to \n Prof Oak \n ", 1, 4, FONT_7X8, WHITE);
                    uLCD.locate(0,2);
                    uLCD.printf("X:%d", Player.x);
                    uLCD.locate(4,2);
                    uLCD.printf("Y:%d", Player.y);
                    while(1){
                        inputs = read_inputs();
                        if (!inputs.b1){
                            return FULL_DRAW;    
                        }
                    }
                }
                if(*((int*)Player.state) == END){
                    uLCD.text_string("MENU: \n STATUS: \n Find Ash \n ", 1, 4, FONT_7X8, WHITE);
                    uLCD.locate(0,2);
                    uLCD.printf("X:%d", Player.x);
                    uLCD.locate(4,2);
                    uLCD.printf("Y:%d", Player.y);
                    while(1){
                        inputs = read_inputs();
                        if (!inputs.b1){
                            return FULL_DRAW;    
                        }
                    }
                }
                
            
        default:        break;
    }
    return NO_RESULT;
}

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
void draw_game(int init)
{
    // Draw game border first
    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
                draw_player(u, v, run);
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }

    // Draw status bars    
    draw_upper_status(Player.x, Player.y);
    draw_lower_status(Player.has_key);
}


/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion. Note: using the similar
 * procedure you can init the secondary map(s).
 */
void init_main_map()
{
    // Create maze
    Map* map = set_active_map(1);
    pc.printf("set active map \r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    const char* maze1 =
"      xxxxxxxxxxx "
"xx xx          xx "
"xx xx xxxxxxxx    "
"   xx x        xx "
"xxxxx x xxxxxxxxx "
"      x        xx "
"xxxxxxxxxxxxxx    "
"               xx "
"xxxxxxxxxxxxxxxx  "
"         xxxxxxx s"
"xxxxxxxx xxxxxxx x"
"            xxxx x"
"xxxxxxxxxxx   xx x"
"           xx    x"
"xxxxxxxxxx    xx x"
"           xxxxx x"
"xxxxxxxx xxxxxxx x"
"         xxxxxxx x";
    add_maze(1,1,maze1);
    add_mball(1,12);
    
    pc.printf("add walls \r\n");
    static int map1 = 0;
    add_stairs(18, 10, &map1);
    pc.printf("print map \r\n");
    print_map();
    
    
    
    pc.printf("start init_main_map \r\n");
    // "Random" plants
    map = set_active_map(0);
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }
    pc.printf("plants\r\n");
        
    pc.printf("Adding walls!\r\n");
    add_wall(0,             0,              HORIZONTAL, map_width());
    add_wall(0,             map_height()-1, HORIZONTAL, map_width());
    add_wall(0,             0,              VERTICAL,   map_height());
    add_wall(map_width()-1, 0,              VERTICAL,   map_height());

    add_NPC(3,3, &state);
    add_fake(15,32);
    add_fake(6,40);
    add_fake(42,16);
    add_fake(37,25);
    if (difficulty){
        add_fake(23,7);
        add_fake(10,42);
        add_fake(30,5);
        add_fake(48,23);
    }
    print_map();
}

/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */

 
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    
    uLCD.filled_rectangle(0, 0, 128, 128, BLACK);
    uLCD.text_string("Choose dificulty \n >B1 - easy \n >B2 - hard", 1, 4, FONT_7X8, WHITE);
    GameInputs inputs;
        while(1){
            inputs = read_inputs();
            if (!inputs.b1){
                difficulty=0;
                relocate=0;  
                break;  
            }
            if (!inputs.b2){
                difficulty=1;
                relocate=-1;
                break;
            }
        }
    
    //Start Screen
    pc.printf("pre start screen \r\n");
    uLCD.filled_rectangle(0, 0, 128, 128, BLACK);
    draw_Start();
    pc.printf("post start screen \r\n");


    // Initialize the maps
    maps_init();
    init_main_map();
    
    // Initialize game state
    set_active_map(0);
    Player.x = Player.y = 5;
    Player.state = &state;

    // Initial drawing
    draw_game(true);

    // Main game loop
    while(1)
    {
        // Timer to measure game update speed
        Timer t; t.start();
        
        // Actuall do the game update:
        // 1. Read inputs        
        GameInputs in = read_inputs();
        // 2. Determine action (get_action)  
        int action = get_action(in);      
        // 3. Update game (update_game)
        int result = update_game(action);
        // 3b. Check for game over
        if (result == 1){ break; }
        // 4. Draw frame (draw_game)
        draw_game(result);
        
        // 5. Frame delay
        t.stop();
        int dt = t.read_ms();
        if (dt < 100) wait_ms(100 - dt);
    }
    draw_game_over(1);
}
