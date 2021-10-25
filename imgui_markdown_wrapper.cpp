/*
 * =====================================================================================
 *
 *       Filename:  imgui_markdown_wrapper.cpp
 *
 *    Description:  wrapper for imgui_markdown.h
 *
 * =====================================================================================
 */


#include	<imgui.h>
#include	<imgui_markdown.h>
#include	<imgui_markdown_wrapper.h>

void iggMarkdown(char* markdown_) {
    ImGui::MarkdownConfig mdConfig;

    //mdConfig.linkCallback =         LinkCallback;
    //mdConfig.tooltipCallback =      NULL;
    //mdConfig.imageCallback =        ImageCallback;
    //mdConfig.linkIcon =             ICON_FA_LINK;
    //mdConfig.headingFormats[0] =    { H1, true };
    //mdConfig.headingFormats[1] =    { H2, true };
    //mdConfig.headingFormats[2] =    { H3, false };
    //mdConfig.userData =             NULL;
    //mdConfig.formatCallback =       ExampleMarkdownFormatCallback;
    ImGui::Markdown( markdown_, strlen(markdown_), mdConfig );
}
