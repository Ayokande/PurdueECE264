#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"

int main (int argc, char* argv[])
{
mintf("5796364987");
mintf("That %c look real good today", "b");
mintf("The weather will be 50 degreees.");
mintf("%s has %d calories", "Pringles", 150);
mintf("He's so broke, he has a %d bank overdraft", -500);
mintf("A computer treats %d ad %b", 124, 124);
mintf("Look what %d looks like in hexadecimal %x", 200, 200);
mintf("I love myself %d times more than I hate her.", 1200);
return EXIT_SUCCESS;
}
