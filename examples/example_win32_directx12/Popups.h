#pragma once

namespace MyApp
{
    bool* RenderPopups(bool* menu_flags);

    void ToggleFullscreen();

    enum class Themes;
    Themes GetTheme();
    void ToggleTheme();
}
