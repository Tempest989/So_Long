# So_Long
This Project is about creating a 2D game using the 42 Custom library, Minilibx.  
Read the [subject.pdf](https://github.com/Tempest989/So_Long/blob/main/en.subject.pdf) for in-depth information about the Project.
### **WARNING: This Project will only work on Mac.**
# My Score
<img width="1347" alt="So_Long Score" src="https://user-images.githubusercontent.com/55472613/178904454-001e4ee1-3319-4f0c-a5f2-8261820eb4de.png">

# Makefile Utility
- `make compile` will compile the Minilibx library, then compile the So_Long Project, as the executable `so_long`.
- `make clean` will delete, if possible, the executable `so_long`.
- `make` and `make so_long` will run the commands `make clean` and `make compile`.
- `make dark` will compile the Minilibx library, then compile the Extra part of the So_Long Project, as the executable `so_dark`.
- `make dark_clean` will delete, if possible, the executable `so_dark`.
- `make fclean` will run `make clean` and `make dark_clean`, then run `make clean` for the Minilibx library.
- `make norm` will run the Norminette (42's Coding Standard for C) for the non-Minilibx files.
- `make re` will run the commands, `make fclean` and `make compile`.
# Code Execution Format
- `./so_long [file name ending in ".ber"]`
- `./so_dark [file name ending in ".ber"]`
# Controls
- `W` = Up.
- `S` = Down.
- `A` = Left.
- `D` = Right.
- `Esc` = Exit from the Game.
# Difference Between So_Long and So_Dark
So_Dark is a custom version of So_Long that I created as an extension of this Project, where instead of displaying the entire Map to the Player, So_Dark only displays a 3x3 grid around the Player intially and reveals the rest of the Map as the Player Moves around it, based on a 3x3 grid radius around the Player.
- So_Dark has no effect on my So_Long score, since it doesn't match any of the Bonus sections.
### Got all the Images I used in this Project from this [Github](https://github.com/pasqualerossi/So_Long).
