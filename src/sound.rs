use std::os;

// C++ Sound shim
extern "C" {
    pub fn new_sound() -> *const os::raw::c_void;
    pub fn sound_push_back(
        sound: *const os::raw::c_void,
        value: os::raw::c_double,
    ) -> *const os::raw::c_void;
    pub fn sound_save_file(
        sound: *const os::raw::c_void,
        path: *const os::raw::c_char,
    ) -> os::raw::c_int;
}
