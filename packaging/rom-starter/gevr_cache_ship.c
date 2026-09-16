/* Windows implementation for GEVR cache ship stamp helpers. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>

#include "gevr_cache_ship.h"

static void gevr_trim(char *s)
{
    char *start;
    size_t n;

    if (!s || !*s) {
        return;
    }
    start = s;
    while (*start == ' ' || *start == '\t' || *start == '\r' || *start == '\n') {
        start++;
    }
    if (start != s) {
        memmove(s, start, strlen(start) + 1u);
    }
    n = strlen(s);
    while (n > 0 && (s[n - 1] == ' ' || s[n - 1] == '\t' || s[n - 1] == '\r' || s[n - 1] == '\n')) {
        s[n - 1] = '\0';
        n--;
    }
}

const char *gevr_ship_tag_expected(void)
{
    const char *env = getenv("GEVR_SHIP_TAG");
    if (env && env[0]) {
        return env;
    }
    return GEVR_SHIP_TAG_DEFAULT;
}

static int gevr_path_join(const char *dir, const char *leaf, char *out, size_t out_cap)
{
    size_t dlen;
    int need_sep;

    if (!dir || !leaf || !out || out_cap == 0) {
        return -1;
    }
    dlen = strlen(dir);
    need_sep = (dlen > 0 && dir[dlen - 1] != '\\' && dir[dlen - 1] != '/');
    if (dlen + (need_sep ? 1u : 0u) + strlen(leaf) + 1u > out_cap) {
        return -1;
    }
    memcpy(out, dir, dlen);
    if (need_sep) {
        out[dlen++] = '\\';
    }
    memcpy(out + dlen, leaf, strlen(leaf) + 1u);
    return 0;
}

int gevr_ship_stamp_read(const char *cache_dir, char *out, size_t out_cap)
{
    char path[MAX_PATH];
    FILE *f;
    size_t n;

    if (!cache_dir || !out || out_cap < 2) {
        return -1;
    }
    out[0] = '\0';
    if (gevr_path_join(cache_dir, GEVR_CACHE_SHIP_FILE, path, sizeof(path)) != 0) {
        return -1;
    }
    f = fopen(path, "rb");
    if (!f) {
        return -1;
    }
    n = fread(out, 1, out_cap - 1, f);
    fclose(f);
    out[n] = '\0';
    gevr_trim(out);
    return (out[0] != '\0') ? 0 : -1;
}

int gevr_ship_stamp_write(const char *cache_dir, const char *tag)
{
    char path[MAX_PATH];
    FILE *f;

    if (!cache_dir || !tag || !tag[0]) {
        return -1;
    }
    if (gevr_path_join(cache_dir, GEVR_CACHE_SHIP_FILE, path, sizeof(path)) != 0) {
        return -1;
    }
    f = fopen(path, "wb");
    if (!f) {
        return -1;
    }
    fprintf(f, "%s\n", tag);
    fclose(f);
    return 0;
}

static void gevr_delete_if_exists(const char *path)
{
    DeleteFileA(path);
}

int gevr_cache_ready_exists(const char *cache_dir)
{
    char ready_path[MAX_PATH];
    WIN32_FIND_DATAA fd;
    HANDLE h;

    if (!cache_dir) {
        return 0;
    }
    if (gevr_path_join(cache_dir, GEVR_CACHE_READY_FILE, ready_path, sizeof(ready_path)) != 0) {
        return 0;
    }
    h = FindFirstFileA(ready_path, &fd);
    if (h == INVALID_HANDLE_VALUE) {
        return 0;
    }
    FindClose(h);
    return 1;
}

int gevr_ship_stamp_invalidate_if_mismatch(const char *cache_dir)
{
    char ready_path[MAX_PATH];
    char combined_path[MAX_PATH];
    char on_disk[128];
    const char *expected;
    WIN32_FIND_DATAA fd;
    HANDLE h;

    on_disk[0] = '\0';
    if (!cache_dir) {
        return -1;
    }
    if (gevr_path_join(cache_dir, GEVR_CACHE_READY_FILE, ready_path, sizeof(ready_path)) != 0) {
        return -1;
    }
    h = FindFirstFileA(ready_path, &fd);
    if (h == INVALID_HANDLE_VALUE) {
        return 0;
    }
    FindClose(h);

    expected = gevr_ship_tag_expected();
    if (gevr_ship_stamp_read(cache_dir, on_disk, sizeof(on_disk)) != 0) {
        goto invalidate;
    }
    if (_stricmp(on_disk, expected) == 0) {
        return 0;
    }

invalidate:
    gevr_delete_if_exists(ready_path);
    if (gevr_path_join(cache_dir, "combined.bin", combined_path, sizeof(combined_path)) == 0) {
        gevr_delete_if_exists(combined_path);
    }
    if (gevr_path_join(cache_dir, GEVR_CACHE_SHIP_FILE, ready_path, sizeof(ready_path)) == 0) {
        gevr_delete_if_exists(ready_path);
    }
    fprintf(stderr, "[gevr_prepare] ship stamp mismatch (disk=%s expected=%s) - forcing re-prepare\n",
            on_disk[0] ? on_disk : "(none)", expected);
    return 1;
}
