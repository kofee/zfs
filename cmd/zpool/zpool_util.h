/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */
/*
 * Copyright (c) 2005, 2010, Oracle and/or its affiliates. All rights reserved.
 */

#ifndef	ZPOOL_UTIL_H
#define	ZPOOL_UTIL_H

#include <libnvpair.h>
#include <libzfs.h>

#ifdef	__cplusplus
extern "C" {
#endif

/*
 * Basic utility functions
 */
void *safe_malloc(size_t);
void zpool_no_memory(void);
uint_t num_logs(nvlist_t *nv);
uint64_t array64_max(uint64_t array[], unsigned int len);
int isnumber(char *str);

/*
 * Virtual device functions
 */

nvlist_t *make_root_vdev(zpool_handle_t *zhp, nvlist_t *props, int force,
    int check_rep, boolean_t replacing, boolean_t dryrun, int argc,
    char **argv);
nvlist_t *split_mirror_vdev(zpool_handle_t *zhp, char *newname,
    nvlist_t *props, splitflags_t flags, int argc, char **argv);

/*
 * Pool list functions
 */
int for_each_pool(int, char **, boolean_t unavail, zprop_list_t **,
    zpool_iter_f, void *);

/* Vdev list functions */
typedef int (*pool_vdev_iter_f)(zpool_handle_t *, nvlist_t *, void *);
int for_each_vdev(zpool_handle_t *zhp, pool_vdev_iter_f func, void *data);

typedef struct zpool_list zpool_list_t;

zpool_list_t *pool_list_get(int, char **, zprop_list_t **, int *);
void pool_list_update(zpool_list_t *);
int pool_list_iter(zpool_list_t *, int unavail, zpool_iter_f, void *);
void pool_list_free(zpool_list_t *);
int pool_list_count(zpool_list_t *);
void pool_list_remove(zpool_list_t *, zpool_handle_t *);

libzfs_handle_t *g_zfs;


typedef	struct vdev_cmd_data
{
	char *line;	/* cmd output */
	char *path;	/* vdev path */
	char *upath;	/* vdev underlying path */
	char *pool;	/* Pool name */
	char *cmd;	/* backpointer to cmd */
} vdev_cmd_data_t;

typedef struct vdev_cmd_data_list
{
	char *cmd;		/* Command to run */
	unsigned int count;	/* Number of vdev_cmd_data items (vdevs) */

	/* vars to whitelist only certain vdevs, if requested */
	libzfs_handle_t *g_zfs;
	char **vdev_names;
	int vdev_names_count;
	int cb_name_flags;

	vdev_cmd_data_t *data;	/* Array of vdevs */

} vdev_cmd_data_list_t;

vdev_cmd_data_list_t *all_pools_for_each_vdev_run(int argc, char **argv,
    char *cmd, libzfs_handle_t *g_zfs, char **vdev_names, int vdev_names_count,
    int cb_name_flags);

void free_vdev_cmd_data_list(vdev_cmd_data_list_t *vcdl);

#ifdef	__cplusplus
}
#endif

#endif	/* ZPOOL_UTIL_H */
