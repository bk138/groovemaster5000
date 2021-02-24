use std::time::Duration;

use crate::sound::{self, Sound};
use sdl2::audio::{AudioCallback, AudioSpecDesired};

struct SamplePlayer<'a> {
    samples: &'a Vec<f64>,
    offset: usize,
}

impl<'a> AudioCallback for SamplePlayer<'a> {
    type Channel = f32;

    fn callback(&mut self, out: &mut [f32]) {
        // shift data over to audio buffer
        for (pos, x) in out.iter_mut().enumerate() {
            *x = match self.samples.get(pos + self.offset) {
                Some(sample) => *sample as f32,
                None => 0.0,
            };
        }
        self.offset += out.len();
    }
}

pub fn play(sound: &Sound) {
    println!("play started");

    let audio_subsystem = sdl2::init().unwrap().audio().unwrap();

    let spec = AudioSpecDesired {
        freq: Some(sound::SMPLRATE as i32),
        channels: Some(1), // mono
        samples: None,     // default sample size
    };

    let device = audio_subsystem
        .open_playback(None, &spec, |_spec| {
            // initialize the audio callback
            SamplePlayer {
                samples: sound.get_samples(),
                offset: 0,
            }
        })
        .unwrap();

    // Start playback
    device.resume();

    std::thread::sleep(Duration::from_millis(
        sound.get_samples().len() as u64 / sound::SMPLRATE as u64 * 1000,
    ));

    // device will be dropped here, i.e also be closed
    println!("play ended");
}
