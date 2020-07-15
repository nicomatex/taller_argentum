#include "text_input.h"

#include <iostream>

TextInput::TextInput(SDL_Rect render_area, SDL_Renderer* renderer,
                     SDL_Color font_color, SDL_Color background_color,
                     TTF_Font* font, uint64_t max_len)
    : render_area(render_area),
      render_text("", font, font_color, renderer),
      enabled(false),
      renderer(renderer),
      render_blink(true),
      background_color(background_color),
      max_len(max_len) {
    blink_timer.start();
}

TextInput::~TextInput() {}

void TextInput::add_characters(const char* characters) {
    if (text.length() >= max_len)
        return;
    text += characters;
    render_text.update_text(text);
    blink_timer.start();
    render_blink = true;
}

void TextInput::erase() {
    if (text.length() > 0) {
        text.pop_back();
    }
    render_text.update_text(text);
    blink_timer.start();
    render_blink = true;
}

void TextInput::toggle() {
    enabled = !enabled;
    if (enabled) {
        render_blink = true;
        blink_timer.start();
    } else {
        blink_timer.stop();
    }
}

void TextInput::render_cursor() {
    if (!enabled)
        return;
    if (blink_timer.get_ticks() > 500) {
        render_blink = !render_blink;
        blink_timer.start();
    }

    if (!render_blink)
        return;

    float scale_factor = (float)render_area.h / (float)render_text.get_height();
    int text_width = render_text.get_width() * scale_factor;
    int cursor_base_x = text_width + render_area.x;
    if (cursor_base_x > render_area.x + render_area.w) {
        cursor_base_x = render_area.x + render_area.w;
    } else if (text == "") {
        cursor_base_x = render_area.x + 1;
    }
    int cursor_base_y = render_area.y + 3;
    int cursor_height = render_area.h - 3;
    int cursor_width = 2;

    SDL_Rect cursor_rect = {cursor_base_x, cursor_base_y, cursor_width,
                            cursor_height};

    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderFillRect(renderer, &cursor_rect);
}

void TextInput::render_background() {
    SDL_Rect background_area = render_area;

    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                           background_color.b, background_color.a);
    SDL_RenderFillRect(renderer, &background_area);
}

void TextInput::render() {
    render_background();
    float scale_factor = (float)render_area.h / (float)render_text.get_height();
    int dest_width = render_text.get_width() * scale_factor;
    int dest_height = render_text.get_height() * scale_factor;
    SDL_Rect render_origin = {0, 0, render_text.get_width(),
                              render_text.get_height()};

    if (dest_width > render_area.w) {
        int max_real_width = render_area.w / scale_factor;
        dest_width = render_area.w;
        render_origin.x = render_text.get_width() - max_real_width;
    }

    SDL_Rect render_dest = {render_area.x, render_area.y, dest_width,
                            dest_height};
    render_text.render(render_origin, render_dest);
    render_cursor();
}

std::string TextInput::get_text() {
    return text;
}

void TextInput::erase_all() {
    text = "";
    render_text.update_text(text);
}