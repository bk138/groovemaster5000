use std::env;
use std::process;

use groovemaster5000::instrument;
use groovemaster5000::note_sheet;
use groovemaster5000::picked_string;
use groovemaster5000::player;
use groovemaster5000::sound;


fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("ERROR: no infile!");
        process::exit(1);
    }

    let mut notesheet = note_sheet::NoteSheet::new();
    println!("noten ok? {:?}", notesheet.load_file(&args[1]));
    notesheet.notes.sort_by(|a, b| a.on_sample.cmp(&b.on_sample));

    let mut output = sound::Sound::new();

    /*
    let note = note_sheet::Note {
        on_time: 0.0,
        on_sample: 0,
        length_time: 4.0,
        length_sample: 44100 * 4,
        note: 0,
        freq: 440.0,
        loudness: 0.0,
    };

    let mut pickedstring = picked_string::PickedString::new(&note);

    while !pickedstring.is_done() {
        pickedstring.tick();
        output.push_back(pickedstring.output);
    }
     */

    let mut guitar = instrument::Instrument::new();

    let mut note_it = 0;

    for sample_now in 0..notesheet.sample_count() {
        guitar.tick(); //play...

        //  we are not at the end yet
        while note_it != notesheet.notes.len() && notesheet.notes[note_it].on_sample == sample_now {
            //current note is NOW
            let s = picked_string::PickedString::new(&notesheet.notes[note_it]);

            guitar.add(s);

            note_it += 1; // maybe another note NOW?
        }

        output.push_back(guitar.output);
    }

    player::play(&output);

    output.save_file("out.aum").unwrap();
}
