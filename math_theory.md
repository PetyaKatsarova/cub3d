 cos(θ) (cosine) = adjacent / hypotenuse
→ how far along x-axis

sin(θ) (sine) = opposite / hypotenuse
→ how far along y-axis




x = cos(angle); // horizontal direction
y = sin(angle); // vertical direction
This gives you a unit vector (length = 1) pointing in direction angle.

🔄 Angle in radians
Degrees	Radians
0°	0
90°	π/2
180°	π
270°	3π/2

angle = 0         → (cos, sin) = (1, 0)    → facing right  
angle = π/2       → (0, 1)                 → facing up  
angle = π         → (-1, 0)                → facing left  
angle = 3π/2      → (0, -1)                → facing down

           (0,1)
             ↑
             |
             |     π/2
             |
(-1,0) ←–––––•–––––→ (1,0)
             |
             |     3π/2
             ↓
           (0,-1)
cos(θ) = x

sin(θ) = y

θ = angle from right (0 radians) rotating counterclockwise
==========================================
In 2D:

A vector is a direction with magnitude.

Defined by:
origin (x, y)
direction (dx, dy)
length (l)
==========================================
To draw a vector from (x, y):
Use this loop:

double i = 0;
while (i < length)
{
	int px = x + cos(angle) * i;
	int py = y + sin(angle) * i;
	set_px(d, px, py, COLOR);
	i += 1;
}
---------------------------------------------
Let’s say:

pl->x = 100

pl->y = 100

pl->angle = 0

Draw vector of length 50:
raw_vector(t_data *d, double x, double y, double angle, double length)
{
	double i = 0;
	while (i < length)
	{
		int px = x + cos(angle) * i;
		int py = y + sin(angle) * i;
		set_px(d, px, py, WALL_COLOR); // lime
		i += 0.5;
	}
}
==========================================

#define TILE_SIZE 50 // should be png size
#define WIDTH 1800
#define HEIGHT 1200

Cols = WIDTH / TILE_SIZE = 1800 / 50 = 36
Rows = HEIGHT / TILE_SIZE = 1200 / 50 = 24

==================================
orig game, not secure link from school:
http://users.atw.hu/wolf3d/
==================================
Floor and ceiling must be filled with solid colors, not textures.
.cub file:
F 150,150,150
C 100,100,255
=================================
You're in a giant bathroom. The floor is made of square tiles.
You're standing in the middle of one tile.

You have a laser pointer.

You point it in a slightly diagonal direction — not perfectly forward, not perfectly sideways, but somewhere in between.

Now:

The laser will cross tile edges.
There are two kinds of edges:
Vertical lines (between tiles left–right)
Horizontal lines (between tiles top–bottom)
You want to know:
“How far does the laser go before it hits the first vertical line?”
“How far before it hits the first horizontal line?”
This is what delta_dist_x and delta_dist_y tell us:
One gives the distance between vertical line hits.
The other gives distance between horizontal hits.
Super Simple Rule:
If your laser points more left–right, it’ll hit vertical lines more often.
If it points more up–down, it’ll hit horizontal lines more often.
So each step in the raycasting loop does:
Compare:
Will the laser hit a vertical line first?
Or a horizontal line?
Move to the next tile in that direction.
Repeat until it hits a wall.

Imagine you're standing in a giant room full of tiles (a grid).
You're looking straight ahead.
That’s your view direction — a tiny invisible arrow called:

(dir_x, dir_y)
It points where your nose is pointing.

🖼️ Now pretend your head is a movie camera.
The camera sees a wide picture — not just a dot straight ahead, but a field of view.

That wide view is like a window floating in front of your face.
It’s invisible, but imagine stretching your arms sideways:
Your direction --->

Your arms
<-------------|------------->
That stretched-out line is the camera plane:
(plane_x, plane_y)

The view direction tells where you are looking.
The camera plane tells how wide your screen is, and what’s left and right.
For every vertical line x on the screen:

Start from the middle of your nose (dir_x, dir_y)

Move a bit left or right using plane_x and plane_y (like reaching left or right arm)

That gives the direction for that ray.

Summary:
dir = where your head points

plane = how wide your eyes can see

Together = calculate every ray direction for screen pixels

======================================
Step 2: Calculating the Delta Distance
The next step in the raycasting algorithm is to calculate the delta distance between two consecutive x or y intersections with a grid line. This is done by determining the distance the ray must travel to reach the next grid line in the x or y direction.

