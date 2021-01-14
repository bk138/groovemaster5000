use std::{os, ptr};

use crate::{noise_gen::NoiseGen, note_sheet::Note, sound};

// C++ MultiModul shim
extern "C" {
    pub fn new_multimodul(
        buflen: os::raw::c_int,
        pick1: os::raw::c_int,
        pick2: os::raw::c_int,
        ws1: os::raw::c_double,
        ws2: os::raw::c_double,
    ) -> *const os::raw::c_void;
    pub fn multimodul_next(multimodul: *const os::raw::c_void);
    pub fn multimodul_get_output(multimodul: *const os::raw::c_void) -> *const os::raw::c_double;
    pub fn multimodul_set_input(
        multimodul: *const os::raw::c_void,
        input: *const os::raw::c_double,
    );
}

// C++ Mixer shim
extern "C" {
    pub fn new_mixer(
        in1: *const os::raw::c_double,
        in2: *const os::raw::c_double,
        w1: os::raw::c_double,
        w2: os::raw::c_double,
    ) -> *const os::raw::c_void;
    pub fn mixer_next(mixer: *const os::raw::c_void);
    pub fn mixer_get_output(mixer: *const os::raw::c_void) -> *const os::raw::c_double;
}

pub struct PickedString {
    // the inner devices
    noise: NoiseGen,
    delayline: *const os::raw::c_void,
    lowpass: *const os::raw::c_void,
    mix: *const os::raw::c_void,

    ticks: u64,
    samples: u64,

    done: bool,

    /*
    here you can turn the screws
     */
    // delay line
    pub delay_p: Vec<i32>,
    pub delay_w: Vec<f64>,

    // lowpass
    pub lowpass_p: Vec<i32>,
    pub lowpass_w: Vec<f64>,

    // mixer
    pub mix_in: Vec<f64>,
    pub mix_w: Vec<f64>,

    pub output: f64,
}

impl PickedString {
    pub unsafe fn new(n: &Note) -> PickedString {
        let delaylength: i32 = (sound::SMPLRATE / n.freq) as i32;
        let delayrem: f64 = (sound::SMPLRATE % n.freq) / n.freq;
        let damp: f64 = 0.0015 * (1.0 / n.length_time);

        let mut ps = PickedString {
            done: false,
            ticks: 0,
            output: 0.0,
            samples: u64::from(n.length_sample),

            // noise
            noise: NoiseGen::new(delaylength),

            // delay line
            delay_p: vec![delaylength - 1, delaylength - 2],
            delay_w: vec![delayrem, 1.0 - delayrem],
            delayline: new_multimodul(
                delaylength,
                delaylength - 1,
                delaylength - 2,
                delayrem,
                1.0 - delayrem,
            ),

            // lowpass
            lowpass_p: vec![0, 1],
            lowpass_w: vec![0.5 - damp, 0.5],
            lowpass: new_multimodul(1, 0, 1, 0.5 - damp, 0.5),

            // mixer
            mix_in: Vec::new(),
            mix_w: vec![1.0, 0.999],
            mix: ptr::null(),
        };

        // still mixer. ouch
        ps.mix = new_mixer(
            &ps.noise.output,
            multimodul_get_output(ps.lowpass),
            1.0,
            0.999,
        );

        multimodul_set_input(ps.delayline, mixer_get_output(ps.mix));
        multimodul_set_input(ps.lowpass, multimodul_get_output(ps.delayline));

        ps
    }

    pub unsafe fn tick(&mut self) {
        self.ticks += 1;

        if self.ticks > self.samples {
            self.done = true;
        }

        self.noise.next();
        mixer_next(self.mix);
        multimodul_next(self.delayline);
        multimodul_next(self.lowpass);

        self.output = *multimodul_get_output(self.delayline);
    }

    pub fn is_done(&self) -> bool {
        self.done
    }
}