/*reverse.c */
#include <stdio.h>
#include <string.h>


reverse(char *before, char *after);

main()
{
	char str[100];    /*Buffer to hold reversed string */
	reverse("cat", str);  /*Reverse the string "cat" */
	printf("reverse(\"cat\")=%s\n", str); /*Display result */
	reverse("noon", str); /*Reverse the string "noon" */
	printf("reverse(\"noon\")=%s\n", str); /*Display result */
	
}

reverse(char *before, char *after)
{
	int i;
	int j;
	int len;
	len=strlen(before);

	for(j=len-1, i=0; j>=0; j--, i++){
		after[i]=before[j];
       // printf(after[i]);  
    }  
	after[len]=NULL;
}
