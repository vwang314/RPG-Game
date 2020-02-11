#include "map.h"

#include "globals.h"
#include "graphics.h"

/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 */
struct Map {
    HashTable* items;
    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
static Map map;
static Map maze;
static int active_map;

/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 */
static unsigned XY_KEY(int X, int Y) {
    // TODO: Fix me!
    return X + Y * map_width();
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    // TODO: Fix me!
    return key % map_width();
}

void maps_init()
{
    // TODO: Implement!    
    // Initialize hash table
    map.items = createHashTable( map_hash , 50 );
    // Set width & height
    map.w = 50;
    map.h = 50;
    maze.items = createHashTable( map_hash , 20);
    maze.w = 20;
    maze.h = 20;
}

Map* get_active_map()
{
    if(active_map == 0)
        return &map;
    else if (active_map == 1)
        return &maze;
    else
        return &map;
}

Map* set_active_map(int m)
{
    active_map = m;
    if(active_map == 0)
        return &map;
    else if(active_map == 1)
        return &maze;
    else
        return NULL;
}

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P', 'N', 'S', 'M', 'F', 'T'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    return get_active_map()->w;
}

int map_height()
{
    return get_active_map()->h;
}

int map_area()
{
    return map_width() * map_height();
}

MapItem* get_north(int x, int y)
{
    Map *temp = get_active_map();
    int key = XY_KEY(x,y-1); //north is y-1
    return (MapItem*) getItem(temp->items,key);
}

MapItem* get_south(int x, int y)
{
    Map *temp = get_active_map();
    int key = XY_KEY(x,y+1); //south is y+1
    return (MapItem*) getItem(temp->items,key);
}

MapItem* get_east(int x, int y)
{
    Map *temp = get_active_map();
    int key = XY_KEY(x+1,y); //east is x+1
    return (MapItem*) getItem(temp->items,key);
}

MapItem* get_west(int x, int y)
{
    Map *temp = get_active_map();
    int key = XY_KEY(x-1,y);//west is x-1
    return (MapItem*) getItem(temp->items,key);
}

MapItem* get_here(int x, int y)
{
    if(x > -1 && x < get_active_map()->w && y > -1 && y < get_active_map()->h)
        return (MapItem*) getItem(get_active_map()->items, XY_KEY(x, y));
    else
        return NULL;
}


void map_erase(int x, int y)
{
    deleteItem(get_active_map()->items, XY_KEY(x, y));
}

void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        w1->walkable = false;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
    }
}

void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_NPC(int x, int y, int* state)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = NPC;
    w1->draw = draw_NPC;
    w1->walkable = false;
    w1->data = state;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_stairs(int x, int y, int* map)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = STAIRS;
    w1->draw = draw_stairs;
    w1->walkable = true;
    w1->data = map;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_maze(int x, int y, const char* maze)
{
    for(int i = 0; i < 18*18; i++)
    {
        if(maze[i] == 'x')
            add_wall(x + i % 18, y + i / 18, HORIZONTAL, 1);
    }
}

void add_mball(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = MBALL;
    w1->draw = draw_mball;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_fake(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = FAKE;
    w1->draw = draw_treasure;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_treasure(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = TREASURE;
    w1->draw = draw_treasure;
    w1->walkable = false;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}


