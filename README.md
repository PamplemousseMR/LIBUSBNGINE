# LIBUSBNGINE

Libusb sandbox.

## Travis

[![Build Status](https://travis-ci.com/PamplemousseMR/LIBUSBNGINE.svg?branch=master)](https://travis-ci.com/PamplemousseMR/LIBUSBNGINE)

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

- [Conan](https://conan.io/) : The C / C++ Package Manager for Developers.
- [Libusb](https://github.com/libusb/libusb) : A cross-platform library to access USB devices.

### Generation

Add bincrafters remote : `conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan`

Use conan to download/build libraries : `conan install -s build_type=Release -if C:\build_release .`

Generate using cmake in the same build directory than conan: `cmake`.

## Authors

* **MANCIAUX Romain** - *Initial work* - [PamplemousseMR](https://github.com/PamplemousseMR).

## License

This project is licensed under the GNU Lesser General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details.