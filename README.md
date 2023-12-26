# 2048

# The game

This game consists of a grid filled with integer numbers and blank spaces. You can move all cells to one direction (that’s your gameplay) in a way that, if a cell finds another cell with the same number, they combine into only one cell with this new number.

The objective is to reach the biggest number possible until your grid is completely full.

# How to run

Just run the ```run.sh```

```bash
# Running the game
cd src
./run.sh
```

The script will make the installation work for you (like downloading a tabling library from my github)

# The commands
## Move
You have four moves:

1. Left to right: ```right```, ``r``, ``A``, ``esquerda``
2. Right to left: ```left```, ```l```, ```D```, ``direita``
3. Top down: ```down```, ```d```, ```S```, ```baixo```
4. Bottom up: ```up```, ```u```, ```W```, ```cima```

Note that the third input matches the ```W```, ```A```, ```S```, ```D``` input, but to avoid conflicts it’s upper case (just use the ```CapsLk``` and be happy)

## Save and load
You can save the game with command ```\SAVE``` \
You can load a saved game with command ```\LOAD``` \

## Quit game
You can quit game with command ```\QUIT``` \


# TODOs
1. Add different field grid sizes - OK
2. Add a more automatic control (without pressing "enter")
3. Add a more natural print (without printing tons of grids in the screen) - OK
4. Add a save option to continue the game even if the game was closed - OK
5. Add a save control, to save more informations about a saved game and avoid trying to \
load a not existing save
6. Fix a bug that ramdonly crashes the game - OK (i hope so)

# Author

[Augusto dos Santos](github.com/augustodsgv)
