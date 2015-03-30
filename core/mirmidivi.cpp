/*
 * mirmidivi is rendering midi as visual
 *
 * Copyright (C) 2014-2015 Shun Terabayashi <shunonymous@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <cstdlib>
#include <dlfcn.h>
#include "core.hpp"

namespace mirmidivi
{
    namespace option
    {
	extern mode option(int argc,char **argv);
    }
    namespace alsa_seq
    {
	void ld_alsa_seq()
	{
	    // Open alsa_seq library
	    void *handle = dlopen("./alsa_seq/libalsa_seq.so",RTLD_LAZY);
	    if (!handle)
	    {
		std::cerr << "Cannot open library: " << dlerror() << std::endl;
		exit(1);
	    }
	    
	    // load the symbol
	    typedef void (*alsa_seq_t)();

	    //reset errors
	    dlerror();
	    alsa_seq_t alsa_seq = (alsa_seq_t) dlsym(handle, "alsa_seq");
	    const char* dlsym_error = dlerror();
	    if (dlsym_error)
	    {
		std::cerr << "Cannot load symbol 'alsa_seq': " << dlsym_error << std::endl;
		dlclose(handle);
		exit(1);
	    }
	    alsa_seq();
	    dlclose(handle);
	} // void ld_alsa_seq()
    } // namespace alsa_seq
}//namespace mirmidivi

int main(int argc,char **argv)
{
    using namespace mirmidivi;

    mode modes;

    modes = option::option(argc,argv); // set option -> ./option.cpp
    
    if ( modes.midi_seq_mode() == "alsa")
    {
	// Load ALSA Sequencer module
	alsa_seq::ld_alsa_seq();
    }
    return 0;
}
