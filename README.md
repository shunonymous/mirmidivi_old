Building:
 Please install following softwares before building:
 	-Boost library
	-asoundlib
	-CMake
	-Compiler (GCC or Clang)
 
 Execute following command in terminal:
 	 $ cd /path/to/dir/mirmidivi
 	 $ cmake .
	 $ make

How to use:
 Execute following command in terminal:
 	 $ cd /path/to/dir/mirmidivi
	 $ ./mirmidivi -a
 ALSA sequencer port was opened in this.
 You can check mirmidivi's port number by following command.
	 $ aconnect -o
 If you are using aplaymidi, and mirmidivi's port number was
 129, you can play midi by this command:
	 $ aplaymidi -p 129 your_favorite_midi_file.mid