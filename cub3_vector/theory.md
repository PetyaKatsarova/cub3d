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

scss
Copy
Edit
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

