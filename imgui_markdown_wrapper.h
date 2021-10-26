#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct {
		char* link;
		int link_len;
	} iggMarkdownLinkCallbackData;

        extern iggMarkdownLinkCallbackData iggMarkdown(char *markdown_);
#ifdef __cplusplus
}
#endif