Example of delta dist x and y

	// ...

	int map_x = (int)pos_x;
	int map_y = (int)pos_y;

	double delta_dist_x = fabs(1 / ray_dir_x);
	double delta_dist_y = fabs(1 / ray_dir_y);

	// ...
This gives us the distance the ray must travel to reach the next grid line in each direction. Note here that the pos_x and pos_y both refer to the pl’s position.

Step 3: Calculating the Step and Initial Side Distances
Now we need to calculate the step_x, step_y and the initial side distances for the ray. The step_x and step_y variables determine the direction in which the ray moves through the grid.

The side_dist_x and side_dist_y variables represent initially the distance the ray must travel from its current position to the next grid line in the x or y direction. Later these variables will be updated with the delta distance as the ray moves through the grid.

=============================================================

A frame in a game or graphical application is a single iteration of drawing and updating the display. It includes rendering objects, handling events, and updating the screen.

In MiniLibX, the function that handles rendering a frame is mlx_loop_hook, which repeatedly calls a function to update and render the screen.

Steps for Frames:
mlx_loop_hook: Registers a function to be called every frame.

mlx_loop: Starts the MLX event loop to repeatedly call the frame function.

================================================

Radians are a unit for measuring angles, like degrees but more mathematically natural:

1 full circle = 2π radians = 360°
π radians = 180°
π/2 radians = 90°
0.1 radians ≈ 5.7°
The angle represents the player's viewing direction - where the player is looking.
     North (90° or π/2)
           ↑
           |
West ←────●────→ East (0° or 0 radians)
           |
           ↓
     South (270° or 3π/2)
From: Player's position (center point)
To: The direction the player is facing
Player view:
    
    ↗ angle = π/4 (45°)
   ●   ← player position
    
    → angle = 0 (facing right/east)
   ●
    
    ↓ angle = 3π/2 (270°, facing down/south)
   ●
   The angle is between:

Starting line: Positive X-axis (horizontal line pointing right)
Ending line: Your viewing direction vector

Example - facing northwest:

     Y ↑
       |    ↗ viewing direction
       |   /
       |  / angle = 3π/4
       | /
───────●────────→ X
       starting reference line
Standard Mathematical Convention
This follows the standard trigonometric convention:

0 radians = positive X-axis (east)
π/2 radians = positive Y-axis (north)
π radians = negative X-axis (west)
3π/2 radians = negative Y-axis (south)

The angle is always measured counterclockwise from the positive X-axis to your current viewing direction. This is why when you press LEFT arrow (rotate left), the angle increases, and when it goes negative, it wraps around to 2π.

Angle = 0 (facing east):
cos(0) = 1, sin(0) = 0
     Y ↑
       |
───────●────────→ X
       direction = (1, 0)

Angle = π/2 (facing north):
cos(π/2) = 0, sin(π/2) = 1
     Y ↑ direction = (0, 1)
       |
       |
───────●────────→ X

Angle = π (facing west):
cos(π) = -1, sin(π) = 0
     Y ↑
       |
   ←───●────────→ X
   direction = (-1, 0)

d->pl->delta_x = cos(d->pl->angle) * 5;
d->pl->delta_y = sin(d->pl->angle) * 5;

cos(angle) gives how much to move in X direction (-1 to +1)
sin(angle) gives how much to move in Y direction (-1 to +1)

The 0.1 is a speed control factor:
cd->pl->delta_x = cos(d->pl->angle) * 5;  // Direction vector with magnitude 5
// Then in movement:
move_x = d->pl->delta_x * 0.1;           // 5 * 0.1 = 0.5 pixels per frame
Speed Breakdown

Delta magnitude: 5 (your direction vector length)
Movement multiplier: 0.1
Actual movement per frame: 5 × 0.1 = 0.5 pixels

Why This Small Value?

Frame rate: pl_control() is called every frame (60+ FPS)
Smooth movement: 0.5 pixels × 60 FPS = 30 pixels/second
Control: Without the 0.1, you'd move 5 pixels per frame = 300 pixels/second (way too fast!)

Speed Comparison in Your Code
c// Continuous rotation: 0.02 radians per frame (very slow)
d->pl->angle -= 0.02;

// Immediate rotation: 0.1 radians per keypress (faster)
d->pl->angle -= 0.1;  // in handle_arrow_keys()

// Movement: 0.1 × delta per frame (moderate speed)
move_x = d->pl->delta_x * 0.1;
The 0.1 makes movement smooth and controllable instead of lightning-fast.
