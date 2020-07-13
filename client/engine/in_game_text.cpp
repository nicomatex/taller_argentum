#include "in_game_text.h"
#include "resource_manager.h"
#include "engine_config.h"

InGameText::InGameText(const std::string& text, SDL_Color color, int font_id,
                       visual_info_t visual_info)
    : RenderizableObject(visual_info),
      render_text(text,
                  ResourceManager::get_instance().get_bitmap_font(font_id),
                  color) {
    float size_proportion =
        (float)render_text.get_width() / (float)render_text.get_height();
    this->visual_info.width = this->visual_info.height * size_proportion;
    
    int width_excess = SIZE_GRANULARITY - (this->visual_info.width / 2);
    int offset_x = width_excess / 2;
    this->visual_info.offset_x = offset_x;
}

void InGameText::update_text(const std::string& text) {
    render_text.update_text(text);
    float size_proportion =
        (float)render_text.get_width() / (float)render_text.get_height();
    this->visual_info.width = this->visual_info.height * size_proportion;
    int width_excess = SIZE_GRANULARITY - (this->visual_info.width / 2);
    int offset_x = width_excess / 2;
    this->visual_info.offset_x = offset_x;
}

void InGameText::render(SDL_Rect dest) { render_text.render(dest); }