/* GEVR cache ship stamp - shared between gevr_prepare and GevrRomStarter.
 * Copy into GoldenEyeVR: packaging/rom-starter/ (product tree).
 *
 * Each public Beta tag (vr438, vr439, ...) sets GEVR_SHIP_TAG in gevr-*-boot.cmd.
 * On prepare, if %LOCALAPPDATA%\GEVR\cache\<rom-sha>\ship.txt != this tag,
 * drop the ready marker and force a full re-slice from the player's ROM.
 */
#ifndef GEVR_CACHE_SHIP_H
#define GEVR_CACHE_SHIP_H

#include <stddef.h>

#ifndef GEVR_SHIP_TAG_DEFAULT
#define GEVR_SHIP_TAG_DEFAULT "vr438"
#endif

#define GEVR_CACHE_SHIP_FILE "ship.txt"
#define GEVR_CACHE_READY_FILE "ready"

/* Trimmed tag from getenv("GEVR_SHIP_TAG") or GEVR_SHIP_TAG_DEFAULT. */
const char *gevr_ship_tag_expected(void);

/* Read ship.txt into out (NUL-terminated). Returns 0 on success. */
int gevr_ship_stamp_read(const char *cache_dir, char *out, size_t out_cap);

/* Write ship.txt (tag + newline). Returns 0 on success. */
int gevr_ship_stamp_write(const char *cache_dir, const char *tag);

/*
 * If ready exists but ship.txt is missing or != expected tag, remove ready and
 * combined.bin under cache_dir so prepare cannot short-circuit.
 * Returns 1 if cache was invalidated, 0 if left unchanged, -1 on error.
 */
int gevr_ship_stamp_invalidate_if_mismatch(const char *cache_dir);

/* Returns 1 if ready marker exists in cache_dir. */
int gevr_cache_ready_exists(const char *cache_dir);

#endif
