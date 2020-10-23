use std::os;

// C++ Notesheet shim
extern "C" {
    pub fn new_notesheet() -> *const os::raw::c_void;
    pub fn notesheet_load_file(
        notesheet: *const os::raw::c_void,
        path: *const u8,
    ) -> os::raw::c_int;
}

#[repr(C)]
#[derive(Debug, Copy, Clone)]
pub struct Note {
    pub on_time: f64,
    pub on_sample: ::std::os::raw::c_ulong,
    pub length_time: f64,
    pub length_sample: ::std::os::raw::c_uint,
    pub note: ::std::os::raw::c_int,
    pub freq: f64,
    pub loudness: f64,
}
