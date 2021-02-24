pub fn mixer_next(inputs_and_weights: Vec<(f64, f64)>) -> f64 {
    let mut output = 0.0;

    for (input, weight) in inputs_and_weights {
        output += input * weight;
    }

    output
}
