use std::fs;
use std::io::BufWriter;
use std::io::Write;

pub const SMPLRATE: f64 = 44100.0;

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
        let mut buffer = BufWriter::new(fs::File::create(path).unwrap());

        for i in &to_be_saved {
            buffer.write_all(&i.to_le_bytes()).expect("write failed");
        }
        buffer.flush().unwrap();

        true
    }
}
