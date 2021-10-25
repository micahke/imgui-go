package imgui

// #include "imgui_markdown_wrapper.h"
import "C"

func Markdown(data *string, linkCB func(s string)) {
	state := newInputTextState(*data, nil)
	defer func() {
		*data = state.buf.toGo()
		state.release()
	}()

	C.iggMarkdown((*C.char)(state.buf.ptr))
	s := C.GoString(C.iggMarkdownLink.link)
	s = s[:int(C.iggMarkdownLink.link_len)]
	if s != "" {
		linkCB(s)
	}
}
