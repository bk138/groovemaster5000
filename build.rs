// build.rs

fn main() {
    cc::Build::new()
        .cpp(true) // Switch to C++ library compilation.
        .file("src/util.cpp")
        .file("src/Instrument.cpp")
        .compile("libgroovemaster.a");
}
