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
