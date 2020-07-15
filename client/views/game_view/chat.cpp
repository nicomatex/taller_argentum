#include "chat.h"

#include "../../client_config.h"

Chat::Chat(SDL_Rect chat_area, int nlines, SDL_Renderer* renderer,
           TTF_Font* font)
    : text_input(
          {chat_area.x, chat_area.y + ((chat_area.h / nlines) * (nlines - 1)),
           chat_area.w, chat_area.h / nlines},
          renderer, CHAT_INPUT_FONT_COLOR, CHAT_INPUT_BACKGROUND_COLOR, font),
      text_box({chat_area.x, chat_area.y, chat_area.w,
                chat_area.h - (chat_area.h / nlines)},
               renderer, nlines - 1, CHAT_BOX_FONT_COLOR,
               CHAT_BOX_BACKGROUND_COLOR, font) {}

Chat::~Chat() {}

void Chat::add_characters(const char* characters) {
    text_input.add_characters(characters);
}

void Chat::input_erase() {
    text_input.erase();
}

std::string Chat::get_input_and_erase() {
    std::string input = text_input.get_text();
    text_input.erase_all();
    return input;
}

void Chat::print_line(std::string line) {
    text_box.add_line(line);
}

void Chat::render() {
    text_input.render();
    text_box.render();
}

void Chat::toggle() {
    text_input.toggle();
}