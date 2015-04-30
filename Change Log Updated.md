	April 20th	
FILES EDITED - SFEvent.cpp, SFEvent.h & SFApp.cpp
Added a SFEVENT_PLAYER_UP & SFEVENT_PLAYER_DOWN

	April 21st
FILES EDITED - SFApp.cpp, SFApp.h, SFAssest.cpp & SFAssest.h
Added new wall assest (SFASSET_WALL) using the alien.png

	April 23rd
FILES EDITED - SFApp.cpp, SFApp.h, SFAssest.cpp & SFAssest.h
Changed amount of aliens on screen to 2 and centered
Creates four lines of walls and centered
Prevented player from moving off screen
- still some inaccuracy with spacing and projectiles do not erase.
Stopped collectable from moving
Updated Collisions
- Projectile to Wall, destroys projectile
- Player to Wall, no effect
- Player to Collectable, no effect
- Player to Alien, no effect
Added a random regenerate for coin, after collision with player

	April 24th
FILES EDITED - SFApp.cpp, SFApp.h, SFAssest.cpp & SFAssest.h
Added new assets
SFASSET_PROJECTILE2 & SFASSET_WALL2
Added new sprites to replace old ones
enemy.png, diamond.png, player.png, wall1.png, wall2.png, projetcile.png, projectile2.png
- Something wrong with the PNG files for projectiles (Maybe transparency on image since sRBG is in Error message)
Repositioned the Walls
Updated Collisions
- Player to Wall, however no effect
- Player to Collectable, Re-spawn collectable
- Player to Alien, Player re-spawn
Re-Updated Collisions
- Player to Collectable, Hides, doesn't destroy
  - Compare to Aiden's original Alien kill
- Player to Alien, Player re-spawn & Alien Re-spawn
- Problem where Alien can re-spawn under the player making it unable to be shot.
Fixed player to edge of screen collision

	April 25th
FILES EDITED - SFApp.cpp, SFApp.h, SFAssest.cpp & SFAssest.h
Updated Collisions
- Alien to Wall, prevents Alien spawning under a wall
- Player to Coin, Destroys Coin.
Added similar code to destroy the projectiles after they have hit top of screen
Alien's random re-spawn now is within a set space
- new problem is aliens can spawn above a wall segment so a player cannot kill them
Added a scoring system
- Need to add end screen

	April 26th
FILES EDITED - SFApp.cpp, SFApp.h, SFAssest.cpp, SFAssest.h, SFEvent.h & SFEvent.cpp
Added new assets SFASSET_EMERALD, SFASSET_SAPPHIRE, SFASSET_RUBY, SFASSET_DIAMOND
Created four new collectable items with an counter which is set to go to an end game screen upon all items being collected under SFApp::OnUpdateWorld
Added 3 new projectiles to go left, down and right
- was having an issue with use of for statements and "auto" so have had to use copies of similar code for simplicity
- Problem with arrows not deleting at the wall, now fixed

	April 28th
FILES EDITED - SFApp.cpp, SFApp.h, SFAssest.cpp & SFAssest.h
Fixed sRGB file problem by creating new projectile PNG files
Created an end game screen
Updated the gem locations
Added more walls

April 30th
FILES EDITED - SFApp.cpp, SFApp.h, SFAssest.cpp & SFAssest.h
Changed walls to holes and made player re-spawn upon collision to make the game more difficult
Changed background colour
Updated end of screen collision
General clean up


