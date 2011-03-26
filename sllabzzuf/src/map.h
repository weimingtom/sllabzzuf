#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "Tile.h"
#include "TileSheet.h"

class Map{
private:
	std::string mapFileLocation;
	std::map< int, std::vector<Tile*> > tileLayers;
	Tile* wall;
	int width, height, theme;
	TileSheet *tileSheet;
	SDL_Rect getTileScreenCoord(Tile* tile, SDL_Rect* camera);
	void drawBackground(SDL_Surface* screen);
	void blitTile(SDL_Surface* screen, SDL_Rect* camera, Tile* tile);

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
	bool loadMap(std::string filepath);
};
#endif // MAP_H_INCLUDED
