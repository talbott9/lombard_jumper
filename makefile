ljumper: ljumper.cpp sdlstuff.cpp physics.h physics.cpp player.h player.cpp tile.h tile.cpp renderer.h renderer.cpp convert.cpp globalvars.h leveleditor.h leveleditor.cpp particles.h particles.cpp cutscenes.h cutscenes.cpp scripts.cpp
	g++ ljumper.cpp -w -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o ljumper -ggdb3
	#g++ convert.cpp -o convert
