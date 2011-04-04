#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Tile.h"
#include "TileSheet.h"
//#include "block.h"

class Map{
private:
	std::string mapFileLocation;
	std::map< int, std::vector<Tile*> > tileLayers;
	//std::vector<Block*> blocks;
	Tile* wall;
	int width, height, theme;
	TileSheet *tileSheet;
	SDL_Rect getTileScreenCoord(Tile* tile, SDL_Rect* camera);
	void drawBackground(SDL_Surface* screen);
	void blitTile(SDL_Surface* screen, SDL_Rect* camera, Tile* tile);
	bool finished;

public:
	Map();
	~Map();
	std::vector<Tile*> get_Tiles(int layer);
	std::map< int, std::vector<Tile*> > get_Layers();
	Tile* get_Tile(int layer, int x, int y);
	Tile* get_Tilepx(int layer, int x, int y);
	int get_Width();
	int get_Height();
	int get_Widthpx();
	int get_Heightpx();
	int get_theme();
	void set_theme(int th);
	void set_Width(int newWidth);
	void set_Height(int newHeight);
	void set_TileSheet(std::string filename);
	void drawMap(SDL_Surface* screen, SDL_Rect* camera);
	void drawMapSlice(SDL_Surface* screen, SDL_Rect* camera, int topLayer, int bottomLayer = 0);
	void drawBlocks(SDL_Surface* screen, SDL_Rect* camera);
	void rotateRight();
	void rotateUp();
	void rotateLeft();
	void rotateTileUp(Tile* tile);
	void rotateTileRight(Tile* tile);
	void rotateTileLeft(Tile* tile);
	bool loadMap(std::string filepath);
	//direction: 0= up, 1=right, 2=down, 3=left
	bool solid_collision(int direction, int x, int y, int w=32, int h=32);
	bool tile_test(int type, int tile_x, int tile_y, int x, int y, int w, int h);
	bool is_done(int x, int y);
	void finish_map();
};
#endif // MAP_H_INCLUDED
