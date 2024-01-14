# Bit-Tangler

Bit-Tangler facilitates controlled file corruption through byte overwrites. Users can specify the percentage of data to be affected, introducing a touch of randomness for realistic scenarios. Tailor the intensity for controlled testing, providing a user-friendly tool to explore and fortify data integrity with precision.

## Download and Compilation
### Prerequisites:
- git
- gcc
- make

Clone the repository and run the Makefile:
```shell
git clone https://github.com/ThomasWaytec/Bit-Tangler.git
cd ./Bit-Tangler
make
```

## Usage
Type in ```./tangler``` followed by the name of the file you'd like to corrupt. 

### Intensity Level:
You can use `--intensity` or `-i`followed by the intensity level to tell how much you want the file to be corrupted.
Where the intensity level is: intensity > 0 and intensity < 101

### Examples:
``` shell
./tangler image.jpg
./tangler usernames.txt -i 50
./tangler program.exe --intensity 3 
./tangler.exe videos/movie.mp4 -i 100