### Portal Gun Arduino

This arduino code is designed to accept input from a rotary encoder and write from an array 

## Changing the Portal List

If you want to change the portal list, simply alter the `dimensions` array found near the top of the main Arduino `portalgun.ino` file (line 28 as of this writing). You must also increase the dimensionCount because apparently you can't just ask an array how many members it has in this language.

## Changing the Default (First) Dimension

The first dimension is defined as `String current = "C137"` on line 26 as of this writing. 
