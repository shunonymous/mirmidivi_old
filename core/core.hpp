/*
 * core.hpp - 
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

namespace mirmidivi
{
    typedef std::string mod;
    class mode
    {
    private:
	mod midi_seq_mod;
	mod gfx_mod;
    public:
	void set_midi_seq_mode(mod seqmod){ midi_seq_mod = seqmod; }
	mod midi_seq_mode(){ return midi_seq_mod; }
	void set_gfx_mode(mod gfxmod){ gfx_mod = gfxmod; }
	mod gfx_mode(){ return gfx_mod; }
    };
}
