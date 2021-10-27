package imgui

// #include "imgui_markdown_wrapper.h"
import "C"

type MarkdownHeaderData struct {
	Font         Font
	HasSeparator bool
}

type MarkdownImageData struct {
	TextureID *TextureID
	Size      Vec2
}

var markdownImageCallbackCache func(url string) MarkdownImageData

var markdownImageCache map[string]*MarkdownImageData

func init() {
	markdownImageCache = make(map[string]*MarkdownImageData)
}

// Markdown implements imgui_markdown.h
// NOTE about arguments:
// - data is pointer to markdown text data
// - linkCB is callback called when link is clicked (it should most likely open link in a web browser)
// - imageCB is expected to load an image at `path` and return POINTER to its texture with some other
//   stats. BE AWARE that imageCB MUST NOT pause goroutine. It could e.g.:
//   - create variable with TextureID = 0
//   - invoge a new goroutine and load the texture there and set pointers value
//   - return pointer to declared variable
// - headers are headers formatting data. Note, that first index of slice will be applied
//   to top-level (H1), second for H2 and so on.
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
	if _, found := markdownImageCache[path]; !found {
		d := markdownImageCallbackCache(path)
		markdownImageCache[path] = &d
	}

	d := markdownImageCache[path]
	if d.TextureID == nil || *d.TextureID == 0 {
		return result
	}

	sizeArg, _ := d.Size.wrapped()

	result.texture = d.TextureID.handle()
	result.size = *sizeArg

	return result
}
