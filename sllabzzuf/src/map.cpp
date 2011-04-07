#include "map.h"
#include <algorithm>

Map::Map(){
	height = 0;
	width = 0;
	mapFileLocation = "";
	tileSheet = new TileSheet();
	theme=0;
	finished=false;
}

void Map::drawBlocks(SDL_Surface* screen, SDL_Rect* camera){
    for(int i=blocks.begin(); i<blocks.end(); i++){
        block->draw(screen, camera);
        }
    }
}
std::vector<Block*> Map::get_blocks(){
    return blocks;
}
bool Map::loadMap(std::string filepath){
	std::cout << "Loading map " << filepath << "\n";
	std::ifstream mapFile(filepath.c_str(), std::ifstream::in);

	if(mapFile == NULL && filepath != "data/ice1.map"){
		mapFileLocation = "data/ice1.map";
		std::cout << " Map filepath was invalid loading ice1.map.\n";
		if(loadMap(mapFileLocation)){
			mapFile.close();
			return true;
		}
	}
	if(mapFile != NULL){
		std::cout << "ifstream successfull, loading tiles. " << filepath << "\n";
		mapFileLocation = filepath;
		tileLayers.clear(); //TODO: clear layers of tiles correctly.

		int my_type;
		int layer;
		int object;
		int object_x;
		int object_y;
		int num_objects;
		std::vector<Tile*> currentTiles;
		mapFile >> theme;
		mapFile >> width; //in tiles
		mapFile >> height; //in tiles
		mapFile >> num_objects

        for(int i=0; i<num_objects; i++){
            mapFile >> object;
            mapFile >> object_x;
            mapFile >> object_y;
            if(object==0)
            blocks.push_back(new Block(object_x*32, object_y*32));

        }
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
void Map::rotateRight(){
      int type = width;
      width = height;
      height = type;
	for(std::map< int,std::vector<Tile*> >::iterator layer = tileLayers.begin(); layer != tileLayers.end(); layer++){
		for(std::vector<Tile*>::iterator tile = layer->second.begin(); tile != layer->second.end(); tile++){
		    Tile *current= *tile;
			type= current->get_type();
			switch(type){
			case 3: type=49; break;
			case 4: type=42; break;
			case 5: type=35; break;
			case 6: type=28; break;
			case 7: type=21; break;
			case 8: type=14; break;
			case 9: type=7; break;
			case 10: type=17; break;
			case 11: type=18; break;
			case 12: type=11; break;
			case 13: type=10; break;
            case 14: type=22; break;
            case 16: type=8; break;
            case 17: type=20; break;
			case 18: type=19; break;
			case 19: type=12; break;
			case 20: type=13; break;
            case 21: type=23; break;
			case 22: type=16; break;
			case 23: type=9; break;
			case 24: type=50; break;
			case 25: type=43; break;
			case 26: type=36; break;
			case 27: type=29; break;
			case 28: type=24; break;
			case 29: type=3; break;
			case 30: type=32; break;
            case 31: type=30; break;
            case 32: type=33; break;
            case 33: type=31; break;
            case 34: type=41; break;
			case 35: type=25; break;
			case 36: type=4; break;
			case 41: type=34; break;
			case 42: type=26; break;
			case 43: type=5; break;
			case 49: type=27; break;
			case 50: type=6; break;
			default: break;
			}
			rotateTileRight(*tile);
            current->set_type(type);
            *tile = current;
		}
		std::vector<Tile*> holding_vector;
		for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                holding_vector.push_back(layer->second.at((height- i - 1 ) + j*height));
            }
		}
		layer->second.clear();
		for(int k=0; k<holding_vector.size(); k++){
        layer->second.push_back(holding_vector.at(k));
		}
		//reverse(layer->second.begin(), layer->second.end());
	}
}
void Map::rotateTileRight(Tile* tile){
    	int x=tile->get_box()->y;
		int y=tile->get_box()->x;
		y=(height)-y-1;
		tile->set_x(x);
		tile->set_y(y);
}
void Map::rotateLeft(){
      int type = width;
      width = height;
      height = type;
	for(std::map< int,std::vector<Tile*> >::iterator layer = tileLayers.begin(); layer != tileLayers.end(); layer++){
		for(std::vector<Tile*>::iterator tile = layer->second.begin(); tile != layer->second.end(); tile++){
		    Tile *current= *tile;
			type= current->get_type();
			switch(type){
			case 3: type=29; break;
			case 4: type=36; break;
			case 5: type=43; break;
			case 6: type=50; break;
			case 7: type=9; break;
			case 8: type=16; break;
			case 9: type=23; break;
			case 10: type=13; break;
			case 11: type=12; break;
			case 12: type=19; break;
			case 13: type=20; break;
            case 14: type=8; break;
            case 16: type=22; break;
            case 17: type=10; break;
			case 18: type=11; break;
			case 19: type=18; break;
			case 20: type=17; break;
            case 21: type=7; break;
			case 22: type=14; break;
			case 23: type=21; break;
			case 24: type=28; break;
			case 25: type=35; break;
			case 26: type=42; break;
			case 27: type=49; break;
			case 28: type=6; break;
			case 29: type=27; break;
			case 30: type=31; break;
            case 31: type=33; break;
            case 32: type=30; break;
            case 33: type=32; break;
            case 34: type=41; break;
			case 35: type=5; break;
			case 36: type=26; break;
			case 41: type=34; break;
			case 42: type=4; break;
			case 43: type=25; break;
			case 49: type=3; break;
			case 50: type=24; break;
			default: break;
			}
			rotateTileLeft(*tile);
            current->set_type(type);
            *tile = current;
		}
		std::vector<Tile*> holding_vector;
		for(int i=0; i<height; i++){
            for(int j=0; j<width; j++){
                holding_vector.push_back(layer->second.at(i + (width - j -1)*height));
            }
		}
		layer->second.clear();
		for(int k=0; k<holding_vector.size(); k++){
        layer->second.push_back(holding_vector.at(k));
		}
		//reverse(layer->second.begin(), layer->second.end());
	}
}
void Map::rotateTileLeft(Tile* tile){
    	int x=tile->get_box()->y;
		int y=tile->get_box()->x;
		x=(width)-x-1;
		tile->set_x(x);
		tile->set_y(y);
}
void Map::rotateUp(){
    int type;
	for(std::map< int,std::vector<Tile*> >::iterator layer = tileLayers.begin(); layer != tileLayers.end(); layer++){
		for(std::vector<Tile*>::iterator tile = layer->second.begin(); tile != layer->second.end(); tile++){
		    Tile *current= *tile;
			type= current->get_type();
			switch(type){
			case 3: type=27; break;
			case 4: type=26; break;
			case 5: type=25; break;
			case 6: type=24; break;
			case 7: type=23; break;
			case 8: type=22; break;
			case 9: type=21; break;
			case 10: type=20; break;
			case 11: type=19; break;
			case 12: type=18; break;
			case 13: type=17; break;
            case 14: type=16; break;
            case 16: type=14; break;
            case 17: type=13; break;
			case 18: type=12; break;
			case 19: type=11; break;
			case 20: type=10; break;
            case 21: type=9; break;
			case 22: type=8; break;
			case 23: type=7; break;
			case 24: type=6; break;
			case 25: type=5; break;
			case 26: type=4; break;
			case 27: type=3; break;
			case 28: type=50; break;
			case 29: type=49; break;
			case 30: type=33; break;
            case 31: type=32; break;
            case 32: type=31; break;
            case 33: type=30; break;
			case 35: type=43; break;
			case 36: type=42; break;
			case 42: type=36; break;
			case 43: type=35; break;
			case 49: type=29; break;
			case 50: type=28; break;
			default: break;
			}
			rotateTileUp(*tile);
            current->set_type(type);
            *tile = current;
		}
		reverse(layer->second.begin(), layer->second.end());
	}
}
void Map::rotateTileUp(Tile* tile){
    	int x=tile->get_box()->x;
		int y=tile->get_box()->y;
		x=(width)-x-1;
		y=(height)-y-1;
		tile->set_x(x);
		tile->set_y(y);
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

bool Map::solid_collision(int direction, int x, int y, int w, int h){
    std::cout << "\n";
    if((x< 0) || (x+w > get_Widthpx()) || (y<0) || (y+h >= get_Heightpx())){
    //std::cout<<"Map boundry collision.\n";
    return true;
    }
    int type, tile_x, tile_y;
    tile_x = (x/32)*32;
    tile_y = (y/32)*32;
    //top left collision tile
    if(direction==0 || direction==3){
    type = get_Tiles(0)[x/32 + (y/32*get_Width())]->get_type();
    //std::cout << "testing top left collision with     (" << tile_x/32 << "," << tile_y/32 << ") px:(" << tile_x << "," << tile_y << ") type " << type << ": ";
    if(tile_test(type, tile_x, tile_y, x, y, w, h))
    return true;
    }
    //top right collision tile
    if(direction==0 || direction==1){
    type = get_Tiles(0)[x/32+ 1 + (y/32*get_Width())]->get_type();
    //std::cout << "testing top right collision with    (" << tile_x/32 + 1 << "," << tile_y/32 << ") px:(" << tile_x+32 << "," << tile_y << ") type " << type << ": ";
    if(tile_test(type, tile_x+32, tile_y, x, y, w, h))
    return true;
    }
    //bottom left collision tile
    if(direction==2||direction==3){
    type = get_Tiles(0)[x/32 + (((y)/32+1)*get_Width())]->get_type();
    //std::cout << "testing bottom left collision with  (" << tile_x/32 << "," << tile_y/32+1 << ") px:(" << tile_x << "," << tile_y+32 << ") type " << type << ": ";
    if(tile_test(type, tile_x, tile_y+32, x, y, w, h))
    return true;
    }
    //bottom right collision tile
    if(direction==2||direction==1){
    type = get_Tiles(0)[x/32 + 1 + ((y/32+1)*get_Width())]->get_type();
    //std::cout << "testing bottom right collision with (" << tile_x/32+1 << "," << tile_y/32+1 << ") px:(" << tile_x+32 << "," << tile_y+32 << ") type " << type << ": ";
    if(tile_test(type, tile_x+32, tile_y+32, x, y, w, h))
    return true;
    }
    return false;
}

bool Map::tile_test(int type, int tile_x, int tile_y, int x, int y, int w, int h){
    int relative_x= x+(w/3)-tile_x;
    int relative_y= y-tile_y;
    int relative_w= x+(2*w/3)-tile_x;
    int relative_h= y+h-tile_y;
    if(type==33){
        if((tile_y + 32 > y)&&(tile_y+16 < y+h)&&(tile_x+32>x)&&(tile_x<x+w)){
            return true;
        }
    }else if(type==30){
        if((tile_y + 16 > y)&&(tile_y < y+h)&&(tile_x+32>x)&&(tile_x<x+w)){
            return true;
        }
    }else if(type==31){
        if((tile_y + 32 > y)&&(tile_y < y+h)&&(tile_x+32>x)&&(tile_x+16<x+w)){
            return true;
        }
    }else if(type==32){
        if((tile_y + 32 > y)&&(tile_y < y+h)&&(tile_x+16>x)&&(tile_x<x+w)){
            return true;
        }
    }else if (type==3){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y+16 && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))<(relative_h*2)-32){
                    return true;
                }
            }
    }else if (type==4){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))<relative_h*2){
                    return true;
                }
            }
    }else if (type==5){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if(relative_x<((relative_h*2))){
                    return true;
                }
            }
    }else if (type==6){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y+16 && y<tile_y+32){
                if(relative_x<(relative_h*2)-32){
                    return true;
                }
            }
    }else if (type==11){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))>relative_y){
                    return true;
                }
            }
    }else if (type==12){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if(relative_x>relative_y){
                    return true;
                }
            }
    }else if (type==18){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if(relative_x<relative_h){
                    return true;
                }
            }
    }else if (type==19){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))<relative_h){
                    return true;
                }
            }
    }else if (type==24){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if(relative_x>((relative_h*2))){
                    return true;
                }
            }
    }else if (type==25){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if(relative_x>(relative_y*2)-32){
                    return true;
                }
            }
    }else if (type==26){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))>(relative_y*2)-32){
                    return true;
                }
            }
    }else if (type==27){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))>relative_y*2){
                    return true;
                }
            }
    }else if (type==28){
            if(x+w > tile_x+16 && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))*2<relative_h){
                    return true;
                }
            }
    }else if (type==29){
            if(x+w > tile_x && x < tile_x+16 && y+h > tile_y && y<tile_y+32){
                if((relative_x*2)<relative_h){
                    return true;
                }
            }
    }else if (type==35){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))*2 -32<relative_h){
                    return true;
                }
            }
    }else if (type==36){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((relative_x*2)-32<relative_h){
                    return true;
                }
            }
    }else if (type==42){
            if(x+w > tile_x && x < tile_x && y+h > tile_y && y<tile_y+32){
                if((relative_x*2)>relative_y){
                    return true;
                }
            }
    }else if (type==43){
            if(x+w > tile_x && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))*2>relative_y){
                    return true;
                }
            }
    }else if (type==49){
            if(x+w > tile_x+16 && x < tile_x+32 && y+h > tile_y && y<tile_y+32){
                if((relative_x*2)-32>relative_y){
                    return true;
                }
            }
    }else if (type==50){
            if(x+w > tile_x && x < tile_x+16 && y+h > tile_y && y<tile_y+32){
                if((tile_x+32 - (x+(2*w/3)))*2 -32 > relative_y){
                    return true;
                }
            }
    }else if (type==52){
        finish_map();
        //std::cout<<"reached and exit.\n";
        return false;
    }else if(type!=0){
        if((tile_y + 32 > y)&&(tile_y < y+h)&&(tile_x+32>x)&&(tile_x<x+w)){
            return true;
        }
    }

    return false;
}
void Map::finish_map(){
    if(!finished)
    finished=true;
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
bool Map::is_done(int x, int y){
    if(get_Tiles(0)[x/32 + (y/32*get_Width())]->get_type()==52 || get_Tiles(0)[x/32+ 1 + (y/32*get_Width())]->get_type()==52 || get_Tiles(0)[x/32 + (((y)/32+1)*get_Width())]->get_type()==52 || get_Tiles(0)[x/32 + 1 + ((y/32+1)*get_Width())]->get_type()==52)
    return true;
    return false;
}
