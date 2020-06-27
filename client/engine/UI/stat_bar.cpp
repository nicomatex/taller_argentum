#include "stat_bar.h"

StatBar::StatBar(SDL_Rect render_area, TTF_Font* font, SDL_Renderer* renderer,
                 unsigned int max_value, SDL_Color bar_color,
                 SDL_Color text_color)
    : renderer(renderer),
      render_area(render_area),
      bar_color(bar_color),
      render_text("", font, text_color, renderer),
      max_value(max_value),
      current_value(max_value) {
    render_text.set_style(TTF_STYLE_BOLD);
    render_text.update_text(std::to_string(current_value) + "/" + std::to_string(max_value));
}

StatBar::~StatBar() {}

void StatBar::_render_text() {
    int x_center = render_area.x + (render_area.w / 2);
    int y_center = render_area.y + (render_area.h / 2);
    float scale_factor = (float)render_area.h / (float)render_text.get_height();

    int dest_width = render_text.get_width() * scale_factor;
    int dest_height = render_text.get_height() * scale_factor;

    int dest_x = x_center - (dest_width / 2);
    int dest_y = y_center - (dest_height / 2);

    SDL_Rect dest = {dest_x, dest_y, dest_width, dest_height};
    render_text.render(dest);
}

void StatBar::_render_bar() {
    SDL_Rect bar_area = render_area;
    float fill_proportion = (float)current_value / (float)max_value;
    bar_area.w *= fill_proportion;
    
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, bar_color.r, bar_color.g,
                           bar_color.b, bar_color.a);
    SDL_RenderFillRect(renderer, &bar_area);
}

void StatBar::set_current_value(unsigned int new_current_value){
    current_value = new_current_value;
    if(current_value > max_value) current_value = max_value;
    render_text.update_text(std::to_string(current_value) + "/" +
                            std::to_string(max_value));
}

void StatBar::set_max_value(unsigned int new_max_value){
    max_value = new_max_value;

    /* Para truncar el valor actual de ser necesario
    y actualizar el texto.*/
    set_current_value(current_value);
}

void StatBar::render(){
    _render_bar();
    _render_text();
}