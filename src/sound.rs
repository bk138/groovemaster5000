use std::fs;
use std::io::Write;
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

pub struct Sound {
    snddata: Vec<f64>,
}

impl Sound {
    pub fn new() -> Sound {
        Sound {
            snddata: Vec::new(),
        }
    }

    pub fn push_back(&mut self, value: f64) {
        self.snddata.push(value);
    }

    pub fn save_file(&self, path: &str) -> bool {
        let mut to_be_saved: Vec<i16> = Vec::new();

        // de-normalize and save as i16
        for i in &self.snddata {
            to_be_saved.push((*i * 32000.0) as i16);
        }

        // stow it away
        let mut f = fs::File::create(path).unwrap();

        for i in &to_be_saved {
            f.write_all(&i.to_le_bytes()).expect("write failed");
        }

        true
    }
}
