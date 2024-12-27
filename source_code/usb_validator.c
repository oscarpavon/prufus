#include <string.h>
#include "prufus.h"

#include "scripts_names.h"

#define ARENA_MAX_SIZE 1024
#define READ_SIZE 64

typedef struct {
    size_t offset;
    char buffer[ARENA_MAX_SIZE];
} arena_t;

static char *arena_tail(arena_t *arena);
static void arena_save(arena_t *arena, size_t size);

static void next_token(char **disk_info);
static void terminate_token(char **disk_info);
static void parse_disk(char **disk_info, size_t disk);

// global storage for disks
Disk disks[MAX_DISKS];

size_t get_usb_disks(void) {
    static arena_t arena = {0}; // device info stored here
    FILE *script = popen(get_usb_disks_script, "r");
    size_t disk_count = 0;
    
    // read all
    while (!feof(script)) {
	char *chunk = arena_tail(&arena);
	size_t bytes = fread(chunk, 1, READ_SIZE, script);
	
	arena_save(&arena, bytes); 
	*arena_tail(&arena) = 0;
	
	if (strpbrk(chunk, "\n")) { 
	    ++disk_count;
	}
    }
    *arena_tail(&arena) = 0;

    pclose(script);
    printf("Disk count: %zu\n", disk_count);

    char *disk_info = arena.buffer;
    for (size_t disk = 0; disk < disk_count; ++disk)
    {
	parse_disk(&disk_info, disk);
    }

    for (size_t i = 0; i < disk_count; ++i)
    {	
	printf("%s %s %s\n", disks[i].device, disks[i].name, disks[i].size);
    }

    return disk_count;
}

static void parse_disk(char **disk_info, size_t disk)
{
    next_token(disk_info); // parse device
    disks[disk].device = *disk_info;
    terminate_token(disk_info);
    
    next_token(disk_info); // parse disk label
    disks[disk].name = *disk_info;
    terminate_token(disk_info);
    
    next_token(disk_info); // parse size	
    disks[disk].size = *disk_info;
    terminate_token(disk_info);
}

static size_t arena_mark(arena_t *arena) {
    return arena->offset;
}

static void arena_reset(arena_t *arena, size_t mark) {
    arena->offset = mark;
}

static void arena_save(arena_t *arena, size_t size) {
    arena->offset += size;
}

static char *arena_tail(arena_t *arena) {
    return &arena->buffer[arena->offset];
}

static void next_token(char **disk_info)
{
    *disk_info = strpbrk(*disk_info, "\"") + 1;
}

static void terminate_token(char **disk_info)
{
    *disk_info = strpbrk(*disk_info, "\"");
    **disk_info = 0; // null terminate
    ++(*disk_info);
}
