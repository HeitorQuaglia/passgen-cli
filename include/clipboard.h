#ifndef CLIPBOARD_H
#define CLIPBOARD_H

#ifdef __cplusplus
extern "C" {
#endif

/// Códigos de retorno
#define CLIP_SUCCESS 0
#define CLIP_ERROR   -1

int copy_to_clipboard(const char *text);

#ifdef __cplusplus
}
#endif

#endif // CLIPBOARD_H
