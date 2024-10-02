# Robotika 7 Semestras

## Setting up Arduino on Linux

### Installation

```bash
sudo pacman -S arduino-cli
sudo pacman -S screen
```

### Grant Temporary USB Permissions

```bash
sudo chmod a+rw /dev/ttyACM0
```

## Configure Arduino

```bash
arduino-cli config init
arduino-cli core update-index
arduino-cli core install arduino:avr
```

## Compiling and Uploading Sketches

```bash
arduino-cli compile --fqbn arduino:avr:uno Timer/Timer.ino
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Timer/Timer.ino
```

## Useful commands

### Install Libraries

```bash
arduino-cli lib search "LibraryName"
arduino-cli lib install "LibraryName"
```

### List Installed Libraries

```bash
arduino-cli lib list
```

### Real time arduino statements (useful for debugging)

```bash
screen /dev/ttyACM0 9600
```
