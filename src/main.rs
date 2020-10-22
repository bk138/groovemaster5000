use std::env;
use std::process;

// Notesheet shim
extern "C" {
    fn new_notesheet() -> *const libc::c_void;
    fn notesheet_load_file(notesheet: *const libc::c_void, path: *const u8) -> libc::c_int;
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len() < 2 {
        eprintln!("ERROR: no infile!");
        process::exit(1);
    }

    unsafe {
        let notesheet = new_notesheet();
        println!(
            "noten ok? {}",
            notesheet_load_file(notesheet, args[1].as_ptr())
        );
    }
}
