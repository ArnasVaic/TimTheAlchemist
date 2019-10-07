all:
	g++ -o main.exe main.cpp -DSFML_STATIC -I \
	"C:\Program Files (x86)\SFML\SFML\include" -L \
	"C:\Program Files (x86)\SFML\SFML\lib" -lsfml-graphics-s -lsfml-audio-s \
	-lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype \
	-lopenal32 -lflac -lvorbisenc -lvorbisfile \
	-lvorbis -logg\
