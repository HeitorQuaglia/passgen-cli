#include "clipboard.h"
#include <stdio.h>
#include <stdlib.h>

#if defined(__APPLE__)
static const char *clipboard_cmds[] = {
    "pbcopy"
};
#elif defined(__linux__) || defined(__unix__) \
   || defined(__FreeBSD__) || defined(__NetBSD__) \
   || defined(__OpenBSD__)
static const char *clipboard_cmds[] = {
    "wl-copy",
    "xclip -selection clipboard",
    "xsel --clipboard --input"
};
#else
static const char *clipboard_cmds[] = {
    "xclip -selection clipboard",
    "xsel --clipboard --input"
};
#endif

static const size_t clipboard_cmd_count =
    sizeof(clipboard_cmds) / sizeof(clipboard_cmds[0]);

static int exec_copy(const char *cmd, const char *text) {
    FILE *fp = popen(cmd, "w");
    if (!fp) return CLIP_ERROR;
    fputs(text, fp);
    int rc = pclose(fp);
    return (rc == 0) ? CLIP_SUCCESS : CLIP_ERROR;
}

int copy_to_clipboard(const char *text) {
    if (!text) return CLIP_ERROR;

    for (size_t i = 0; i < clipboard_cmd_count; ++i) {
        if (exec_copy(clipboard_cmds[i], text) == CLIP_SUCCESS) {
            return CLIP_SUCCESS;
        }
    }
    return CLIP_ERROR;
}
