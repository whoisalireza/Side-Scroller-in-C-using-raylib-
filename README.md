# Side-Scroller-in-C-using-raylib-

#THIS GAME IS NOT IN A PLAYABLE STATE RIGHT NOW

- OLD DESCRIPTION BEGIN -

Another small project for uni. A flappy bird like side scroller, which is not finished however.
- OLD DESCRIPTION END -

WARNING: This game is currently not playable in every resolution... right now it is written for 1080p. There is also a 720p mode and you can resize the window as you want, however the actual game world still neeeds to be made resizable. Resolutions other than 1080p might work, however that is pure coincidence. - Will get fixed tho!

This project is long not just a project for the university anymore. I try to make this my first ever game.
I want to make it a side-scroller/platformer with certain levels that play like flappy bird.

Right now it is not even in alpha, there will be a lot of stuff added in the future...

To run this game, download or clone this repository, and just double click on the game.exe file. However, if your antivirus goes off or you just want to build the .exe yourself, open a command prompt in the directory where you saved this project, and then run "mingw32-make".

This should work for Windows users, Linux users should just run "make" but I dont know
if this project even works on Linux/UNIX based systems.

# Usage of level.txt:

- " * " = high block

- " - " = middle block (the only challenge in this came until now.. xD

- " _ " = low block

- " . " = win block (needs to be present and touched, otherwise game can not finish)

You can create your own level which by default supports up to 1000 blocks, anything above that will be ignored by the game
because MAX_OBSTACLES is set to 1000. You can edit that how you want tho lol.
