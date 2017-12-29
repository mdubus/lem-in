# lem-in

Lem-in is an algorithm project, where ants have to go the fastest as posible from start-room to end-room.

## Algorithm

This is an home-made algorithm. 

I check all possible paths and compare them to select the best paths. 

This can take a lot of time on big maps. 

To reduce the calculation time, I eliminated some paths (useless, dead-end, ...). 

## Understanding the maps
```
10          // ants number
1 250 150   // Room name (1) ants it's X-Y coordonates
2 550 150
3 550 450
##start     // Next room will be start room
4 250 450
##end       // Next room will be end room
5 850 450
6 850 150
1-2         // Relations between rooms. Room 1 and 2 are linked
1-3
1-4
2-4
2-6
2-5
3-4
3-5
3-6
5-6
```

## Understanding the output

L[ant]-[room]
```
L1-2 L2-3                // Turn 1 : ant number 1 go to room 2. Ant number 2 go to room 3
L1-5 L3-2 L2-5 L4-3
L3-5 L5-2 L4-5 L6-3
L5-5 L7-2 L6-5 L8-3
L7-5 L9-2 L8-5 L10-3
L9-5 L10-5
```

## Prerequisites

`brew install SDL2`

`brew install SDL2_ttf`

`brew install SDL2_image`

If brew isn't installed, compile the project with the sources (don't forget to change the Makefile).

## Installation

`make`

## Run

Standard mode : 

`./lem-in < [map]`

Visualizer mode :

`./lem-in < [map] | ./visu`

## Bonus

### Special rooms

You can add 2 special rooms : 
- One containing a Snorlax. Ants can't go this way, it's blocked !

`##snorlax`

- An other containing lava. Ants can't go this way, it burns ! 

`##lava`

### Visualizer

You can run a visualizer to see you ants moving. 
Here are the commands : 
- right key : see next turn
- r : reinitialize the anthill
- + - : change your ants speed
- esc : escape the visualizer

Here is an example of what can be obtained with this algorithm and visualizer :

### Debug mode

`./lem-in -d < [map]`

This allows two things : 
- When an arror occurs trying to launch a map, it will write the exact error on the stderr instead of "ERROR"
- Lauching a map, it will give more info about the map and the algorithm (number of ants, rooms, pipes, all possible paths, chosen paths, relations between rooms, ...)

### Visual graph in png

`./graph.sh [map]`

This will generate a png of the anthill, with all rooms and their relations.

### Script test

`./script.sh`

This will launch a script testing the parsing. 
This is usefull to test all sort of maps with errors (no ants, no start room, anthill with no solutions, ...).


# Final mark

`125/100 (Full bonus)`
