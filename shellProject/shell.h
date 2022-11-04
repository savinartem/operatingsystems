#ifndef SHELL_H
#define SHELL_H

void print_promtWevlcom()
{   
    int num=1830;
    printf("\t\t\t-------------------------------------\n");
     printf("\t\t\t\t GroupProject\n\t\t\t\t  GroupName: %d\n",num);
     printf("\t\t\t-------------------------------------\n");
}
void print_prompt1(void)
{
    fprintf(stderr, "=)\t");
}
char *read_cmd();




#endif
