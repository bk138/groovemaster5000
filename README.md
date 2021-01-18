# groovemaster5000

This is the solution to task 6 of "Mathematische Grundlagen der digitalen
Klanganalyse und -synthese", held by Manfred Hild during winter semester
2007/2008 at Humbold Universität zu Berlin.

## Original C++ Version

Authored by Benjamin Werner and Christian Beier.

Build via `make -C src`, run by `./src/groovemaster5000 CLSFsonate.not`, play output
via `play -r 44k -e signed -b 16 -c 1 -t raw  out.aum`.

## Rust Version Ported From The C++ One

Run by `cargo run CLSFsonate.not`, play output like for C++ version.
