# ImCtrl
An image viewer app, optimised for use with a gamepad.

## Getting started
If you just want to use the app, a pre-built executable will soon be provided in [Releases](https://github.com/photoshopdan/ImCtrl/releases). Alternatively you can build it yourself, as shown below.

### Prerequisites
- Git.
- CMake 3.26 or higher.

### Installation
Clone this repository recursively:
```Shell
git clone --recurse-submodules https://github.com/photoshopdan/ImCtrl.git
```
To configure and build from the project directory:
```Shell
cmake -S . -B build
cmake --build build --config Release --parallel 8
```
