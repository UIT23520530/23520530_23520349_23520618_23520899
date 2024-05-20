



# Installation guide
You will need:
* OpenAL to run the game.
* SFML Library if you want to build the game yourself.

# OpenAL: 
Download the [Windows installer](https://www.openal.org/downloads/) for OpenAL then extract and run it to install openAL.

# SFML library:

* [Download](https://www.sfml-dev.org/download/sfml/2.6.1/) the version matching your compiler then extract into a new folder.

* Add the path of the folder into environment variables.
name the variable SFML_PATH.
* Open Project Properties,set to all configurations, then open the C/C++ tab.
* Under the General tab, in  "Additional include directories" add in "$(SFML_PATH)\include" without the quotes.
* Under the Preprocessor tab, in "Preprocessor Definitions" add in "SFML_STATIC" without the quotes, seperate with ";" if there is something already there.

* Open the Linker tab, under General, in "Additional library directories" add in "$(SFML_PATH)\lib".
 * Under Input in the "Additional Dependencies" field,then: 
 * * set Configuration to Release and then add in 
 ~~~~
 sfml-system-s.lib;sfml-window-s.lib;sfml-graphics-s.lib;opengl32.lib;freetype.lib;winmm.lib;gdi32.lib;sfml-audio-s.lib;openal32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;$(CoreLibraryDependencies);%(AdditionalDependencies)
 ~~~~
 
* * set Configuration to Debug and add in 
~~~~
sfml-system-s-d.lib;sfml-window-s-d.lib;sfml-graphics-s-d.lib;opengl32.lib;freetype.lib;winmm.lib;gdi32.lib;sfml-audio-s-d.lib;openal32.lib;flac.lib;vorbisenc.lib;vorbisfile.lib;vorbis.lib;ogg.lib;$(CoreLibraryDependencies);%(AdditionalDependencies)"
~~~~


* Search for "Edit Environment Variables" in windows search, open it, click Advanced, then "Environment Variables".
* * Click New to add a new variable. 
* * Name this variable whatever you like, the variable value will be the path to the game in the project, from the cloned repository it should be:
(wherever you cloned it to) \23520530_23520349_23520618_23520899\Snake_Game 
* Click OK until exit the window.

* In your project properties in Visual Studio. Under C/C++, in General, in "Additional Include Directories":
* * Seperate from what is already there with a ";", then add in 
~~~~
$(NAME)\include" (replace NAME with your variable name).

~~~~
* Click Apply, then OK.

Now you can build the game with CTRL+B, then run with F5.

