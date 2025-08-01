====================================================
b4 starting, do:
sudo apt install cmake libglfw3-dev libgl1-mesa-dev xorg build-essential
Install X server (VcXsrv for Windows) and set $DISPLAY.

-- now using minilibx_linux ----
b4 make command need to compile the mlx(minilibx) library:
cd lib/minilibx_linux
cmake -B build
cmake --build build

;; b4 make command need to compile the mlx42 library:
;; cd lib/MLX42
;; cmake -B build
;; cmake --build build
===================================================
mxl42:
https://github.com/codam-coding-college/MLX42/wiki

===================================================


Program name cub3D
Turn in files All your files
Makefile all, clean, fclean, re, bonus
===================================================
Arguments a map in format *.cub
===================================================
External functs.
• open, close, read, write,
printf, malloc, free, perror,
strerror, exit, gettimeofday.
• All functions of the math
library (-lm man man 3 math).
• All functions of the MinilibX
library.
Libft authorized Yes
====================================================
Description You must create a “realistic” 3D graphical
representation of the inside of a maze from a
first-person perspective. You have to create this
representation using the ray-casting principles
mentioned earlier.
The constraints are as follows:
• You must use the miniLibX. Either the version that is available on the operating
system, or from its sources. If you choose to work with the sources, you will
need to apply the same rules for your libft as those written above in Common
Instructions part.
• The management of your window must remain smooth: changing to another window, minimizing, etc.
• Display different wall textures (the choice is yours) that vary depending on which
side the wall is facing (North, South, East, West).
7
cub3D My first RayCaster with miniLibX
• Your program must be able to set the floor and ceiling colors to two different ones.
• The program displays the image in a window and respects the following rules:
◦ The left and right arrow keys of the keyboard must allow you to look left and
right in the maze.
◦ The W, A, S, and D keys must allow you to move the point of view through
the maze.
◦ Pressing ESC must close the window and quit the program cleanly.
◦ Clicking on the red cross on the window’s frame must close the window and
quit the program cleanly.
◦ The use of images of the minilibX library is strongly recommended.
• Your program must take as a first argument a scene description file with the .cub
extension.
◦ The map must be composed of only 6 possible characters: 0 for an empty space,
1 for a wall, and N,S,E or W for the pl’s start position and spawning
orientation.
This is a simple valid map:
111111
100101
101001
1100N1
111111
◦ The map must be closed/surrounded by walls, if not the program must return
an error.
◦ Except for the map content, each type of element can be separated by one or
more empty lines.
◦ Except for the map content which always has to be the last, each type of
element can be set in any order in the file.
◦ Except for the map, each type of information from an element can be separated
by one or more spaces.
◦ The map must be parsed as it looks in the file. Spaces are a valid part of the
map and are up to you to handle. You must be able to parse any kind of map,
as long as it respects the rules of the map.
8
cub3D My first RayCaster with miniLibX
◦ Except for the map, each element must begin with its type identifier (composed
by one or two characters), followed by its specific information in a strict order:
∗ North texture:
NO ./path_to_the_north_texture
· identifier: NO
· path to the north texture
∗ South texture:
SO ./path_to_the_south_texture
· identifier: SO
· path to the south texture
∗ West texture:
WE ./path_to_the_west_texture
· identifier: WE
· path to the west texture
∗ East texture:
EA ./path_to_the_east_texture
· identifier: EA
· path to the east texture
∗ Floor color:
F 220,100,0
· identifier: F
· R,G,B colors in range [0,255]: 0, 255, 255
9
cub3D My first RayCaster with miniLibX
∗ Ceiling color:
C 225,30,0
· identifier: C
· R,G,B colors in range [0,255]: 0, 255, 255
◦ Example of the mandatory part with a minimalist .cub scene:
NO ./path_to_the_north_texture
SO ./path_to_the_south_texture
WE ./path_to_the_west_texture
EA ./path_to_the_east_texture
F 220,100,0
C 225,30,0
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
◦ If any misconfiguration of any kind is encountered in the file, the program
must exit properly and return "Error\n" followed by an explicit error message
of your choice.