#pragma once

#ifndef CLIR_FRAMEBUFFER_H
#define CLIR_FRAMEBUFFER_H

#ifdef __cplusplus

#include <stddef.h>

// Generate n buffers and store the names in ids
void clirGenFramebuffers(size_t n, size_t* ids);

#endif // __cplusplus

#endif // CLIR_FRAMEBUFFER_H
