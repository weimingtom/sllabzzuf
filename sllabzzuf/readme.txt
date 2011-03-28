version 0.0.3

-It reads the newgame.map file in /data 
-renders the map in roughly the same way as the level editor. 
-Arrow keys to walk.
-Z to jump
-X + arrow to dash
-The game loop is almost all there
-classes for everything
-Unit, currently unused, inherits from Object.

-It's not a bug; its a feature: jumping cancels out dash's recharch time.
spam z+x+z+x etc to zoom forward, will consume MP like crazy though.
*****BUGS*******
-For some reason you cannot dash for the first 5 seconds or so.

*****TO DO******
-triangle tiles are still considered squares in collision detection
-attack + its own particle effects.
-progressing to the next map
-auto pause/display text notices