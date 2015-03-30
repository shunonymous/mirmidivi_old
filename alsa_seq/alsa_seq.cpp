/*
 * alsa_seq.cpp
 *
 * Copyright (C) 2015 Shun Terabayashi <shunonymous@gmail.com>
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
 *
 * This code is based on Matthias Nagorni's seqdemo.c <http://turing.suse.de/~mana/seqdemo.c>.
 * 
 */

#include <cstdio>
#include <alsa/asoundlib.h>
#include <cstdlib>
#include <unistd.h>

namespace mirmidivi
{

    extern void rendering();

    namespace alsa_seq
    {
	extern snd_seq_event_t *seq_handle;	
	extern int npfd;
	extern struct pollfd *pfd;
	
	snd_seq_t *open_seq()
	{
	    snd_seq_t *seq_handle;
	    int portid;

	    if (snd_seq_open(&seq_handle, "default", SND_SEQ_OPEN_INPUT, 0) < 0) {
		fprintf(stderr, "Error opening ALSA sequencer.\n");
		exit(1);
	    }
	    snd_seq_set_client_name(seq_handle, "mirmidivi");
	    if ((portid = snd_seq_create_simple_port(seq_handle, "mirmidivi",
						     SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE,
						     SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
		fprintf(stderr, "Error creating sequencer port.\n");
		exit(1);
	    }
	    return(seq_handle);
	} // snd_seq_t *open_seq()
	    
	void midi_action(snd_seq_t *seq_handle)
	{

	    snd_seq_event_t *ev;

	    do
	    {
		snd_seq_event_input(seq_handle, &ev);
		switch (ev->type) 
		{
		case SND_SEQ_EVENT_CONTROLLER: 
		    fprintf(stderr, "Control event on Channel %2d: %5d       \r",
			    ev->data.control.channel, ev->data.control.value);
		    break;
		case SND_SEQ_EVENT_PITCHBEND:
		    fprintf(stderr, "Pitchbender event on Channel %2d: %5d   \r", 
			    ev->data.control.channel, ev->data.control.value);
		    break;
		case SND_SEQ_EVENT_NOTEON:
		    fprintf(stderr, "Note On event on Channel %2d: %5d       \r",
			    ev->data.control.channel, ev->data.note.note);
		    break;        
		case SND_SEQ_EVENT_NOTEOFF: 
		    fprintf(stderr, "Note Off event on Channel %2d: %5d      \r",         
			    ev->data.control.channel, ev->data.note.note);           
		    break;        
		} // switch (ev->type)
		snd_seq_free_event(ev);
	    } while (snd_seq_event_input_pending(seq_handle, 0) > 0);
	} // void midi_action(snd_seq_t *seq_handle)

	extern "C" void alsa_seq()
	{

	    snd_seq_t *seq_handle;
	    int npfd;
	    struct pollfd *pfd;
    
	    seq_handle = open_seq();
	    npfd = snd_seq_poll_descriptors_count(seq_handle, POLLIN);
	    pfd = (struct pollfd *)alloca(npfd * sizeof(struct pollfd));
	    snd_seq_poll_descriptors(seq_handle, pfd, npfd, POLLIN);
	    while (1) {
		if (poll(pfd, npfd, 100000) > 0) 
		{
		    midi_action(seq_handle);
		    //rendering(seq_handle);
		}  
	    }
	} // extern "C" void receive_midi()
    } // namespace alsa
} // namespace mirmidivi
	
