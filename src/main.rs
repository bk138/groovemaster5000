use std::env;
use std::ffi::CString;
use std::os;
use std::process;

mod note_sheet;
mod sound;

// C++ PickedString shim
extern "C" {
    pub fn new_pickedstring(note: *const note_sheet::Note) -> *const os::raw::c_void;
    pub fn pickedstring_is_done(pickedstring: *const os::raw::c_void) -> os::raw::c_int;
    pub fn pickedstring_tick(pickedstring: *const os::raw::c_void);
    pub fn pickedstring_get_output(pickedstring: *const os::raw::c_void) -> os::raw::c_double;
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
        let notesheet = note_sheet::new_notesheet();
        println!(
            "noten ok? {}",
            note_sheet::notesheet_load_file(
                notesheet,
                CString::new(args[1].as_str()).unwrap().as_ptr()
            )
        );

        let output = sound::new_sound();

        let pickedstring = new_pickedstring(&note);

        while pickedstring_is_done(pickedstring) == 0 {
            pickedstring_tick(pickedstring);
            sound::sound_push_back(output, pickedstring_get_output(pickedstring));
        }

        sound::sound_save_file(output, CString::new("out.aum").unwrap().as_ptr());
    }
}
