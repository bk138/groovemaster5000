use crate::picked_string::PickedString;

pub struct Instrument {
    parts: Vec<PickedString>,
    pub output: f64,
}

impl Instrument {
    pub fn new() -> Instrument {
        Instrument {
            parts: Vec::new(),
            output: 0.0,
        }
    }

    pub fn add(&mut self, part: PickedString) {
        self.parts.push(part);
    }

    pub fn tick(&mut self) {
        self.output = 0.0;

        // first clean up
        self.parts.retain(|part| !part.is_done());

        // then play our parts
        for part in self.parts.iter_mut() {
            part.tick();
            self.output += part.output;
        }

        self.output = if !self.parts.is_empty() {
            self.output / self.parts.len() as f64
        } else {
            0.0
        };
    }
}
