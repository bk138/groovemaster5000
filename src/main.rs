use std::env;
use std::process;

mod instrument;
mod mixer;
mod multi_modul;
mod noise_gen;
mod note_sheet;
mod picked_string;
mod sound;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("ERROR: no infile!");
        process::exit(1);
    }

    let mut notesheet = note_sheet::NoteSheet::new();
    println!("noten ok? {}", notesheet.load_file(&args[1]));

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

    for sample_now in 0..notesheet.notes.last().unwrap().on_sample {
        guitar.tick(); //play...

        //  we are not at the end yet
        if note_it != notesheet.notes.len() {
            while notesheet.notes[note_it].on_sample == sample_now {
                //current note is NOW

                let s = picked_string::PickedString::new(&notesheet.notes[note_it]);

                guitar.add(s);

                note_it += 1; // maybe another note NOW?
            }
        }

        output.push_back(guitar.output);
    }

    output.save_file("out.aum");
}
