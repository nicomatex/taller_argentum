#include "chat.h"

#include "client_config.h"

Chat::Chat(SDLArea chat_area, int nlines, SDL_Renderer* renderer)
    : text_input(SDLArea(chat_area.getX(),
                         chat_area.getY() +
                             ((chat_area.getHeight() / nlines) * (nlines - 1)),
                         chat_area.getWidth(), chat_area.getHeight() / nlines),
                 CHAT_FONT, renderer, CHAT_INPUT_FONT_COLOR,
                 CHAT_INPUT_BACKGROUND_COLOR),
      text_box(
          SDLArea(chat_area.getX(), chat_area.getY(), chat_area.getWidth(),
                  chat_area.getHeight() - (chat_area.getHeight() / nlines)),
          CHAT_FONT, renderer, nlines - 1, CHAT_BOX_FONT_COLOR,
          CHAT_BOX_BACKGROUND_COLOR) {}

Chat::~Chat(){}

void Chat::add_characters(char* characters){
    text_input.add_characters(characters);
}

void Chat::input_erase(){
    text_input.erase();
}

std::string Chat::get_input_and_erase(){
    std::string input = text_input.get_text();
    text_input.erase_all();
    return input;
}

void Chat::print_line(std::string line){
    text_box.add_line(line);
}

void Chat::render(){
    text_input.render();
    text_box.render();
}

void Chat::toggle(){
    text_input.toggle();
}