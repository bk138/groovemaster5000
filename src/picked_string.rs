use crate::{
    mixer::mixer_next, multi_modul::MultiModul, noise_gen::NoiseGen, note_sheet::Note, sound,
};

pub struct PickedString {
    // the inner devices
    noise: NoiseGen,
    delayline: MultiModul,
    lowpass: MultiModul,

    ticks: u64,
    samples: u64,

    done: bool,

    pub output: f64,
}

impl PickedString {
    pub fn new(n: &Note) -> PickedString {
        let delaylength: i32 = (sound::SMPLRATE / n.freq) as i32;
        let delayrem: f64 = (sound::SMPLRATE % n.freq) / n.freq;
        let damp: f64 = 0.0015 * (1.0 / n.length_time);

        PickedString {
            done: false,
            ticks: 0,
            output: 0.0,
            samples: u64::from(n.length_sample),

            // noise
            noise: NoiseGen::new(delaylength),

            // delay line
            delayline: MultiModul::new(
                delaylength,
                vec![
                    (delaylength - 1, delayrem),
                    (delaylength - 2, 1.0 - delayrem),
                ],
            ),

            // lowpass
            lowpass: MultiModul::new(1, vec![(0, 0.5 - damp), (1, 0.5)]),
        }
    }

    pub fn tick(&mut self) {
        self.ticks += 1;

        if self.ticks > self.samples {
            self.done = true;
        }

        self.output = self.delayline.next(mixer_next(vec![
            (self.noise.next(), 1.0),
            (self.lowpass.next(self.output), 0.999),
        ]));
    }

    pub fn is_done(&self) -> bool {
        self.done
    }
}
