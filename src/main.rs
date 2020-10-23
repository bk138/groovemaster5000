use std::env;
use std::process;

mod note_sheet;

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("ERROR: no infile!");
        process::exit(1);
    }

    let note = note_sheet::Note {
        on_time: 0.0,
        on_sample: 0,
        length_time: 4.0,
        length_sample: 44100 * 4,
        note: 0,
        freq: 440.0,
        loudness: 0.0,
    };

    unsafe {
        let notesheet = note_sheet::new_notesheet();
        println!(
            "noten ok? {}",
            note_sheet::notesheet_load_file(notesheet, args[1].as_ptr())
        );
    }
}
