# Findit

this stupid simple app came when i was in process of developing a basic git like clone (will be made public soon) and i made a parser that parses the whole directory recursively and prints everything
and this was born from that with a few tweaks to the code it works well for now 

## Usage:

```
Usage findit <PATH> <KEYWORD> <Ignore DIR/FILE> < -sh Search hidden by default hidden files are skipped>
OR findit -version 
Minimum usage findit <PATH> <KEYWORD>
```

Example:
``` findit . findit ```

## Build and Install:
Build with ```make all```

Then install with:
``` sudo chmod +x install.sh && ./install.sh```

### IM IN LOVE WITH C 
