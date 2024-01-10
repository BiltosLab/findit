# Findit

this stupid simple app does exactly what ```find``` does on unix systems it came to live when i was in process of developing a basic git like clone (will be made public soon) and i made a parser that parses the whole directory recursively sadly its slow when using in huge dirs etc but for normal use it functions almost like ```find``` in unix systems.

this was meant to be educational nothing more nothing less.


## Usage:

```
Usage findit <PATH> <KEYWORD> <Ignore DIR/FILE> < -sh Search hidden by default hidden files are skipped>
OR findit -version 
Minimum usage findit <PATH> <KEYWORD>
```

Example:
``` findit . findit ```

## Build and Install:
Only Unix-like OSes are supported i do not use windows.
this was not tested on anything other than arch linux but it should work on MacOS and BSDs
GCC and Make are required to build

Build with ```make all```

Then install with:
``` sudo chmod +x install.sh && ./install.sh```

