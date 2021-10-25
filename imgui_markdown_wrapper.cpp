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

iggMarkdownLinkCallbackData iggMarkdownLink;
static void markdownLinkCallback(ImGui::MarkdownLinkCallbackData);

void iggMarkdown(char* markdown_) {
        // clean up link callbacks
        iggMarkdownLink.link = NULL;
        iggMarkdownLink.link_len = 0;

        ImGui::MarkdownConfig mdConfig;

        mdConfig.linkCallback =         markdownLinkCallback;
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

void markdownLinkCallback(ImGui::MarkdownLinkCallbackData data_) {
       iggMarkdownLink.link = (char*)(data_.link);
       iggMarkdownLink.link_len = data_.linkLength;
       // is image
}
