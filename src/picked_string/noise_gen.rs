use rand::Rng;

pub struct NoiseGen {
    counter: i32,
}

impl NoiseGen {
    pub fn new(l: i32) -> NoiseGen {
        NoiseGen { counter: l }
    }

    pub fn next(&mut self) -> f64 {
        if self.counter == 0 {
            0.0
        } else {
            self.counter -= 1;
            // using this instead of stdlib.h's rand() makes the Rust version sound different
            (-32768.0 + rand::thread_rng().gen_range(0.0, 65536.0)) / 32768.0
        }
    }
}
