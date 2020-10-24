use std::env;
use std::os;
use std::process;

mod note_sheet;

// C++ PickedString shim
extern "C" {
    pub fn new_pickedstring(note: *const note_sheet::Note) -> *const os::raw::c_void;
    pub fn pickedstring_is_done(pickedstring: *const os::raw::c_void) -> os::raw::c_int;
    pub fn pickedstring_tick(pickedstring: *const os::raw::c_void);
    pub fn pickedstring_get_output(pickedstring: *const os::raw::c_void) -> os::raw::c_double;
}

// C++ Sound shim
extern "C" {
    pub fn new_sound() -> *const os::raw::c_void;
    pub fn sound_push_back(
        sound: *const os::raw::c_void,
        value: os::raw::c_double,
    ) -> *const os::raw::c_void;
    pub fn sound_save_file(sound: *const os::raw::c_void, path: *const u8) -> os::raw::c_int;
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
            note_sheet::notesheet_load_file(notesheet, args[1].as_ptr())
        );

        let output = new_sound();

        let pickedstring = new_pickedstring(&note);

        while pickedstring_is_done(pickedstring) == 0 {
            pickedstring_tick(pickedstring);
            sound_push_back(output, pickedstring_get_output(pickedstring));
        }

        sound_save_file(output, "out.aum\0".as_ptr()); //FIXME make use of CStr
    }
}
