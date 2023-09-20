# PA9 Boggle
Authors: Ava Stromme, Kristen Blue, Sarah Janzen </br>
Date: 4/30/2020 </br>
Description: A simplistic game of Boggle using SFML graphics library.

## How to Build Project
- Open the project solution (PA9_boggle.sln) with the Visual Studio IDE (ex: Visual Studio Community 2019)
- Choose a Build: Debug or Release
- Press F7 or click <i>Build&rarr;Build Solution</i> from the menu bar.
- If you encounter linker errors that lead you to suspect that the graphics library is not linking, first try going into 32Win mode.  
  - To go into 32Win mode:
    - Click the button beside Debug/Release mode button (it will likely be 64 or 86). 
    - From the popup menu, choose Win32.
- If that doesn't fix the issue, check that <a href="#SFML">SFML is linked</a>.

## How to Run Project
- Inside the Visual Studio IDE, press F5 or ctrl+F5, or click <i>Debug&rarr;Start Debugging</i> or <i>Debug&rarr;Start Without Debugging</i>.

## <div id="SFML">How to Link SFML</div>
Ensure that SFML is linking in at least 1 of 4 ways: static debug, static release, dynamic debug, or dyanmic release. Our project is set up with static linking for both debug and release modes (in 32Win mode), but could be switched to dynamic with relative ease. Inside the project properties:
- For <i>Configuration: All Configurations</i>
  - Under <i>Configuration Properties&rarr;C/C++&rarr;General&rarr;Additional Include Directories</i> ensure that <i><b>./SFML/include</b></i> is listed.
  - Under <i>Configuration Properties&rarr;Linker&rarr;General&rarr;Additional Library Directories</i> ensure that <i><b>./SFML/lib</b></i> is listed.
- For a <b>Static Debug</b> Build:
  - For <i>Configuration: Debug</i>
    - Under <i>Configuration Properties&rarr;C/C++&rarr;Preprocessor&rarr;Preprocessor Definitions</i> ensure that <b><i>SFML_STATIC</i></b> is listed.
    - Under <i>Configuration Properties&rarr;Linker&rarr;Input&rarr;Additional Dependencies</i> ensure that these files are listed:
      - sfml-graphics-s-d.lib
      - sfml-window-s-d.lib
      - sfml-system-s-d.lib
      - sfml-audio-s-d.lib
      - opengl32.lib
      - freetype.lib
      - winmm.lib
      - gdi32.lib
      - openal32.lib
      - flac.lib
      - vorbisenc.lib
      - vorbisfile.lib
      - vorbis.lib
      - ogg.lib
- For a <b>Static Release</b> Build:
  - For <i>Configuration: Release</i>
    - Under <i>Configuration Properties&rarr;C/C++&rarr;Preprocessor&rarr;Preprocessor Definitions</i> ensure that <b><i>SFML_STATIC</i></b> is listed.
    - Under <i>Configuration Properties&rarr;Linker&rarr;Input&rarr;Additional Dependencies</i> ensure that these files are listed:
      - sfml-graphics-s.lib
      - sfml-window-s.lib
      - sfml-system-s.lib
      - sfml-audio-s.lib
      - opengl32.lib
      - freetype.lib
      - winmm.lib
      - gdi32.lib
      - openal32.lib
      - flac.lib
      - vorbisenc.lib
      - vorbisfile.lib
      - vorbis.lib
      - ogg.lib
- For a <b>Dynamic Debug</b> Build:
  - For <i>Configuration: Debug</i>
    - Under <i>Configuration Properties&rarr;Linker&rarr;Input&rarr;Additional Dependencies</i> ensure that these files are listed:
      - sfml-graphics-d.lib
      - sfml-window-d.lib
      - sfml-system-d.lib
      - sfml-audio-d.lib
- For a <b>Dynamic Release</b> Build:
  - For <i>Configuration: Release</i>
    - Under <i>Configuration Properties&rarr;Linker&rarr;Input&rarr;Additional Dependencies</i> ensure that these files are listed:
      - sfml-graphics.lib
      - sfml-window.lib
      - sfml-system.lib
      - sfml-audio.lib
- If SFML is linked dynamically, copy the dlls of SFML/bin into the folder that has the executable.

## Rules of Boggle
- 4 x 4 square of pseudo randomized letters
- (traditionally at least 2 players or more, but we should probably make it single-player)
- goal is to get highest total points
- player makes words from the assorment of random letters by stringing
  together a series of adjacent letters.
  (sequential letters in the player's words have to be next to each other 
  vertically, horizontally, or diagonally) 
- (traditionally the players have a time limit for making words, we could 
  keep this or let them have as long as they choose, or have some way of 
  deciding when the game is over)
- scoring (in general: more letters = more points)</br>
  <table>
  <tr><th>number of letters</th><td>3</td><td>4</td><td>5</td><td>6</td><td>7</td><td>8+</td></tr>
  <tr><th>points per word</th><td>1</td><td>1</td><td>2</td><td>3</td><td>5</td><td>11</td></tr>
  </table> (though, we could change the point system)
- multiple meanings of the same word are not counted as individual words and 
  do not earn more points ("lead" as in the verb meaning to guide is not 
  counted as a different word from "lead" as in the noun meaning the metal 
  / Pb element on the periodic table)
- variations of spelling a word (even if it does not change the meaning) are 
  counted as individual words ("run", "runs", and "running" are different words)
- the cube Qu is counted as 2 letters
  (could change this if the programming gets too weird; 
  we could alternatively change Qu to just be Q, since we don't have the limitation
  of using six sided dice; though it would be ideal to have a U neighbor in
  the case that a Q is placed)
