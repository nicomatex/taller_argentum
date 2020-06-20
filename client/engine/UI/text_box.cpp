#include "text_box.h"

#include <iostream>

TextBox::TextBox(SDL_Rect render_area, const std::string& font_file,
                 SDL_Renderer* renderer, int nlines, SDL_Color font_color,
                 SDL_Color background_color)
    : render_area(render_area),
      renderer(renderer),
      nlines(nlines),
      background_color(background_color) {
    for (int i = 0; i < nlines; i++) {
        render_lines.emplace_back("", font_file, font_color, renderer);
    }
}

TextBox::~TextBox() {}

void TextBox::erase_all() { lines.empty(); }

void TextBox::add_line(std::string line) {
    if (line == "") return;
    lines.emplace_front(line);
    if (lines.size() > nlines) {
        lines.pop_back();
    }
    for (int i = 0; i < lines.size(); i++) {
        render_lines[i].update_text(lines[i]);
    }
}

void TextBox::render_background() {
    SDL_Rect background_area = render_area;
    // SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, background_color.r, background_color.g,
                           background_color.b, background_color.a);
    SDL_RenderFillRect(renderer, &background_area);
}

void TextBox::render() {
    render_background();
    int line_height = render_area.h / nlines;
    float scale_factor =
        (float)line_height / (float)render_lines[0].get_height();

    for (int i = 0; i < nlines; i++) {
        int dest_width = render_lines[i].get_width() * scale_factor;
        int dest_height = render_lines[i].get_height() * scale_factor;

        SDL_Rect render_origin = {0, 0, render_lines[i].get_width(),
                                  render_lines[i].get_height()};
        SDL_Rect render_dest = {render_area.x,
                                render_area.y + (nlines - i - 1) * line_height,
                                dest_width, dest_height};
        render_lines[i].render(render_origin, render_dest);
    }

    /*if (dest_width > render_area.getWidth()) {
        int max_real_width = render_area.getWidth() / scale_factor;
        dest_width = render_area.getWidth();
        render_origin.set_new_pos(render_text.get_width() - max_real_width, 0);
    }*/
}