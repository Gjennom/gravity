#include "banner.h"

int main(int argc, char *argv[]) {
    string text = get_text(argc, argv);
    Letter_Blocks blocks = get_blocks("matrix_5x7.txt");
    int text_width = 10;
    int text_height = get_text_height(text, text_width);
    Picture picture = make_picture(text_width, text_height);
    int text_row = 0, text_column = 0;
    for (char letter : text) {
        draw_letter(picture, letter, blocks,
                    text_row, text_column);
        advance_text_position(text_width, text_row, text_column);
    }
    print_picture(picture);
    return 0;
}

