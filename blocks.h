#ifndef BLOCKS_H
#define BLOCKS_H

#include <stdint.h>  /* uint8_t etc */

/* Format specifiers */
#define STR_F  "ss"
#define BOOL_F "sb"
#define INT_F  "si"

extern const char *ALIGN_STR[];
enum Align {
    DEFAULT,
    left,
    center,
    right,
};

/* Available block values in i3bar (that are useful...) */
typedef struct Block {
    char *full_text;
    char *color;
    uint8_t separator;
    uint8_t sep_block_width;
    char *short_text;
    uint8_t min_width;
    enum Align align;
    uint8_t urgent;
    struct Block *next;
} Block;

json_t *build_block_chain(Block*);
json_t *block_to_json(Block*);

#endif
