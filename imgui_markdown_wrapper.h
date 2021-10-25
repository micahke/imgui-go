#pragma once

typedef struct {
        char* link;
        int link_len;
        //IggBool isImage;
} iggMarkdownLinkCallbackData;

#ifdef __cplusplus
extern "C"
{
#endif
    extern void iggMarkdown(char *markdown_);
    extern iggMarkdownLinkCallbackData iggMarkdownLink;
#ifdef __cplusplus
}
#endif
