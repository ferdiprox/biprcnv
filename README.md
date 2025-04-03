
# Biprolex resources Converter

A some little tool that i created long ago to modify Biprolex's audio files and get their versions in modern formats, with full quality. 

It uses SFML as a library to change audio files, just because its simple to use for me.

## Building 

Just creating a `build` folder, generating files for Ninja generator in it, and then `ninja` does all the magic. Thats all.

Example:
```
git clone https://github.com/ferdiprox/biprcnv
cd biprcnv
mkdir build
cd build
cmake -G Ninja ../
ninja
```

Dont forget to install all the dependences (sfml, git, cmake, ninja).
