#include <stdio.h>
#include <stdint.h>
#include <unistd.h>  /* sleep() */
#include <jansson.h> /* JSON support */
#include <string.h>

/* Format specifiers */
#define STR_F  "ss"
#define BOOL_F "sb"
#define INT_F  "si"

const char *ALIGN_STR[] = {"default", "left", "center", "right"};
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

/* Take an i3bar block and convert it to a json_t object */
json_t *block_to_json(Block *b) {
    char *c_form   = (b->color)           ? STR_F  : "";
    char *sep_form = (b->separator)       ? BOOL_F : "";
    char *sbw_form = (b->sep_block_width) ? INT_F  : "";
    char *st_form  = (b->short_text)      ? STR_F  : "";
    char *mw_form  = (b->min_width)       ? INT_F  : "";
    char *a_form   = (b->align)           ? STR_F  : "";
    char *u_form   = (b->urgent)          ? BOOL_F : "";

    // 8 fields in the struct and two {}... Magic numbers FTW
    char *format_str = malloc(sizeof(char) * 8*2 + (sizeof(char) * 2));

    sprintf(format_str, "{ss, %s%s%s%s%s%s%s}",
            c_form, sep_form, sbw_form,
            st_form, mw_form, a_form, u_form);
    json_t *result = json_pack(format_str,
                    "full_text", b->full_text,
                    "color", b->color,
                    "separator", b->separator,
                    "separator_block_width", b->sep_block_width,
                    "short_text", b->short_text,
                    "min_width", b->min_width,
                    "align", ALIGN_STR[b->align],
                    "urgent", b->urgent);
    free(format_str);
    return result;
}

/* Return a json_t array of all blocks following _start_block_ */
json_t *build_block_chains(Block *start_block) {
    json_t *result = json_array();
    Block *b = start_block;
    do {
        json_array_append_new(result, block_to_json(b));
    } while((b = b->next));
    return result;
}

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
    printf("%s\n", json_dumps(build_block_chains(&b), JSON_INDENT(4)));

    free(txt);
    return 0;
}
