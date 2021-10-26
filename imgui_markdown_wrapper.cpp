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
#include	<WrapperConverter.h>

iggMarkdownLinkCallbackData iggMarkdownLink;
static void markdownLinkCallback(ImGui::MarkdownLinkCallbackData);

iggMarkdownLinkCallbackData iggMarkdown(
                char* markdown_,
                iggMarkdownHeaderData headers_[], int numHeaderLevels
        ) {
        // clean up link cache.
        iggMarkdownLink.link = NULL;
        iggMarkdownLink.link_len = 0;

        // create imgui markdown config:
        // TODO: implement all these methods
        ImGui::MarkdownConfig mdConfig;

        mdConfig.linkCallback =         markdownLinkCallback;
        for ( int i = 0; i < numHeaderLevels; i++ ) {
                ImFont* font = reinterpret_cast<ImFont *>(headers_[i].font);
                mdConfig.headingFormats[i] = { font, (bool)(headers_[i].separator) };
        }
        //mdConfig.tooltipCallback =      NULL;
        //mdConfig.imageCallback =        ImageCallback;
        //mdConfig.linkIcon =             ICON_FA_LINK;
        //mdConfig.userData =             NULL;
        //mdConfig.formatCallback =       ExampleMarkdownFormatCallback;
        
        // run ImGui Markdown
        ImGui::Markdown( markdown_, strlen(markdown_), mdConfig );

	return iggMarkdownLink;
}

void markdownLinkCallback(ImGui::MarkdownLinkCallbackData data_) {
       iggMarkdownLink.link = (char*)(data_.link);
       iggMarkdownLink.link_len = data_.linkLength;
       // is image
}
