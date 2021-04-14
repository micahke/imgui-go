#include "wrapper/ConfiguredImGui.h"

// imgui code
// imgui/ is added to include path in wrapper.go
#include "imgui.cpp"
#include "imgui_demo.cpp"
#include "imgui_draw.cpp"
#include "imgui_tables.cpp"
#include "imgui_widgets.cpp"
#ifdef IMGUI_ENABLE_FREETYPE
#include "misc/freetype/imgui_freetype.cpp"
#endif

// imgui-go code
#include "wrapper/Context.cpp"
#include "wrapper/Focus.cpp"
#include "wrapper/DragDrop.cpp"
#include "wrapper/DrawCommand.cpp"
#include "wrapper/DrawData.cpp"
#include "wrapper/DrawList.cpp"
#include "wrapper/Font.cpp"
#include "wrapper/FontAtlas.cpp"
#include "wrapper/FontConfig.cpp"
#include "wrapper/FontGlyphRangesBuilder.cpp"
#include "wrapper/InputTextCallbackData.cpp"
#include "wrapper/IO.cpp"
#include "wrapper/Layout.cpp"
#include "wrapper/ListClipper.cpp"
#include "wrapper/Main.cpp"
#include "wrapper/Popup.cpp"
#include "wrapper/Scroll.cpp"
#include "wrapper/State.cpp"
#include "wrapper/Style.cpp"
#include "wrapper/Tables.cpp"
#include "wrapper/Widgets.cpp"
#include "wrapper/Window.cpp"
#include "wrapper/WrapperConverter.cpp"

// imnodes code
// imnodes/ is added to include path in wrapper.go
#include "imnodes.cpp"

// imgui-go wrapper around imnodes
#include "wrapper/imnodesWrapper.cpp"

// implot code
// implot/ is added to include path in wrapper.go
#include "implot.cpp"
#include "implot_demo.cpp"
#include "implot_items.cpp"

// imgui-go wrapper around implot
#include "wrapper/implotWrapper.cpp"
