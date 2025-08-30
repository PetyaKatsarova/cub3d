Why 64x64 px tiles?

Pros:

Powers of two (64) are efficient for bitwise operations and memory alignment.
Easy math for grid calculations (shifting, masking).
Large enough for visible detail, small enough for smooth movement.
Common standard in classic raycasting engines (Wolfenstein 3D, Doom).
Cons:

Fixed size may limit flexibility for different map scales or resolutions.
Large tiles can make small maps look blocky.
Small tiles increase memory usage and may slow down rendering if the map is huge.
Summary:
64x64 is a practical, efficient, and historically proven choice for grid-based raycasting.