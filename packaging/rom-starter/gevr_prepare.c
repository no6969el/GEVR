/*
 * gevr_prepare - CLI ROM slice into %LOCALAPPDATA%\GEVR\cache\<sha256>\
 *
 * Reference source for GoldenEyeVR (not built in the public GEVR docs repo).
 * Wire gevr_extract_combined_from_rom() at the marked call site in the product tree.
 *
 * Ship stamp: GEVR_SHIP_TAG (env, set by gevr-vrNNN-boot.cmd) must match ship.txt
 * beside ready. Mismatch removes ready + combined.bin so we never print
 * "READY already prepared" on a stale cache after a public zip update.
 */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gevr_cache_ship.h"

static int gevr_cache_dir_for_rom(const char *rom_sha256, char *out, size_t out_cap)
{
    const char *base;
    size_t n;

    if (!rom_sha256 || !out || out_cap < 32) {
        return -1;
    }
    base = getenv("GEVR_CACHE_DIR");
    if (base && base[0]) {
        n = snprintf(out, out_cap, "%s", base);
    } else {
        const char *local = getenv("LOCALAPPDATA");
        if (!local || !local[0]) {
            return -1;
        }
        n = snprintf(out, out_cap, "%s\\GEVR\\cache\\%s", local, rom_sha256);
    }
    return (n > 0 && (size_t)n < out_cap) ? 0 : -1;
}

/*
 * Product tree: replace this stub with the real extractor that writes combined.bin.
 * Must return 0 on success.
 */
static int gevr_extract_combined_from_rom(const char *rom_path, const char *cache_dir)
{
    (void)rom_path;
    (void)cache_dir;
    fprintf(stderr, "[gevr_prepare] gevr_extract_combined_from_rom not linked (reference build)\n");
    return 1;
}

static int gevr_write_ready_marker(const char *cache_dir)
{
    char path[MAX_PATH];
    FILE *f;

    if (snprintf(path, sizeof(path), "%s\\%s", cache_dir, GEVR_CACHE_READY_FILE) >= (int)sizeof(path)) {
        return -1;
    }
    f = fopen(path, "wb");
    if (!f) {
        return -1;
    }
    fclose(f);
    return 0;
}

static int gevr_do_prepare(const char *rom_path, const char *cache_dir)
{
    const char *tag = gevr_ship_tag_expected();

    if (gevr_extract_combined_from_rom(rom_path, cache_dir) != 0) {
        return 1;
    }
    if (gevr_write_ready_marker(cache_dir) != 0) {
        return 1;
    }
    if (gevr_ship_stamp_write(cache_dir, tag) != 0) {
        return 1;
    }
    fprintf(stderr, "[gevr_prepare] prepared cache tag=%s\n", tag);
    return 0;
}

int main(int argc, char **argv)
{
    const char *rom_path;
    const char *rom_sha;
    char cache_dir[MAX_PATH];

    if (argc < 2) {
        fprintf(stderr, "usage: gevr_prepare <rom.z64> [rom_sha256]\n");
        return 2;
    }
    rom_path = argv[1];
    rom_sha = (argc >= 3) ? argv[2] : getenv("GEVR_ROM_SHA256");
    if (!rom_sha || !rom_sha[0]) {
        fprintf(stderr, "[gevr_prepare] need ROM sha256 (arg or GEVR_ROM_SHA256)\n");
        return 2;
    }

    if (gevr_cache_dir_for_rom(rom_sha, cache_dir, sizeof(cache_dir)) != 0) {
        fprintf(stderr, "[gevr_prepare] could not build cache dir\n");
        return 1;
    }

    (void)gevr_ship_stamp_invalidate_if_mismatch(cache_dir);

    if (gevr_cache_ready_exists(cache_dir)) {
        fprintf(stderr, "[gevr_prepare] READY already prepared (ship=%s)\n", gevr_ship_tag_expected());
        return 0;
    }

    return gevr_do_prepare(rom_path, cache_dir) == 0 ? 0 : 1;
}
