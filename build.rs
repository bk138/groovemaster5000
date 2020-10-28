// build.rs

fn main() {
    cc::Build::new()
        .cpp(true) // Switch to C++ library compilation.
        .file("src/util.cpp")
        .file("src/Notesheet.cpp")
        .file("src/Mixer.cpp")
        .file("src/MultModul.cpp")
        .file("src/NoiseGen.cpp")
        .file("src/PickedString.cpp")
        .file("src/Instrument.cpp")
        .compile("libgroovemaster.a");
}
