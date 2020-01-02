all: main.cpp 
	g++  -g -Wall -o main main.cpp

clean:
	rm main
	rm main.dSYM/Contents/Info.plist
	rm main.dSYM/Contents/Resources/DWARF/main
	rmdir main.dSYM/Contents/Resources/DWARF
	rmdir main.dSYM/Contents/Resources
	rmdir main.dSYM/Contents
	rmdir main.dSYM
