use std::env;
use std::os;
use std::process;

mod note_sheet;

// Notesheet shim
extern "C" {
    fn new_notesheet() -> *const os::raw::c_void;
    fn notesheet_load_file(notesheet: *const os::raw::c_void, path: *const u8) -> os::raw::c_int;
}

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
        let notesheet = new_notesheet();
        println!(
            "noten ok? {}",
            notesheet_load_file(notesheet, args[1].as_ptr())
        );
    }
}
