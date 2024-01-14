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
Type in `./tangler` followed by the name of the file you'd like to corrupt.
Add optional intensity level after.

### Intensity Level:
Use `--intensity` or `-i` followed by a level (1 to 100) to specify the degree of file corruption. The intensity level should be in the range of 1 to 100 (including).

### Examples:
``` shell
./tangler image.jpg
./tangler usernames.txt -i 50
./tangler program.exe --intensity 3 
./tangler videos/movie.mp4 -i 100