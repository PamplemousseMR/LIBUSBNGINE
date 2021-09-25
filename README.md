# LIBUSBNGINE

Libusb sandbox.

## CI

![Build Status](https://github.com/PamplemousseMR/LIBUSBNGINE/actions/workflows/build.yml/badge.svg)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- [Libusb](https://github.com/libusb/libusb) : A cross-platform library to access USB devices.

### Generation

You can use [Conan](https://conan.io/), the C / C++ Package Manager to get LibUSB.

Use conan to download/build libraries : `conan install -s build_type=Release -if <build_folder> .`

Generate using cmake: `cmake`.

## Authors

* **MANCIAUX Romain** - *Initial work* - [PamplemousseMR](https://github.com/PamplemousseMR).

## License

This project is licensed under the GNU Lesser General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details.
