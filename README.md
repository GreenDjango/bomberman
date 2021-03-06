# Bomberman

[![Bomberman - Trailer](https://imgur.com/YVBB6zT.png)](https://www.youtube.com/watch?v=5d1xmhByLuM "Click to Watch!")

#### The aim of the **Indie Studio** is to implement a cross-platform 3D video game with real-world tools.
[Bomberman](https://en.wikipedia.org/wiki/Bomberman) is a well known game, where you control a character that have to kills the other players on the map with bomb. You can play in multiplayer or against AIs.

Our gameplay reference is [Neo Bomberman](https://en.wikipedia.org/wiki/Neo_Bomberman), released on the Neo Geo and MVS systems in 1997. You can play up to two players on the same PC, on Versus or again AI.

The project is composed with two library all in **C++** : the 3D engine **[Irrlicht 1.8.4](http://irrlicht.sourceforge.net/)** and the part of library **[SFML-audio 2.5](https://www.sfml-dev.org/)**.

#### Subject
  [B-YEP-400_indie.pdf](https://github.com/GreenDjango/bomberman/blob/master/B-YEP-400_indie.pdf)

#### Project realised by:
- **[@Frederic C.](https://github.com/red-gecko27)**
- **Louis C.**
- **[@Théo C.](https://github.com/GreenDjango)**
- **Yann M.**

### Program compilation and launching:
  ##### Linux:
  ```
  cmake .
  make
  ./bomberman
  ```
  > Will compile the entire project and launch it.

   ##### Windows:
  ```
  // Need to use Visual Studio
  // and make a new cmake project
  // for build the .exe
  ```
  >  Will install the Bomberman on your PC. (Follow the instructions)

### Gameplay

#### Player commands
|**Player**|**Keys**|**Effect**|
|---:|---:|:---|
|Player 1|***Arrow keys***<br/>***Space***|Move your character.<br/>Place a bomb.|
|Player 2|***Z Q S D***<br/>***A***|Move your character.<br/>Place a bomb.|

#### Game commands
|**Keys**|**Effect**|
|---:|:---|
|***SPACE***|To skip the intro.|
|***ENTER***|To validate without clicking.|
|***ESCAPE***|To pause the game.|
