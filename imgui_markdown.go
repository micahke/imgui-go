package imgui

// #include "imgui_markdown_wrapper.h"
import "C"

func Markdown(data *string) {
	state := newInputTextState(*data, nil)
	defer func() {
		*data = state.buf.toGo()
		state.release()
	}()

	C.iggMarkdown((*C.char)(state.buf.ptr))
}
