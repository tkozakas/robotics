# Robotika 7 Semestras

## Setting up Arduino on Linux

### Installation
Download arduino-cli [here](https://arduino.github.io/arduino-cli/0.35/installation/) or if you are on linux:
```bash
sudo pacman -S arduino-cli
sudo pacman -S screen
```

### Grant Temporary USB Permissions (linux)

```bash
sudo chmod a+rw /dev/ttyACM0
sudo usermod -aG dialout $USER
```

## Configure Arduino

```bash
arduino-cli config init
arduino-cli core update-index
arduino-cli core install arduino:avr
arduino-cli lib install "Servo"
arduino-cli lib install "LiquidCrystal"
arduino-cli lib install "TimerOne"
```

## Compiling and Uploading Sketches

```bash
arduino-cli compile --fqbn arduino:avr:uno Timer && arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:uno Timer
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
