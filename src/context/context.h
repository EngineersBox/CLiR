#pragma once

#ifndef CLIR_CONTEXT_H
#define CLIR_CONTEXT_H

#ifdef __cplusplus

#include <stddef.h>

#define MAX_FRAMEBUFFERS 1024;

typedef struct CLiRFramebufferContext {
	size_t read;
	size_t write;
	size_t buffers[MAX_FRAMEBUFFERS];
} CLiRFramebufferContext;

typedef struct CLiRContext {
	CLiRFramebufferContext framebuffers;
} CLiRContext;

CLiRContext clirCreateContext();

#endif // __cplusplus

#endif // CLIR_CONTEXT_H
