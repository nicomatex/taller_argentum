#include "responsive_scaler.h"

ResponsiveScaler::ResponsiveScaler(SDLWindow &window, int prototype_width,
                                   int prototype_height)
    : window(window),
      scale_factor_w((float)window.get_width() / (float)prototype_width),
      scale_factor_h((float)window.get_height() / (float)prototype_height) {}

SDL_Rect ResponsiveScaler::scale(SDL_Rect unscaled_rect) {
    return {(int)(unscaled_rect.x * scale_factor_w),
            (int)(unscaled_rect.y * scale_factor_h),
            (int)(unscaled_rect.w * scale_factor_w),
            (int)(unscaled_rect.h * scale_factor_h)};
}

int ResponsiveScaler::simple_scale(int dimension) {
    return (int)(dimension * scale_factor_w);
}

ResponsiveScaler::~ResponsiveScaler() {}