/*
 * TileSheet.cpp
 *
 *  Created on: Jan 30, 2011
 *      Author: Admin
 */

#include "TileSheet.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
//#include "load_img.h"

TileSheet::TileSheet(){
	width = 0;
	height = 0;
	tileSheetSurface = NULL;
}

TileSheet::~TileSheet(){
	if(tileSheetSurface)
		SDL_FreeSurface(tileSheetSurface);
}
/*
SDL_Surface* TileSheet::load_image( std::string filename){
    SDL_Surface* loadedImage = NULL;
    loadedImage = IMG_Load( filename.c_str() );
return loadedImage;
}
*/
SDL_Surface* TileSheet::load_image( std::string filename ){
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = NULL;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized surface
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized
        if( optimizedImage != NULL )
        {
            //Color key surface
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB( optimizedImage->format, 0xFF, 0, 0xFF ) );
        }
    }else{
    std::cout << "loadedImage is still NULL!\n";
    }

    //Return the optimized surface
return optimizedImage;
}

/**
 * Load a tilesheet from a file, and tell if the file should have transparency or chroma-key.
 */
void TileSheet::loadSheet(std::string filename){
	if(tileSheetSurface!=NULL){
		std::cout << "Freeing tileSheetSurface\n";
		SDL_FreeSurface(tileSheetSurface);
	}
		std::cout << "loading tileSheetSurface from " << filename << "\n";

    		tileSheetSurface = load_image(filename);

	if(tileSheetSurface){
		width = tileSheetSurface->w/32;
		height = tileSheetSurface->h/32;
		std::cout << "Tile sheet loaded successfully from " << filename << " with dimensions:" << width << "," << height << "\n";
	}else {
		width = 0;
		height = 0;
		std::cout << "Tile sheet loading failed\n";
	}

}

/**
 * Get the SDL_Surface pointer for this tile sheet.
 */
SDL_Surface *TileSheet::get_Surface(){
	return tileSheetSurface;
}

/**
 * Get the location on the tilesheet of a certain tile based on its subtype
 */
SDL_Rect TileSheet::getTileFromSheet(Tile* tile){
	SDL_Rect ret;
		ret.x = tile->get_type()%width*32;
		ret.y = tile->get_type()/width*32;
        ret.h = 32;
        ret.w = 32;
	return ret;
}

SDL_Rect TileSheet::getBackgroundTile(){
	SDL_Rect ret;

	ret.x = tileSheetSurface->w-64;
	ret.y = tileSheetSurface->h-64;
	ret.h = 64;
	ret.w = 64;
	return ret;
}
