$, $(...) – VARIABLE EXPANSION
$ means "use a variable".
$(...) is how we expand a variable.

$(NAME)     → expands to "cub3d"
$@          → expands to current *target*
$<          → expands to first *prerequisite*
$^          → expands to all *prerequisites*
--------------------------------
SRCS = $(wildcard src/*.c)
Means: “give me all .c files in the src/ folder”.
-------------------------------

:=	Assign variable immediately
$(VAR)	Expand a variable
$@	Target filename
$<	First dependency
$^	All dependencies
$(dir $@)	Directory path of target
@	Hide command output
wildcard	List matching files
patsubst	Pattern substitution
.PHONY	Mark rules as non-file-based
-------------------------------------
ifeq ($(UNAME_S),Linux)
    ...
endif
Means: “If OS is Linux, then use these settings.”
--------------------------------------
What is a "graphical environment"?
It’s the part of Linux that shows windows, buttons, images — like your desktop interface (GNOME, KDE, XFCE).
Without it, you're in text-only mode (like the black terminal).
-------------------------------
What is $DISPLAY?
It’s a special variable that tells programs where to open windows.

Example values:

:0 → screen 0 on your local desktop

localhost:10.0 → remote graphical session (like SSH with X11 forwarding)

If $DISPLAY is empty or wrong, then programs like mlx_init() can’t create a window → crash.
============================
.xpm files:

A .xpm image is a text file like this:

xpm
Copy code
/* XPM */
static char *example[] = {
"4 4 2 1",         // width, height, number of colors, chars per pixel
"0 c #FFFFFF",     // color definitions
"1 c #000000",
"0110",            // each line = row of pixels
"1001",
"1001",
"0110"
};
Explained:
"4 4 2 1" → 4×4 image, 2 colors, each pixel = 1 character

"0 c #FFFFFF" → 0 means white

"1 c #000000" → 1 means black

Image = cross symbol

Feature	XPM	JPG/PNG
Format	Text file	Binary format
Editable	Yes (in any text editor)	No
Compression	None	Yes
Transparency	Yes (basic)	PNG only
Use in MLX	✅ Easy and required	❌ Not supported
==========================

