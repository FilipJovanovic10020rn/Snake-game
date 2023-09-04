Introduction
This is a snake game created from scrach written in c, using the rafgl library. The rafgl library is an educational library made for easy use of graphics manipulation.
The point of the project was learning about 2D graphics, pixels, spreadsheets, particles and game development.

About the code
The game is running on a [n][m] matrix which defines the board and has the snakes positions. The snake is defined with integers larger than 0 ( the biggest being its head ), the free spaces with 0, blocked spaces ( meaning out of bounds ) with -1 and the food with -2.
As the snake collects the fruits it adds the biggest int in that direction making its the head of the snake.
