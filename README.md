# groovemaster5000

This is the solution to task 6 of "Mathematische Grundlagen der digitalen
Klanganalyse und -synthese", held by Manfred Hild during winter semester
2007/2008 at Humbold Universität zu Berlin.

## Original C++ Version

Authored by Benjamin Werner and Christian Beier.

Build via `make -C src`, run by `./src/groovemaster5000 CLSFsonate.not`, play output
via `play -r 44k -e signed -b 16 -c 1 -t raw  out.aum`.

## Rust Version Ported From The C++ One

At commit [7533fc15c33c09a697d50b5fbe5aa00ccbc1c1b1](https://github.com/bk138/groovemaster5000/commit/7533fc15c33c09a697d50b5fbe5aa00ccbc1c1b1),
this matches the C++ version. Afterwards, it diverges into a more Rust-y version.

Run by `cargo run CLSFsonate.not`, play output like for C++ version.
