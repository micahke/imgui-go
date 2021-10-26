package imgui

// #include "imgui_markdown_wrapper.h"
import "C"

type MarkdownHeaderData struct {
	Font         Font
	HasSeparator bool
}

type MarkdownImageData struct {
	TextureID TextureID
	Size      Vec2
}

var markdownImageCallbackCache func(url string) MarkdownImageData = func(_ string) (result MarkdownImageData) {
	return MarkdownImageData{TextureID: 0}
}

func Markdown(data *string, linkCB func(s string), imageCB func(path string) MarkdownImageData, headers []MarkdownHeaderData) {
	markdownImageCallbackCache = imageCB
	state := newInputTextState(*data, nil)
	defer func() {
		*data = state.buf.toGo()
		state.release()
	}()

	cHeaders := []C.iggMarkdownHeaderData{}
	if headers != nil {
		for _, data := range headers {
			cHeaders = append(cHeaders,
				C.iggMarkdownHeaderData{
					font:      data.Font.handle(),
					separator: castBool(data.HasSeparator),
				},
			)
		}
	}

	var cHeadersPtr *C.iggMarkdownHeaderData
	if len(cHeaders) > 0 {
		cHeadersPtr = &cHeaders[0]
	}

	linkData := C.iggMarkdown(
		(*C.char)(state.buf.ptr),
		cHeadersPtr, (C.int)(len(cHeaders)),
	)

	s := C.GoString(linkData.link)
	s = s[:int(linkData.link_len)]
	if s != "" {
		linkCB(s)
	}
}

//export goMarkdownImageCallback
func goMarkdownImageCallback(data C.iggMarkdownLinkCallbackData) (result C.iggMarkdownImageData) {
	if markdownImageCallbackCache == nil {
		return result
	}

	path := C.GoString(data.link)
	path = path[:int(data.link_len)]
	d := markdownImageCallbackCache(path)

	sizeArg, _ := d.Size.wrapped()

	result.texture = d.TextureID.handle()
	result.size = *sizeArg

	return result
}
