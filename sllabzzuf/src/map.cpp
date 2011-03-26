#include "map.h"

Map::Map(){
	height = 0;
	width = 0;
	mapFileLocation = "";
	tileSheet = new TileSheet();
	theme=0;
}


bool Map::loadMap(std::string filepath){
	std::cout << "Loading map with filepath " << filepath << "\n";
	std::ifstream mapFile(filepath.c_str(), std::ifstream::in);

	if(mapFile == NULL && filepath != "data/newgame.map"){
		mapFileLocation = "data/newgame.map";
		std::cout << " Map filepath was invalid loading default.map.\n";
		if(loadMap(mapFileLocation)){
			mapFile.close();
			return true;
		}
	}
	if(mapFile != NULL){
		std::cout << "Loading map " << filepath << "\n";
		mapFileLocation = filepath;
		tileLayers.clear(); //TODO: clear layers of tiles correctly.

		int my_type;
		int layer;
		std::vector<Tile*> currentTiles;
		mapFile >> theme;
		mapFile >> width; //in tiles
		mapFile >> height; //in tiles

		while(mapFile.good()){
			mapFile >> layer;

			for (int y=0; y<height; y++){
				for(int x=0; x<width; x++){
					mapFile >> my_type;
					if( mapFile.fail() || my_type<0 || my_type >55 ){
						mapFile.close();
					}
					currentTiles.push_back(new Tile(x,y, my_type)); // add the tile to the map;
				}
			}

			tileLayers.insert(std::pair< int,std::vector<Tile*> >(layer, currentTiles));
			currentTiles.clear();
			std::cout << "Completed loading layer " << layer << " from .map\n";

		}

		wall = new Tile(-1,-1, 1);
		mapFile.close();
        std::cout << "loadMap finished\n";
		return true;
	}

	std::cout << "Loading default.map failed\n";
	mapFile.close();
	return false;
}

Map::~Map(){

}

std::vector<Tile*> Map::get_Tiles(int layer){
	return tileLayers.find(layer)->second;
}

Tile* Map::get_Tile(int layer, int x, int y){
	if(x < 0 || y < 0 || y >= height || x >= width)
			return NULL;
	return tileLayers.find(layer)->second[x+y*width];
}

Tile* Map::get_Tilepx(int layer, int x, int y){
	return get_Tile(layer, x/32, y/32);
}

int Map::get_Width(){
	return width;
}

int Map::get_Height(){
	return height;
}
int Map::get_theme(){
    return theme;
}
void Map::set_theme(int th){
    theme=th;
}
int Map::get_Widthpx(){
	return width*32;
}
int Map::get_Heightpx(){
	return height*32;
}

/**
 * Draw the background using the bottom right corner of the tileSheet (2x2 squares across the entire background)
 */
void Map::drawBackground(SDL_Surface* screen){
		SDL_Rect tileLocation;
		tileLocation.h = 64;
		tileLocation.w = 64;
		for(int x = 0; x < this->width/2; x++){
			tileLocation.x = x*64;
			for(int y = 0; y < this->height/2; y++){
				tileLocation.y = y*64;
				SDL_BlitSurface( tileSheet->get_Surface(), &tileSheet->getBackgroundTile(), screen, &tileLocation);
			}
		}
}

/**
 * Draws the map onto the screen by blitting visible tiles starting from the lowest layer first onto the screen surface.
 */
void Map::drawMap(SDL_Surface* screen, SDL_Rect* camera){
	drawBackground(screen);
	for(std::map< int,std::vector<Tile*> >::iterator layer = tileLayers.begin(); layer != tileLayers.end(); layer++){
		for(std::vector<Tile*>::iterator tile = layer->second.begin(); tile != layer->second.end(); tile++){
			blitTile(screen, camera, *tile);
		}
	}
}

/**
 * decide of the tile should be blitted and if so blit it to the screen.
 */
void Map::blitTile(SDL_Surface* screen, SDL_Rect* camera, Tile* tile){
	if(	(tile->get_box()->x*32 >= camera->x-32 				//if the tile is within the left side of the screen
		&& tile->get_box()->x*32 < camera->x+camera->w)				//if the tile is within the right side of the screen
		&& (tile->get_box()->y*32 >= camera->y-32 			//if the tile is within the top of the screen
		&& tile->get_box()->y*32 < camera->y+camera->h)){ 			//if the tile is within the bottom of the screen

		//draw the tile to the screen
		SDL_BlitSurface( tileSheet->get_Surface(), &tileSheet->getTileFromSheet(tile), screen, &getTileScreenCoord(tile,camera));
	}
}

/**
 * Get the screen coordinates of a tile given the tile and the current camera.
 */
SDL_Rect Map::getTileScreenCoord(Tile* tile, SDL_Rect* camera){
	SDL_Rect screenCoord;
	screenCoord.x = tile->get_box()->x*32 - camera->x;
	screenCoord.y = tile->get_box()->y*32 - camera->y;
	return screenCoord;
}
void Map::set_TileSheet(std::string filename){
	tileSheet->loadSheet(filename);
}