#include "context.h"

CLiRContext clirCreateContext() {
	CLiRContext ctx = (CLiRContext) {
		.framebuffers = (CLiRFramebufferContext) {
			.read = 0,
			.write = 0,
			.buffers = {},
		},
	};
	return ctx;
}
