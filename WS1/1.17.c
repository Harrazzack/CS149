#include <stdio.h>

int main(void) {
   int baseInt;
   int headInt;
   printf("Enter base Integer: ");
   scanf("%d",&baseInt);
   printf("Enter head Integer: ");
   scanf("%d",&headInt);

   /* Type your code here. */
   printf("    %d\n", headInt);
   printf("    %d%d\n",headInt,headInt);
   printf("%d%d%d%d",baseInt,baseInt,baseInt,baseInt);
   printf("%d%d%d\n",headInt,headInt,headInt);
   printf("%d%d%d%d",baseInt,baseInt,baseInt,baseInt);
   printf("%d%d%d%d\n",headInt,headInt,headInt,headInt);
   printf("%d%d%d%d",baseInt,baseInt,baseInt,baseInt);
   printf("%d%d%d\n",headInt,headInt,headInt);
   printf("    %d%d\n",headInt,headInt);
   printf("    %d\n",headInt);

   
   return 0;
}
