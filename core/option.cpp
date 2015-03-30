/*
 * option.cpp - Parse commandline argument for mirmidivi
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
#include <iterator>
#include <boost/program_options.hpp>
#include "core.hpp"

namespace mirmidivi
{

    namespace option
    {

	mode option(int argc,char **argv)
	{
	    namespace po = boost::program_options;

	    // Declare modes object
	    mode core_opts;

	    // Declare options
	    po::options_description core("Options");
	    core.add_options()
		("help,h","Print this help and exit.")
		("alsa,a","Set sequencer mode as ALSA.")
		("text,t","Launch in text mode.")
		;
    
	    // Read option's values
	    po::variables_map vm;
	    // Conain commandline arguments to vm
	    po::store(po::parse_command_line(argc,argv,core),vm);

	    po::notify(vm);

	    try{
		// When option has "help"
		if(vm.count("help"))
		{
		    std::cout << core << std::endl;
		    exit(0);
		}
		// when option has "alsa"
		if(vm.count("alsa"))
		    core_opts.set_midi_seq_mode("alsa");
		// when option has "text"
		if(vm.count("text"))
		    core_opts.set_gfx_mode("text");
	    } // try
    
	    // When invalid option was given
	    catch(std::exception& e)
	    {
		std::cerr << "Error:" << e.what() << std::endl;
		std::cerr << core << std::endl;
	    }
	    catch(...)
	    {
		std::cerr << "Exception of unknown type." << std::endl;
	    }

	    return core_opts;

	} // void option(int argc,char **argv)

    } // namespace option

} // namespace mirmidivi
