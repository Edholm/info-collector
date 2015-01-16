#include <stdio.h>
#include <unistd.h>  /* sleep() */
#include <jansson.h> /* JSON support */
#include "blocks.h"

int main(void)
{
    int counter = 0;
    char *txt = malloc(10), *tmp;
    json_t *footer;

    //printf("{\"version\":1}\n[[],\n");
    fflush(stdout);
    usleep(20000);
    Block b3 = {"bepa", "red", 1, 9, "b", 9, center, .urgent =1};
    Block b2 = {"apa", .next=&b3};
    Block b = {txt, "green", .next=&b2};
    //while(1) {
        sprintf(txt, "TheGrid (-%i db)", counter);
        //footer = block_to_json(&b);
        //tmp = json_dumps(footer, JSON_COMPACT);

        //printf("%s,\n", tmp);
        fflush(stdout);

        counter++;
        //json_decref(footer);
        //free(tmp);
        //sleep(1);
    //}
    printf("%s\n", json_dumps(build_block_chain(&b), JSON_INDENT(4)));

    free(txt);
    return 0;
}
