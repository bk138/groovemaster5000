use rand::Rng;

pub struct NoiseGen {
    counter: i32,

    pub output: f64,
}

impl NoiseGen {
    pub fn new(l: i32) -> NoiseGen {
        NoiseGen {
            output: 0.0,
            counter: l,
        }
    }

    pub fn next(&mut self) {
        if self.counter == 0 {
            self.output = 0.0;
        } else {
            self.counter -= 1;
            self.output = (-32768.0 + rand::thread_rng().gen_range(0.0, 65536.0)) / 32768.0;
        }
    }
}
