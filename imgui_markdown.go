package imgui

// #include "imgui_markdown_wrapper.h"
import "C"

type MarkdownHeaderData struct {
	Font         Font
	HasSeparator bool
}

func Markdown(data *string, linkCB func(s string), headers []MarkdownHeaderData) {
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
