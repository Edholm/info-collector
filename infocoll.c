#include <stdio.h>
#include <unistd.h>  /* sleep() */
#include <jansson.h> /* JSON support */
#include "blocks.h"

static const char *HEADER = "{\"version\":1}\n[[],\n";

/* Setup the blocks we want and return the "head" of the LinkedList */
Block* setup_blocks() {
    Block *b = malloc(sizeof(Block));
    b->full_text = "apabepa";

    return b;
}

int main(void)
{
    printf(HEADER);
    fflush(stdout);
    /* Give i3bar time to read the header */
    sleep(1);

    Block *first_block = setup_blocks();
    json_t *tmp;
    while(1) {
        tmp = build_block_chain(first_block);
        printf("%s\n", json_dumps(tmp, JSON_INDENT(4)));
        fflush(stdout);
        json_decref(tmp);
        sleep(1);
    }
    return 0;
}
