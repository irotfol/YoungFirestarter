# Young Firestarter
![YF](https://github.com/user-attachments/assets/7bfa1bf3-107f-4d58-bc9a-7715ec458eff)

Input file name: f.in.

Output file name: f.out.

A coordinate system is introduced on a grid field so that the origin is at the intersection of the grid lines, and the axes are directed along the grid lines.

A connected figure consisting of matchsticks has been laid out on this field. Two types of matchsticks were used:
Matchsticks of length 1 were laid along the sides of the cells.
Matchsticks of length √2 were laid along the diagonals of the cells.

A child wants to burn the figure.  They can ignite it at one point with integer coordinates (for example, igniting the figure at point A in the figure is not allowed, but at points B and C it is possible).

It is known that the fire spreads uniformly along a matchstick (but along each matchstick at its own speed). A matchstick can burn in several places (for example, when it catches fire from both ends; or when the fire spreads from one matchstick to another in the middle of a diagonal matchstick - the fire spreads along the newly ignited matchstick in both directions).

Write a program that determines at which point the figure should be ignited so that it burns out in the minimum time.

Input format
The input file first contains the number  N - the number of matchsticks (1 <= N <= 200). Then follows N quintuples of numbers of the form x1 y1 x2 y2 t, specifying the coordinates of the ends of the matchstick and the time it takes to burn completely if it is ignited from one end (it is guaranteed that each matchstick has a length of 1 or √2, all matchsticks form a connected figure, and the position of no two matchsticks coincides). All coordinates are integers not exceeding 200 in absolute value, and the burning time is a natural number not exceeding 100.

Output format
Output the coordinates of the integer point at which the figure should be ignited to burn out in the shortest time, and then the time it takes for the figure to burn out in this case. The time must be output with an accuracy of at least 2 decimal places. If there are multiple solutions, output any of them.

Example
f.in

3

1 1 1 2 10

1 2 2 2 10

1 1 2 2 50

f.out

2 2

35.00
