#include "issue.h"
#include "file_helper.h"
#include "sb.h"
#include "da.h"

#include <assert.h> 
#include <stdbool.h> 
#include <stdint.h> 
#include <stdio.h>
#include <string.h>

#define ISSUES_BASE_PATH ".issues"

#define RED_COLOR 

static int gen_uid(void) 
{
    // TODO: If this issue tracker is used as a service for multiple users, a machine ID and 
    // millisecond precision should be added. For now, we use only the epocho time.
    return get_current_epoch_time();
}

void create_issue_dir(char *issue_path) 
{
    int ret = 0;
    if ((ret = create_dir(issue_path)) != DIR_OK) {
        fprintf(stderr, "ERR: Cant create [%s] dir. (%d)\n", issue_path, ret);
    }
}

void create_issue_md_file(const char *issue_name, const char *issue_path) 
{
    string_builder *issue = sb_create();
    sb_append(issue, "%s/issue.md", issue_path);

    FILE *f = fopen(issue->str, "w");

    date d = get_current_utc_time();
    fprintf(f, "DATE: %02d.%02d.%d\n", d.day, d.mon, d.year);
    fprintf(f, "NAME: %s\n", issue_name);
    fprintf(f, "PRIORITY: 1\n");
    fprintf(f, "RELATED FILES: none\n\n");  
    fprintf(f, "-----------------------------------------\n");
    fprintf(f, "CONTENT: (...)\n");

    fclose(f);
    sb_free(issue);
}

int issue_init(int argc, char** argv) 
{
    (void)argc;
    (void)argv;

    if (is_dir_exist(".issues") == DIR_OK) {
        fprintf(stderr, "ERR: Can't finde .issues base\nCreate one or use:\n\tissues init\n");
        return 1;
    }

    return create_dir("./"ISSUES_BASE_PATH);
}

void issue_append(char *issue_name) 
{
    const uint64_t uid  = gen_uid();
    string_builder *issue_dir = sb_create();
    sb_append(issue_dir, "./%s/ISSUE_%llu_%s", ISSUES_BASE_PATH, uid, issue_name);

    create_issue_dir(issue_dir->str);
    create_issue_md_file(issue_name, issue_dir->str);

    string_builder *issue_open_path = sb_create();
    sb_append(issue_open_path, "%s/issue.md", issue_dir->str);

    open_editor(issue_open_path->str);

    sb_free(issue_dir);
    sb_free(issue_open_path);
}

static void fill_issue(const char* issue_path, issue_view_record *view) 
{
    char tmp[1024] = {0};
    sprintf(tmp, ".issues/%s/issue.md", issue_path);

    FILE *f = fopen(tmp, "r");
    if (!f) {
        fprintf(stderr, "ERR: cant open issue (%s)", tmp);
        exit(1);
    }
    
    char line[1024] = {0};
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "DATE:") != NULL) {
            strncpy(view->date, line + strlen("DATE:"), ISSUE_VIEWER_BUFFER_SIZE);
            trim(view->date);
        }
        else if (strstr(line, "NAME:") != NULL) {
            strncpy(view->name, line + strlen("NAME:"), ISSUE_VIEWER_BUFFER_SIZE);
            trim(view->name);
        }
        else if (strstr(line, "PRIORITY:") != NULL) {
            strncpy(view->prio, line + strlen("PRIORITY:"), ISSUE_VIEWER_BUFFER_SIZE);
            trim(view->prio);
        }
        else if (strstr(line, "CONTENT:") != NULL) {
            strncpy(view->short_breaf, line + strlen("CONTENT:"), ISSUE_VIEWER_BUFFER_SIZE);
            trim(view->short_breaf);
        }
    }

    fclose(f);
}

void issue_viewer(void) 
{
    dir_content output_scan = {0};
    int ret = scan_path(ISSUES_BASE_PATH, &output_scan);
    if (ret != 0) {
        return;
    }


    issue_container issue_container = {0};
    for (size_t i = 0; i < output_scan.count; ++i) {
        issue_view_record issue = {0};
        fill_issue(output_scan.items[i], &issue);
        da_append(&issue_container, issue);
    }

    for (size_t i = 0; i < output_scan.count; ++i) {
        printf("[%zu] %s (%s%s%s) %s\t: %s ...\n", (i + 1), 
                issue_container.items[i].date,
                COLOR_RED, issue_container.items[i].prio,COLOR_RESET,
                output_scan.items[i],
                issue_container.items[i].short_breaf);
    }
}
