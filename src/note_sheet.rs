use std::{
    fs,
    io::{BufRead, BufReader, Error},
};

use ghakuf::messages::*;
use ghakuf::reader::*;
use std::path;

use crate::sound;

#[derive(Debug)]
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
    sample_count: u64,
}

impl NoteSheet {
    pub fn new() -> Self {
        Self {
            notes: Vec::new(),
            sample_count: 0,
        }
    }

    pub fn sample_count(&self) -> u64 {
        self.sample_count
    }

    pub fn load_file(&mut self, path: &str) -> Result<(), Error> {
        if path.ends_with(".not") {
            self.load_note_file(path)
        } else if path.ends_with(".mid") {
            self.load_midi_file(path)
        } else {
            Err(Error::new(
                std::io::ErrorKind::InvalidInput,
                "Invalid notesheet file given, must be .not or .mid",
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

            let note_sample_end = n.on_sample + n.length_sample as u64;
            if note_sample_end > self.sample_count {
                self.sample_count = note_sample_end;
            }

            self.notes.push(n);
        }

        Ok(())
    }

    fn load_midi_file(&mut self, path: &str) -> Result<(), Error> {
        struct MidiHandler<'a> {
            notes: &'a mut Vec<Note>,
            sample_count: &'a mut u64,
            divisions: u16,
            s_per_tick: f64,
            current_on_time: f64,
        }

        impl<'a> Handler for MidiHandler<'a> {
            fn header(&mut self, format: u16, track: u16, time_base: u16) {
                println!(
                    "MIDI: SMF format: {}, track: {}, time base: {}",
                    format, track, time_base
                );
                self.divisions = time_base;
            }

            fn meta_event(&mut self, _delta_time: u32, event: &MetaEvent, data: &Vec<u8>) {
                if let MetaEvent::SetTempo = event {
                    let tempo = (data[0] as u32) << 16 | (data[1] as u32) << 8 | data[2] as u32;
                    self.s_per_tick = (tempo as f64 / self.divisions as f64) / 1000000.0;
                    #[cfg(debug_assertions)]
                    println!(
                        "MIDI: SetTempo: {}, calculated seconds/tick: {}",
                        tempo, self.s_per_tick
                    );
                }
            }

            fn midi_event(&mut self, delta_time: u32, event: &MidiEvent) {
                #[cfg(debug_assertions)]
                println!("MIDI: delta time: {:>4}, MIDI event: {}", delta_time, event,);

                let mut handle_note = |note: &u8, velocity: &u8| {
                    self.current_on_time += delta_time as f64 * self.s_per_tick;
                    let length_time: f64 = 0.0;
                    let note = *note as i32;

                    let n = Note {
                        on_time: self.current_on_time,
                        on_sample: (self.current_on_time * sound::SMPLRATE) as u64,
                        length_time,
                        length_sample: (length_time * sound::SMPLRATE) as u32,
                        note,
                        freq: 1.0594f64.powi(note - 69) * 440.0,
                        loudness: *velocity as f64,
                    };

                    if n.loudness > 0.0 {
                        #[cfg(debug_assertions)]
                        println!("   striking note {:?}", n);
                        self.notes.push(n);
                    } else {
                        // look for unended notesheet entries with same note, starting at end of note sheet
                        let end_note = match self
                            .notes
                            .iter_mut()
                            .rev()
                            .find(|n| n.length_time == 0.0 && n.note == note)
                        {
                            Some(n) => n,
                            None => return, // no previous unended same note found, bail out
                        };
                        end_note.length_time = self.current_on_time - end_note.on_time;
                        end_note.length_sample = (end_note.length_time * sound::SMPLRATE) as u32;
                        #[cfg(debug_assertions)]
                        println!("   ending note {:?}", end_note);

                        // update note sheet's sample count
                        let note_sample_end = end_note.on_sample + end_note.length_sample as u64;
                        if note_sample_end > *self.sample_count {
                            *self.sample_count = note_sample_end;
                        }
                    }
                };

                match event {
                    MidiEvent::NoteOff {
                        ch: _,
                        note,
                        velocity,
                    } => handle_note(note, velocity),
                    MidiEvent::NoteOn {
                        ch: _,
                        note,
                        velocity,
                    } => handle_note(note, velocity),
                    _ => {}
                };
            }

            fn track_change(&mut self) {
                #[cfg(debug_assertions)]
                println!("MIDI: Track changed");
                self.current_on_time = 0.0;
            }
        }

        let mut handler = MidiHandler {
            notes: &mut self.notes,
            sample_count: &mut self.sample_count,
            divisions: 0,
            s_per_tick: 0.0,
            current_on_time: 0.0,
        };
        let mut reader = Reader::new(&mut handler, &path::Path::new(path)).unwrap();

        // TODO Box errors
        match reader.read() {
            Ok(_) => Ok(()),
            Err(_) => Err(Error::new(
                std::io::ErrorKind::InvalidInput,
                "Error reading .mid file",
            )),
        }
    }
}
