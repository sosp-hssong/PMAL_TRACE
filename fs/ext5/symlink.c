/*
 *  linux/fs/ext5/symlink.c
 *
 * Only fast symlinks left here - the rest is done by generic code. AV, 1999
 *
 * Copyright (C) 1992, 1993, 1994, 1995
 * Remy Card (card@masi.ibp.fr)
 * Laboratoire MASI - Institut Blaise Pascal
 * Universite Pierre et Marie Curie (Paris VI)
 *
 *  from
 *
 *  linux/fs/minix/symlink.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *
 *  ext5 symlink handling code
 */

#include <linux/fs.h>
#include <linux/jbd2.h>
#include <linux/namei.h>
#include "ext5.h"
#include "xattr.h"

static void *ext5_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct ext5_inode_info *ei = EXT5_I(dentry->d_inode);
	nd_set_link(nd, (char *) ei->i_data);
	return NULL;
}

const struct inode_operations ext5_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.follow_link	= page_follow_link_light,
	.put_link	= page_put_link,
	.setattr	= ext5_setattr,
	.setxattr	= generic_setxattr,
	.getxattr	= generic_getxattr,
	.listxattr	= ext5_listxattr,
	.removexattr	= generic_removexattr,
};

const struct inode_operations ext5_fast_symlink_inode_operations = {
	.readlink	= generic_readlink,
	.follow_link	= ext5_follow_link,
	.setattr	= ext5_setattr,
	.setxattr	= generic_setxattr,
	.getxattr	= generic_getxattr,
	.listxattr	= ext5_listxattr,
	.removexattr	= generic_removexattr,
};
