# parenthesis

this is a calculator made in c

no external libraries required

## how it works

1. tokenize (2 + 2 -> \[number 2\] \[plus\] \[number 2\])
2. validate (can't have 2 numbers right after each other, same with ops, also check parentheses)
3. solve

### the solving

the solving happens by simplyfing all parentheses until we get the simplest form of the expression (aka how humans solve math)

* (2 + 2 - (5 - 3)) + (2 - (54 - 52) + (32 / 16) - 1)
* (2 + 2 - 2) + (2 - (54 - 52) + (32 / 16) - 1)
* 2 + (2 - (54 - 52) + (32 / 16) - 1)
* 2 + (2 - 2 + 2 - 1)
* 2 + 1
* 3

i made it in 1 night
