# PathFinder

This program was created for my third-year undergraduate module 'Object
Oriented Programming in C++'.  The application uses the Qt framework to create
a GUI to allow the user to set up a 'maze' to be solved by a pathfinding
algorithm. The project files were built with QtCreator.

![Screenshot of the application](https://github.com/Hazza4569/PathFinder/blob/master/docs/screenshot.jpg?raw=true)

The interface allows the user to generate a random maze but also to edit the
maze: adding/removing obstacles, moving the start location, and moving or
adding finish locations. When the pathfinding is requested, the grid updates
sequentially to show each step of the search; providing a visualisation of how
each of the pathfinding algorithms work.

One of the key concepts was the use of polymorphic design to include two
different geometries of grid, square and hexagonal, in which the maze could be
set up.

The associated report I wrote for this project can be found
[here](docs/report.pdf). I was awarded a grade of 96% for this module.
