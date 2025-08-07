https://lodev.org/cgtutor/raycasting.html#Textured_Raycaster

45° makes a perfect diagonal line
Forms right triangle with equal sides

Using Pythagorean theorem:
cos²(45°) + sin²(45°) = 1  (radius = 1)
Since cos(45°) = sin(45°) (equal sides):
2 × cos²(45°) = 1
cos²(45°) = 0.5
cos(45°) = √0.5 = 0.707

STEP_SIZE 1:

cos(45°) = 0.707
STEP_SIZE_size = 2 pixels
X movement = 0.707 × 2 = 1.414
Y movement = 0.707 × 2 = 1.414
Why multiply by 2?

0.707 = direction (how much of each STEP_SIZE goes X vs Y)
2 = how big each STEP_SIZE is (in pixels)
0.707 × 2 = 1.414 = actual pixels moved
=======================================
CALC WALLS SIZE
=======================================

STEP_SIZE 1: Cast rays
Player shoots rays left-to-right across screen
Each ray = 1 pixel column on screen

STEP_SIZE 2: Find wall distance
Ray travels until it hits wall
Measure distance from player to wall

STEP_SIZE 3: Calculate wall height
RULE: Closer walls = taller on screen
      Further walls = shorter on screen
wall_height = SCREEN_HEIGHT / distance
Example:
Wall 10 pixels away → height = 800/10 = 80 pixels tall
Wall 20 pixels away → height = 800/20 = 40 pixels tall

STEP_SIZE 4: Draw the column
Screen center = 400 pixels
Wall height = 80 pixels
Top of wall = 400 - 80/2 = 360
Bottom of wall = 400 + 80/2 = 440

Draw vertical line from y=360 to y=440
================================================
draw a direction vector
------------------------------------------------
Player position: (100, 200)
Direction: (0.5, 0.8)

Point 1: (100, 200) + 1×(0.5, 0.8) = (100.5, 200.8)
Point 2: (100, 200) + 2×(0.5, 0.8) = (101.0, 201.6)  
Point 3: (100, 200) + 3×(0.5, 0.8) = (101.5, 202.4)
Point 4: (100, 200) + 4×(0.5, 0.8) = (102.0, 203.2)
Point 10: (100, 200) + 10×(0.5, 0.8) = (105.0, 208.0)
=================================================
2d vector examples
-------------------------------------------------
assuming starting from (0,0)
(3, 4) = go 3 right, 4 up
(-2, 1) = go 2 left, 1 up
(0.5, 0.8) = go 0.5 right, 0.8 up

adding vectors:
Position + Direction = New Position
(100, 200) + (3, 4) = (103, 204)
2 × (3, 4) = (6, 8)  // Same direction, twice as far
0.5 × (3, 4) = (1.5, 2)  // Same direction, half distance
================================================
matrix
------------------------------------------------
Matrix = a rectangle of numbers, used for transformations
2d rotation matrix
[cos(angle)  -sin(angle)]
[sin(angle)   cos(angle)]

pl->delta_x = cos(pl->angle)
pl->delta_y = sin(pl->angle)
Direction vector = (delta_x, delta_y)
=================================================
RAY CASTING
-------------------------------------------------
ray_x = player_x + STEP_SIZE × cos(ray_angle)
ray_y = player_y + STEP_SIZE × sin(ray_angle)
 Vector = arrow pointing somewhere. Matrix = tool to rotate/transform arrows.
 =============================
 RADIANS
 --------------------------------
 Radians measure ANGLES
0 radians = 0° = East (right)
π/2 radians = 90° = South (down)
π radians = 180° = West (left)
3π/2 radians = 270° = North (up)
Why use radians instead of degrees?

Math functions (cos, sin) expect radians
More precise for calculations
Standard in programming