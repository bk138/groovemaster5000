pub struct MultiModul {
    pointer: i32,
    end: i32,
    begin: i32,
    length: i32,
    bufflength: i32,
    picks_and_weights: Vec<(i32, f64)>,
    buffer: Vec<f64>,
}

impl MultiModul {
    pub fn new(buflen: i32, picks_and_weights: Vec<(i32, f64)>) -> MultiModul {
        MultiModul {
            bufflength: buflen,
            length: buflen,
            buffer: vec![0.0; buflen as usize],
            pointer: 0,
            begin: 0,
            end: buflen - 1,
            picks_and_weights,
        }
    }

    pub fn next(&mut self, input: f64) -> f64 {
        let mut pickpointer: i32;
        self.pointer += 1;
        //cerr << pointer;
        //cerr << " ";
        if self.end >= self.begin {
            //end liegt nach begin auf dem Array einfacher fall;
            if self.pointer > self.end {
                self.pointer = self.begin;
            }
        } else {
            //komplizierter Fall end liegt vor begin
            if self.pointer <= self.begin && self.pointer > self.end {
                //
                self.pointer = self.begin;
            } else {
                if self.pointer >= self.bufflength {
                    self.pointer = 0;
                }
            }
        }
        //cerr << "\n Pointer";
        //cerr << pointer;
        //cerr << "\n";

        let mut output = 0.0;

        for (pick, weight) in &self.picks_and_weights {
            if *pick == 0 {
                output = output + input * weight;
            } else {
                if *pick <= self.length {
                    //cerr << (*pickups)[i];
                    //cerr << " pick\n";
                    pickpointer = self.pointer - pick;
                    if self.end >= self.begin {
                        //einfach Fall
                        if pickpointer < self.begin {
                            pickpointer += self.length;
                        }
                    } else {
                        if pickpointer < 0 {
                            pickpointer = self.bufflength + pickpointer;
                        }
                    }
                    output = output + self.buffer[pickpointer as usize] * weight;
                }
            }

            //cerr << pickpointer;
            //cerr << "\n";
        }
        //output = buffer[pointer];
        self.buffer[self.pointer as usize] = input;
        output
    }
}
