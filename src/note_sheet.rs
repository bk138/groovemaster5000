use std::{
    fs,
    io::{BufRead, BufReader, Error},
};

use crate::sound;

pub struct Note {
    pub on_time: f64,
    pub on_sample: u64,
    pub length_time: f64,
    pub length_sample: u32,
    pub note: i32,
    pub freq: f64,
    pub loudness: f64,
}

pub struct NoteSheet {
    pub notes: Vec<Note>,
}

impl NoteSheet {
    pub fn new() -> Self {
        Self { notes: Vec::new() }
    }

    pub fn load_file(&mut self, path: &str) -> Result<(), Error> {
        if path.ends_with(".not") {
            self.load_note_file(path)
        } else {
            Err(Error::new(
                std::io::ErrorKind::InvalidInput,
                "Invalid notesheet file given, must be .not",
            ))
        }
    }

    fn load_note_file(&mut self, path: &str) -> Result<(), Error> {
        let file = fs::File::open(&path)?;

        let reader = BufReader::new(file);

        for line in reader.lines() {
            let str = line.unwrap();
            let mut value_iter = str.split_whitespace();

            let on_time: f64 = match value_iter.next() {
                None => 0.0,
                Some(v) => v.parse().unwrap(),
            };

            let length_time: f64 = match value_iter.next() {
                None => 0.0,
                Some(v) => v.parse().unwrap(),
            };

            let note: i32 = match value_iter.next() {
                None => 0,
                Some(v) => v.parse().unwrap(),
            };

            let loudness: f64 = match value_iter.next() {
                None => 0.0,
                Some(v) => v.parse().unwrap(),
            };

            let n = Note {
                on_time,
                on_sample: (on_time * sound::SMPLRATE) as u64,
                length_time,
                length_sample: (length_time * sound::SMPLRATE) as u32,
                note,
                freq: 1.0594f64.powi(note - 69) * 440.0,
                loudness,
            };

            self.notes.push(n);
        }

        Ok(())
    }
}
