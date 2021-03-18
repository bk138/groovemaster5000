use groovemaster5000::note_sheet;

/// Not really an integration test as it only tests a single module, but I justed wanted to have one.
#[test]
fn simultaneous_notes_with_different_lengths() {
    let mut notesheet = note_sheet::NoteSheet::new();

    let _ = notesheet.load_file("shortlong.mid");

    assert_ne!(0.0, notesheet.notes[0].length_time);
}
