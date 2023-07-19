# GeometryWars

Geometry wars game implemented with SFML and a custom game engine.

This is assignment 2 following the course COMP4300 Game Programming.

Assignment can be found at this video: https://www.youtube.com/watch?v=OmzU_-zbE7o&t=1301s

I do not have access to the assignment files, nor am I enrolled in the class. But following some basica tutorials from SFML's website, I was able to follow along.

You can check them out here if interested: https://www.sfml-dev.org/tutorials/2.5/

The purpose of the assignment is to create the game Geometry Wars. A config file reads in some unique values related to the game. Those values can be the window size, specific fonts, circles, etc. A player object is spawned in the middle of the screen and enemy entities are spawned every x seconds (defined in the config). The player uses WASD to move around, and left click to fire at the shapes. If a 'bullet' collides with a shape, it will explode, and the players score is increased. If the player hits a shape, they will respawn in the middle of the screen.

Config File Understanding:

Please see the youtube video to understand what each line in the config is looking for. The order can not be rearranged and must follow the same pattern as the video.
