#include <jansson.h> /* JSON support */
#include <string.h>
#include "blocks.h"

const char *ALIGN_STR[] = {"default", "left", "center", "right"};

/* Take an i3bar block and convert it to a json_t object */
json_t *block_to_json(Block *b) {
    char *format_specifiers[] = {
        (b->color)           ? STR_F  : "",
        (b->separator)       ? BOOL_F : "",
        (b->sep_block_width) ? INT_F  : "",
        (b->short_text)      ? STR_F  : "",
        (b->min_width)       ? INT_F  : "",
        (b->align)           ? STR_F  : "",
        (b->urgent)          ? BOOL_F : "",
    };

    size_t elems = sizeof(format_specifiers) / sizeof(char*);
    char *specifiers = calloc(elems, 2);
    for (int i = 0; i < elems; i++) {
        strcat(specifiers, format_specifiers[i]);
    }

    char *format_str = calloc(elems + 4, sizeof(char));
    sprintf(format_str, "{ss%s}", specifiers);
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
    free(specifiers);
    return result;
}

/* Return a json_t array of all blocks following _start_block_ */
json_t *build_block_chain(Block *start_block) {
    json_t *result = json_array();
    Block *b = start_block;
    do {
        json_array_append_new(result, block_to_json(b));
    } while((b = b->next));
    return result;
}
