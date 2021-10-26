#pragma once

#include "imguiWrapperTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif
	typedef struct {
		char* link;
		int link_len;
	} iggMarkdownLinkCallbackData;

        typedef struct {
                IggFont font;
                IggBool separator;
        } iggMarkdownHeaderData;

        extern iggMarkdownLinkCallbackData iggMarkdown(
                        char *markdown_,
                        iggMarkdownHeaderData fonts[], int numHeaderLevels
                );
#ifdef __cplusplus
}
#endif
