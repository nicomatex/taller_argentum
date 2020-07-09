#include "in_game_text.h"

#include "resource_manager.h"
#include "visual_config.h"
#include "engine_config.h"

InGameText::InGameText(visual_info_t visual_info, std::string text, int max_size)
    : RenderizableObject(visual_info),
      render_text(ResourceManager::get_instance().create_text(
          get_offseted_text(text,max_size), NAME_TEXT_FONT_ID,NAME_COLOR)) {

}


std::string InGameText::get_offseted_text(const std::string& text, int total_size){
    std::string padded_text = text;
    if(text.size() > total_size){
        return text.substr(0,total_size);
    }
    int total_padding = total_size - text.size();
    int left_offset = total_padding / 2;
    padded_text.insert(0,left_offset,' ');
    return padded_text;
}

void InGameText::update_text(const std::string& text) {
    render_text.update_text(text);
}

void InGameText::render(SDL_Rect dest) {
    float scale_factor = (float)dest.h / (float)render_text.get_height();
    dest.w = render_text.get_width() * scale_factor;
    render_text.render(dest);
}