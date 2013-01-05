MrDungeon

Android game made for Great Canadian Appathon 48 Competition sponsered by XMG

Coders: Harry, Nathan
Artwork: Carl, Sophia

This game runs on Android 2.2 devices and up as well as on the PC (this is the PC build).

Implements/Uses:

A* algorithm for pathfinding based on http://code.google.com/p/a-star-java/
Vertex Buffer objects for batching sprites. (in libgx.)
Custom screen panning
Custom transition engine

Some instructions...
- To play you need a java run time environment installed. Download it for free somewhere.

- The basic idea is that there is a robot that is trying to get to a trophy. And you are to 
 design an obstacle course with walls and spikes to impede his movement. 
 
 - You can drag the map around to pan to different areas of the "dungeon" and drag traps from the bottom 
 bar to the tileset. (You are not allowed to block the path off completely with walls)

 - Drag the traps to where you *think* the robot is going to go (e.g. around the trophy). And 
 if he steps on it, a mini game will trigger and you have to click the screen to stomp on the robot.
 Do this enough times and he will die.
