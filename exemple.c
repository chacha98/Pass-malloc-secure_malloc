#include <stdlib.h>
#include <stdio.h>

int main(){
int *ptr;
ptr = malloc(15); //a block of 15 integers 
    if (ptr != NULL) {
      *(ptr + 5) = 480; // assign 480 to sixth integer 
      printf("Value of the 6th integer is %d",*(ptr + 5));
    }

}
