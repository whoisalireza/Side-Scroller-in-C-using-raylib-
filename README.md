# Side-Scroller-in-C-using-raylib-

#WARNING: Although this game is resizable, it the game becomes unplayable once resized while playing. 
#Only way to play this game currently through the two pre-defined modes: 1080p and 720p with 720p being a lot easier.

- OLD DESCRIPTION BEGIN -

Another small project for uni. A flappy bird like side scroller, which is not finished however.
- OLD DESCRIPTION END -

This project is long not just a project for the university anymore. I try to make this my first ever game.
I want to make it a side-scroller/platformer with certain levels that play like flappy bird.

Right now it is not even in alpha, there will be a lot of stuff added in the future...

To run this game, download or clone this repository, and just double click on the game.exe file. However, if your antivirus goes off or you just want to build the .exe yourself, open a command prompt in the directory where you saved this project, and then run "mingw32-make".

This should work for Windows users, Linux users should just run "make" but I dont know
if this project even works on Linux/UNIX based systems.

# Usage of level.txt:

- " * " = high block

- " - " = middle block (the only challenge in this came until now.. xD)

- " _ " = low block

- " . " = win block (Needs to be the last block in the level file, everything that comes after wont be recognized. Also needs to be present and touched, otherwise game can not finish)

You can create your own level which by default supports up to 1000 blocks, anything above that will be ignored by the game
because MAX_OBSTACLES is set to 1000. You can edit that how you want tho lol.
