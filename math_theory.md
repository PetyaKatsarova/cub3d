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

player->x = 100

player->y = 100

player->angle = 0

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