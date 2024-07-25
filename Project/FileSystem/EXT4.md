# EXT4

## 高级数据结构设计

### Blocks

EXT4 以`块`为单位分配存储空间。块是一组扇区介于 1KiB 和 64KiB 之间，扇区数量必须为 2 的整数幂。块又被分组成更大的单元，称为`块组`。默认情况下，文件系统可以包含 2^32 个块，启用 64 bits feature，则文件系统可以有 2^64 个块。

### Layout

标准块组的布局：

| Group 0 Padding | ext4 Super Block | Group Descriptors | Reserved GDT Blocks | Data Block Bitmap | inode Bitmap | inode Table | Data Blocks      |
| --------------- | ---------------- | ----------------- | ------------------- | ----------------- | ------------ | ----------- | ---------------- |
| 1024 bytes      | 1 block          | many blocks       | many blocks         | 1 block           | 1 block      | many blocks | many more blocks |

对于块组 0 的特殊情况，前 1024 个字节未使用， 允许安装 x86 引导扇区。 超级块将从偏移量 1024 字节开始。如果块大小 = 1024，则块 0 标记为使用中，超级块就处于块 1。

### Flexible Block Groups

ext4 开始，flex_bg 中几个块组被捆绑在一起作为一个 逻辑块组，bitmap 空间和 inode Table 空间 flex_bg 的第一个块组被扩展为包括位图以及 flex_bg 中所有其他块组的 inode 表。

### Meta Block Groups

### Special inodes

ext4 为特殊功能预留了一些 inode，如下所示：

| inode 编号 | 目的                                           |
| ---------- | ---------------------------------------------- |
| 0          | 没有 inode 0。                                 |
| 1          | 有缺陷的块的列表。                             |
| 2          | **Root directory**                             |
| 3          | User quota                                     |
| 4          | Group quota                                    |
| 5          | Boot loader                                    |
| 6          | Undelete directory                             |
| 7          | Reserved group descriptors inode（调整 Inode） |
| 8          | Journal inode                                  |
| 9          | exclude inode，用于快照                        |
| 10         | Replica inode                                  |
| 11         | lost+found                                     |

### Checksums

### Inline Data

-  文件小于 60 字节，数据就会内嵌存储在 inode.i_block 中。
- 文件的其余部分可以容纳在扩展属性空间内，那么就可以在 inode 主体（"ibody EA"）中找到扩展属性 "system.data"。 当然，这也限制了一个 inode 可以附加的扩展属性数量。 
- 数据大小超过 i_block + ibody EA，就会分配一个常规块，并将内容移至该块。

#### Inline Directories

i_block 的前四个字节是父目录的 inode 编号。 之后是 56 字节的目录条目数组空间；参见 struct ext4_dir_entry。 如果 inode 主体中有 "system.data "属性，则 EA 值也是 struct ext4_dir_entry 数组。 请注意，对于内联目录，i_block 和 EA 空间被视为独立的 dirent 块；目录条目不能跨越这两个块。 内联目录条目不进行校验和，因为 inode 校验和应保护所有内联数据内容。

## 全局数据结构

### Super Block

| Offset | Size   | Name                       | Description                                                  |
| ------ | ------ | -------------------------- | ------------------------------------------------------------ |
| 0x0    | __le32 | **s_inodes_count**         | 节点总数                                                     |
| 0x4    | __le32 | **s_blocks_count_lo**      | 区块总数                                                     |
| 0x8    | __le32 | s_r_blocks_count_lo        | This number of blocks can only be allocated by the super-user. |
| 0xC    | __le32 | **s_free_blocks_count_lo** | 空闲块计数                                                   |
| 0x10   | __le32 | **s_free_inodes_count**    | 空闲 inode 数量                                              |
| 0x14   | __le32 | s_first_data_block         | 第一个数据块， 对于 1k 块的文件系统，该值必须至少为 1，对于所有其他块大小，该值通常为 0 |
| 0x18   | __le32 | **s_log_block_size**       | 块大小为 2 ^ (10 + s_log_block_size)。                       |
| 0x1C   | __le32 | s_log_cluster_size         | Cluster size is 2 ^ (10 + s_log_cluster_size) blocks if bigalloc is enabled. Otherwise s_log_cluster_size must equal s_log_block_size. |
| 0x20   | __le32 | **s_blocks_per_group**     | 每组块数                                                     |
| 0x24   | __le32 | s_clusters_per_group       | Clusters per group, if bigalloc is enabled. Otherwise s_clusters_per_group must equal s_blocks_per_group. |
| 0x28   | __le32 | **s_inodes_per_group**     | 每个组的 Inodes 数                                           |
| 0x2C   | __le32 | s_mtime                    | Mount time, in seconds since the epoch.                      |
| 0x30   | __le32 | s_wtime                    | Write time, in seconds since the epoch.                      |
| 0x34   | __le16 | s_mnt_count                | Number of mounts since the last fsck.                        |
| 0x36   | __le16 | s_max_mnt_count            | Number of mounts beyond which a fsck is needed.              |
| 0x38   | __le16 | **s_magic**                | 标识签名, 0xEF53                                             |
| 0x3A   | __le16 | s_state                    | File system state. See [super_state](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-state) for more info. |
| 0x3C   | __le16 | s_errors                   | Behaviour when detecting errors. See [super_errors](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-errors) for more info. |
| 0x3E   | __le16 | s_minor_rev_level          | Minor revision level.                                        |
| 0x40   | __le32 | s_lastcheck                | Time of last check, in seconds since the epoch.              |
| 0x44   | __le32 | s_checkinterval            | Maximum time between checks, in seconds.                     |
| 0x48   | __le32 | s_creator_os               | Creator OS. See the table [super_creator](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-creator) for more info. |
| 0x4C   | __le32 | s_rev_level                | Revision level. See the table [super_revision](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-revision) for more info. |
| 0x50   | __le16 | s_def_resuid               | Default uid for reserved blocks.                             |
| 0x52   | __le16 | s_def_resgid               | Default gid for reserved blocks.                             |
|        |        |                            | 这些字段仅适用于 EXT4_DYNAMIC_REV 超级块。                   |
| 0x54   | __le32 | s_first_ino                | First non-reserved inode.                                    |
| 0x58   | __le16 | s_inode_size               | inode 结构的大小（字节）                                     |
| 0x5A   | __le16 | s_block_group_nr           | Block group # of this superblock.                            |
| 0x5C   | __le32 | s_feature_compat           | Compatible feature set flags. Kernel can still read/write this fs even if it doesn’t understand a flag; fsck should not do that. See the [super_compat](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-compat) table for more info. |
| 0x60   | __le32 | s_feature_incompat         | Incompatible feature set. If the kernel or fsck doesn’t understand one of these bits, it should stop. See the [super_incompat](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-incompat) table for more info. |
| 0x64   | __le32 | s_feature_ro_compat        | Readonly-compatible feature set. If the kernel doesn’t understand one of these bits, it can still mount read-only. See the [super_rocompat](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-rocompat) table for more info. |
| 0x68   | __u8   | s_uuid[16]                 | 128-bit UUID for volume.                                     |
| 0x78   | char   | **s_volume_name**[16]      | 卷标                                                         |
| 0x88   | char   | s_last_mounted[64]         | Directory where filesystem was last mounted.                 |
| 0xC8   | __le32 | s_algorithm_usage_bitmap   | For compression (Not used in e2fsprogs/Linux)                |
|        |        |                            | Performance hints. Directory preallocation should only happen if the EXT4_FEATURE_COMPAT_DIR_PREALLOC flag is on. |
| 0xCC   | __u8   | s_prealloc_blocks          | #. of blocks to try to preallocate for … files? (Not used in e2fsprogs/Linux) |
| 0xCD   | __u8   | s_prealloc_dir_blocks      | #. of blocks to preallocate for directories. (Not used in e2fsprogs/Linux) |
| 0xCE   | __le16 | s_reserved_gdt_blocks      | Number of reserved GDT entries for future filesystem expansion. |
|        |        |                            | Journalling support is valid only if EXT4_FEATURE_COMPAT_HAS_JOURNAL is set. |
| 0xD0   | __u8   | s_journal_uuid[16]         | UUID of journal superblock                                   |
| 0xE0   | __le32 | s_journal_inum             | inode number of journal file.                                |
| 0xE4   | __le32 | s_journal_dev              | Device number of journal file, if the external journal feature flag is set. |
| 0xE8   | __le32 | s_last_orphan              | Start of list of orphaned inodes to delete.                  |
| 0xEC   | __le32 | s_hash_seed[4]             | HTREE hash seed.                                             |
| 0xFC   | __u8   | s_def_hash_version         | Default hash algorithm to use for directory hashes. See [super_def_hash](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-def-hash) for more info. |
| 0xFD   | __u8   | s_jnl_backup_type          | If this value is 0 or EXT3_JNL_BACKUP_BLOCKS (1), then the `s_jnl_blocks` field contains a duplicate copy of the inode’s `i_block[]` array and `i_size`. |
| 0xFE   | __le16 | s_desc_size                | Size of group descriptors, in bytes, if the 64bit incompat feature flag is set. |
| 0x100  | __le32 | s_default_mount_opts       | Default mount options. See the [super_mountopts](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-mountopts) table for more info. |
| 0x104  | __le32 | s_first_meta_bg            | First metablock block group, if the meta_bg feature is enabled. |
| 0x108  | __le32 | s_mkfs_time                | When the filesystem was created, in seconds since the epoch. |
| 0x10C  | __le32 | s_jnl_blocks[17]           | Backup copy of the journal inode’s `i_block[]` array in the first 15 elements and i_size_high and i_size in the 16th and 17th elements, respectively. |
|        |        |                            | 64bit support is valid only if EXT4_FEATURE_COMPAT_64BIT is set. |
| 0x150  | __le32 | s_blocks_count_hi          | High 32-bits of the block count.                             |
| 0x154  | __le32 | s_r_blocks_count_hi        | High 32-bits of the reserved block count.                    |
| 0x158  | __le32 | s_free_blocks_count_hi     | High 32-bits of the free block count.                        |
| 0x15C  | __le16 | s_min_extra_isize          | All inodes have at least # bytes.                            |
| 0x15E  | __le16 | s_want_extra_isize         | New inodes should reserve # bytes.                           |
| 0x160  | __le32 | s_flags                    | Miscellaneous flags. See the [super_flags](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-flags) table for more info. |
| 0x164  | __le16 | s_raid_stride              | RAID stride. This is the number of logical blocks read from or written to the disk before moving to the next disk. This affects the placement of filesystem metadata, which will hopefully make RAID storage faster. |
| 0x166  | __le16 | s_mmp_interval             | #. seconds to wait in multi-mount prevention (MMP) checking. In theory, MMP is a mechanism to record in the superblock which host and device have mounted the filesystem, in order to prevent multiple mounts. This feature does not seem to be implemented… |
| 0x168  | __le64 | s_mmp_block                | Block # for multi-mount protection data.                     |
| 0x170  | __le32 | s_raid_stripe_width        | RAID stripe width. This is the number of logical blocks read from or written to the disk before coming back to the current disk. This is used by the block allocator to try to reduce the number of read-modify-write operations in a RAID5/6. |
| 0x174  | __u8   | s_log_groups_per_flex      | Size of a flexible block group is 2 ^ `s_log_groups_per_flex`. |
| 0x175  | __u8   | s_checksum_type            | Metadata checksum algorithm type. The only valid value is 1 (crc32c). |
| 0x176  | __le16 | s_reserved_pad             |                                                              |
| 0x178  | __le64 | s_kbytes_written           | Number of KiB written to this filesystem over its lifetime.  |
| 0x180  | __le32 | s_snapshot_inum            | inode number of active snapshot. (Not used in e2fsprogs/Linux.) |
| 0x184  | __le32 | s_snapshot_id              | Sequential ID of active snapshot. (Not used in e2fsprogs/Linux.) |
| 0x188  | __le64 | s_snapshot_r_blocks_count  | Number of blocks reserved for active snapshot’s future use. (Not used in e2fsprogs/Linux.) |
| 0x190  | __le32 | s_snapshot_list            | inode number of the head of the on-disk snapshot list. (Not used in e2fsprogs/Linux.) |
| 0x194  | __le32 | s_error_count              | Number of errors seen.                                       |
| 0x198  | __le32 | s_first_error_time         | First time an error happened, in seconds since the epoch.    |
| 0x19C  | __le32 | s_first_error_ino          | inode involved in first error.                               |
| 0x1A0  | __le64 | s_first_error_block        | Number of block involved of first error.                     |
| 0x1A8  | __u8   | s_first_error_func[32]     | Name of function where the error happened.                   |
| 0x1C8  | __le32 | s_first_error_line         | Line number where error happened.                            |
| 0x1CC  | __le32 | s_last_error_time          | Time of most recent error, in seconds since the epoch.       |
| 0x1D0  | __le32 | s_last_error_ino           | inode involved in most recent error.                         |
| 0x1D4  | __le32 | s_last_error_line          | Line number where most recent error happened.                |
| 0x1D8  | __le64 | s_last_error_block         | Number of block involved in most recent error.               |
| 0x1E0  | __u8   | s_last_error_func[32]      | Name of function where the most recent error happened.       |
| 0x200  | __u8   | s_mount_opts[64]           | ASCIIZ string of mount options.                              |
| 0x240  | __le32 | s_usr_quota_inum           | Inode number of user [quota](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/quota) file. |
| 0x244  | __le32 | s_grp_quota_inum           | Inode number of group [quota](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/quota) file. |
| 0x248  | __le32 | s_overhead_blocks          | Overhead blocks/clusters in fs. (Huh? This field is always zero, which means that the kernel calculates it dynamically.) |
| 0x24C  | __le32 | s_backup_bgs[2]            | Block groups containing superblock backups (if sparse_super2) |
| 0x254  | __u8   | s_encrypt_algos[4]         | Encryption algorithms in use. There can be up to four algorithms in use at any time; valid algorithm codes are given in the [super_encrypt](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#super-encrypt) table below. |
| 0x258  | __u8   | s_encrypt_pw_salt[16]      | Salt for the string2key algorithm for encryption.            |
| 0x268  | __le32 | s_lpf_ino                  | Inode number of lost+found                                   |
| 0x26C  | __le32 | s_prj_quota_inum           | Inode that tracks project quotas.                            |
| 0x270  | __le32 | s_checksum_seed            | Checksum seed used for metadata_csum calculations. This value is crc32c(~0, $orig_fs_uuid). |
| 0x274  | __u8   | s_wtime_hi                 | Upper 8 bits of the s_wtime field.                           |
| 0x275  | __u8   | s_mtime_hi                 | Upper 8 bits of the s_mtime field.                           |
| 0x276  | __u8   | s_mkfs_time_hi             | Upper 8 bits of the s_mkfs_time field.                       |
| 0x277  | __u8   | s_lastcheck_hi             | Upper 8 bits of the s_lastcheck_hi field.                    |
| 0x278  | __u8   | s_first_error_time_hi      | Upper 8 bits of the s_first_error_time_hi field.             |
| 0x279  | __u8   | s_last_error_time_hi       | Upper 8 bits of the s_last_error_time_hi field.              |
| 0x27A  | __u8   | s_pad[2]                   | Zero padding.                                                |
| 0x27C  | __le16 | s_encoding                 | Filename charset encoding.                                   |
| 0x27E  | __le16 | s_encoding_flags           | Filename charset encoding flags.                             |
| 0x280  | __le32 | s_reserved[95]             | Padding to the end of the block.                             |
| 0x3FC  | __le32 | s_checksum                 | Superblock checksum.                                         |

### Block Group Descriptors

| Offset | Size   | Name                    | Description                                                  |
| ------ | ------ | ----------------------- | ------------------------------------------------------------ |
| 0x0    | __le32 | bg_block_bitmap_lo      | Lower 32-bits of location of block bitmap.                   |
| 0x4    | __le32 | bg_inode_bitmap_lo      | Lower 32-bits of location of inode bitmap.                   |
| 0x8    | __le32 | bg_inode_table_lo       | Lower 32-bits of location of inode table.                    |
| 0xC    | __le16 | bg_free_blocks_count_lo | Lower 16-bits of free block count.                           |
| 0xE    | __le16 | bg_free_inodes_count_lo | Lower 16-bits of free inode count.                           |
| 0x10   | __le16 | bg_used_dirs_count_lo   | Lower 16-bits of directory count.                            |
| 0x12   | __le16 | bg_flags                | Block group flags. See the [bgflags](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/globals.html#bgflags) table below. |
| 0x14   | __le32 | bg_exclude_bitmap_lo    | Lower 32-bits of location of snapshot exclusion bitmap.      |
| 0x18   | __le16 | bg_block_bitmap_csum_lo | Lower 16-bits of the block bitmap checksum.                  |
| 0x1A   | __le16 | bg_inode_bitmap_csum_lo | Lower 16-bits of the inode bitmap checksum.                  |
| 0x1C   | __le16 | bg_itable_unused_lo     | Lower 16-bits of unused inode count. If set, we needn’t scan past the `(sb.s_inodes_per_group - gdt.bg_itable_unused)`th entry in the inode table for this group. |
| 0x1E   | __le16 | bg_checksum             | Group descriptor checksum; crc16(sb_uuid+group_num+bg_desc) if the RO_COMPAT_GDT_CSUM feature is set, or crc32c(sb_uuid+group_num+bg_desc) & 0xFFFF if the RO_COMPAT_METADATA_CSUM feature is set. The bg_checksum field in bg_desc is skipped when calculating crc16 checksum, and set to zero if crc32c checksum is used. |
|        |        |                         | These fields only exist if the 64bit feature is enabled and s_desc_size > 32. |
| 0x20   | __le32 | bg_block_bitmap_hi      | Upper 32-bits of location of block bitmap.                   |
| 0x24   | __le32 | bg_inode_bitmap_hi      | Upper 32-bits of location of inodes bitmap.                  |
| 0x28   | __le32 | bg_inode_table_hi       | Upper 32-bits of location of inodes table.                   |
| 0x2C   | __le16 | bg_free_blocks_count_hi | Upper 16-bits of free block count.                           |
| 0x2E   | __le16 | bg_free_inodes_count_hi | Upper 16-bits of free inode count.                           |
| 0x30   | __le16 | bg_used_dirs_count_hi   | Upper 16-bits of directory count.                            |
| 0x32   | __le16 | bg_itable_unused_hi     | Upper 16-bits of unused inode count.                         |
| 0x34   | __le32 | bg_exclude_bitmap_hi    | Upper 32-bits of location of snapshot exclusion bitmap.      |
| 0x38   | __le16 | bg_block_bitmap_csum_hi | Upper 16-bits of the block bitmap checksum.                  |
| 0x3A   | __le16 | bg_inode_bitmap_csum_hi | Upper 16-bits of the inode bitmap checksum.                  |
| 0x3C   | __u32  | bg_reserved             | Padding to 64 bytes.                                         |

## 动态元数据结构

### Index Nodes

inode 表是 struct ext4_inode 的线性数组。 该表的大小应足以存储至少下列的字节的区块：
$$
sb.s\_inode\_size * sb.s\_inodes\_per\_group
$$
包含一个 inode 的块组的编号可计算为
$$
（inode\_number - 1）/sb.s\_inodes\_per\_group
$$
而该组表的偏移量
$$
（inode\_number - 1）\%sb.s\_inodes\_per\_group
$$
没有 inode 0。 inode 校验和是根据 FS UUID、inode 编号和 inode 结构本身计算的。

#### inode

| Offset | Size     | Name                          | Description                                                  |
| ------ | -------- | ----------------------------- | ------------------------------------------------------------ |
| 0x0    | __le16   | **i_mode**                    | 文件模式。 参见下表 i_mode                                   |
| 0x2    | __le16   | i_uid                         | Lower 16-bits of Owner UID.                                  |
| 0x4    | __le32   | **i_size_lo**                 | 以字节为单位的文件大小的低 32 位                             |
| 0x8    | __le32   | **i_atime**                   | 上次访问时间，以自纪元起的秒为单位                           |
| 0xC    | __le32   | **i_ctime**                   | 最后一次节点更改时间                                         |
| 0x10   | __le32   | **i_mtime**                   | 最后数据修改时间                                             |
| 0x14   | __le32   | **i_dtime**                   | 删除时间                                                     |
| 0x18   | __le16   | i_gid                         | Lower 16-bits of GID.                                        |
| 0x1A   | __le16   | i_links_count                 | Hard link count                                              |
| 0x1C   | __le32   | **i_blocks_lo**               | 块 "计数的低 32 位                                           |
| 0x20   | __le32   | **i_flags**                   | Inode 标志。 参见下面的表 i_flags。                          |
| 0x24   | 4 bytes  | i_osd1                        | See the table [i_osd1](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/dynamic.html#i-osd1) for more details. |
| 0x28   | 60 bytes | **i_block[EXT4_N_BLOCKS=15]** | 块映射图或范围树。 参见 "inode.i_block 的内容 "部分          |
| 0x64   | __le32   | i_generation                  | File version (for NFS).                                      |
| 0x68   | __le32   | i_file_acl_lo                 | Lower 32-bits of extended attribute block. ACLs are of course one of many possible extended attributes; I think the name of this field is a result of the first use of extended attributes being for ACLs. |
| 0x6C   | __le32   | **i_size_high / i_dir_acl**   | 文件/目录大小的高 32 位                                      |
| 0x70   | __le32   | i_obso_faddr                  | (Obsolete) fragment address.                                 |
| 0x74   | 12 bytes | i_osd2                        | See the table [i_osd2](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/dynamic.html#i-osd2) for more details. |
| 0x80   | __le16   | i_extra_isize                 | Size of this inode - 128. Alternately, the size of the extended inode fields beyond the original ext2 inode, including this field. |
| 0x82   | __le16   | i_checksum_hi                 | Upper 16-bits of the inode checksum.                         |
| 0x84   | __le32   | i_ctime_extra                 | Extra change time bits. This provides sub-second precision. See Inode Timestamps section. |
| 0x88   | __le32   | i_mtime_extra                 | Extra modification time bits. This provides sub-second precision. |
| 0x8C   | __le32   | i_atime_extra                 | Extra access time bits. This provides sub-second precision.  |
| 0x90   | __le32   | **i_crtime**                  | 文件创建时间，以自纪元起的秒为单位                           |
| 0x94   | __le32   | i_crtime_extra                | Extra file creation time bits. This provides sub-second precision. |
| 0x98   | __le32   | i_version_hi                  | Upper 32-bits for version number.                            |
| 0x9C   | __le32   | i_projid                      | Project ID.                                                  |

#### i_mode

| Value  | Description                              |
| ------ | ---------------------------------------- |
| 0x1    | S_IXOTH (Others may execute)             |
| 0x2    | S_IWOTH (Others may write)               |
| 0x4    | S_IROTH (Others may read)                |
| 0x8    | S_IXGRP (Group members may execute)      |
| 0x10   | S_IWGRP (Group members may write)        |
| 0x20   | S_IRGRP (Group members may read)         |
| 0x40   | S_IXUSR (Owner may execute)              |
| 0x80   | S_IWUSR (Owner may write)                |
| 0x100  | S_IRUSR (Owner may read)                 |
| 0x200  | S_ISVTX (Sticky bit)                     |
| 0x400  | S_ISGID (Set GID)                        |
| 0x800  | S_ISUID (Set UID)                        |
|        | These are mutually-exclusive file types: |
| 0x1000 | S_IFIFO (FIFO)                           |
| 0x2000 | S_IFCHR (Character device)               |
| 0x4000 | S_IFDIR (Directory)                      |
| 0x6000 | S_IFBLK (Block device)                   |
| 0x8000 | S_IFREG (Regular file)                   |
| 0xA000 | S_IFLNK (Symbolic link)                  |
| 0xC000 | S_IFSOCK (Socket)                        |

#### i_flags

| Value      | Description                                                  |
| ---------- | ------------------------------------------------------------ |
| 0x1        | This file requires secure deletion (EXT4_SECRM_FL). (not implemented) |
| 0x2        | This file should be preserved, should undeletion be desired (EXT4_UNRM_FL). (not implemented) |
| 0x4        | File is compressed (EXT4_COMPR_FL). (not really implemented) |
| 0x8        | All writes to the file must be synchronous (EXT4_SYNC_FL).   |
| 0x10       | File is immutable (EXT4_IMMUTABLE_FL).                       |
| 0x20       | File can only be appended (EXT4_APPEND_FL).                  |
| 0x40       | The dump(1) utility should not dump this file (EXT4_NODUMP_FL). |
| 0x80       | Do not update access time (EXT4_NOATIME_FL).                 |
| 0x100      | Dirty compressed file (EXT4_DIRTY_FL). (not used)            |
| 0x200      | File has one or more compressed clusters (EXT4_COMPRBLK_FL). (not used) |
| 0x400      | Do not compress file (EXT4_NOCOMPR_FL). (not used)           |
| 0x800      | Encrypted inode (EXT4_ENCRYPT_FL). This bit value previously was EXT4_ECOMPR_FL (compression error), which was never used. |
| 0x1000     | Directory has hashed indexes (EXT4_INDEX_FL).                |
| 0x2000     | AFS magic directory (EXT4_IMAGIC_FL).                        |
| 0x4000     | File data must always be written through the journal (EXT4_JOURNAL_DATA_FL). |
| 0x8000     | File tail should not be merged (EXT4_NOTAIL_FL). (not used by ext4) |
| 0x10000    | All directory entry data should be written synchronously (see `dirsync`) (EXT4_DIRSYNC_FL). |
| 0x20000    | Top of directory hierarchy (EXT4_TOPDIR_FL).                 |
| 0x40000    | This is a huge file (EXT4_HUGE_FILE_FL).                     |
| 0x80000    | Inode uses extents (EXT4_EXTENTS_FL).                        |
| 0x100000   | Verity protected file (EXT4_VERITY_FL).                      |
| 0x200000   | Inode stores a large extended attribute value in its data blocks (EXT4_EA_INODE_FL). |
| 0x400000   | This file has blocks allocated past EOF (EXT4_EOFBLOCKS_FL). (deprecated) |
| 0x01000000 | Inode is a snapshot (`EXT4_SNAPFILE_FL`). (not in mainline)  |
| 0x04000000 | Snapshot is being deleted (`EXT4_SNAPFILE_DELETED_FL`). (not in mainline) |
| 0x08000000 | Snapshot shrink has completed (`EXT4_SNAPFILE_SHRUNK_FL`). (not in mainline) |
| 0x10000000 | Inode has inline data (EXT4_INLINE_DATA_FL).                 |
| 0x20000000 | Create children with the same project ID (EXT4_PROJINHERIT_FL). |
| 0x80000000 | Reserved for ext4 library (EXT4_RESERVED_FL).                |
|            | Aggregate flags:                                             |
| 0x705BDFFF | User-visible flags.                                          |
| 0x604BC0FF | User-modifiable flags. Note that while EXT4_JOURNAL_DATA_FL and EXT4_EXTENTS_FL can be set with setattr, they are not in the kernel’s EXT4_FL_USER_MODIFIABLE mask, since it needs to handle the setting of these flags in a special manner and they are masked out of the set of flags that are saved directly to i_flags. |

#### Inode Size

在 ext2 和 ext3 中，inode 结构大小固定为 128 字节（EXT2_GOOD_OLD_INODE_SIZE），每个 inode 的磁盘记录大小为 128 字节。 从 ext4 开始，可以在格式化时为文件系统中的所有 inode 分配更大的磁盘 inode，以提供超出原始 ext2 inode 末尾的空间。 磁盘上的 inode 记录大小在超级块中记录为 s_inode_size。 结构 ext4_inode 实际使用的超出最初 128 字节 ext2 inode 的字节数记录在每个 inode 的 i_extra_isize 字段中，这使得结构 ext4_inode 可以在新内核中增长，而无需升级所有磁盘上的 inode。 访问 EXT2_GOOD_OLD_INODE_SIZE 以外的字段时，应验证是否在 i_extra_isize 范围内。 默认情况下，ext4 inode 记录为 256 字节。

#### Finding an Inode

每个块组包含 `sb->s_inodes_per_group` 个节点。 由于 `inode 0` 被定义为不存在，因此可以使用以下公式查找 inode 所在的块组：
$$
bg = (inode\_num - 1) / sb->s\_inodes\_per\_group
$$
在块组的 inode 表中找到特定的 inode：
$$
index = (inode\_num - 1) \% sb->s\_inodes\_per\_group
$$
要获取 inode 表中的字节地址：
$$
offset = index * sb->s\_inode\_size
$$

### The Contents of inode.i_block

#### Symbolic Links

如果目标字符串长度小于 60 字节，符号链接的目标将存储在该字段中。 否则，将使用扩展或块映射分配数据块来存储链接目标。

#### [Direct/Indirect Block Addressing](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/dynamic.html#direct-indirect-block-addressing)

在 ext2/3 中，文件块编号通过（最多）三级 1-1 块映射映射到逻辑块编号。 

#### [Extent Tree](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/dynamic.html#extent-tree)

在 ext4 中，文件到逻辑块的映射已被扩展树所取代。

#### Inline Data

如果文件系统启用了内联数据功能，并且为 inode 设置了标志，那么文件数据的前 60 个字节就有可能存储在这里。

### Directory Entries

#### [Linear (Classic) Directories](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/dynamic.html#linear-classic-directories)

#### [Hash Tree Directories](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/dynamic.html#hash-tree-directories)

## 参考资料

[ext4 Data Structures and Algorithms — The Linux Kernel documentation](https://www.kernel.org/doc/html/v5.4/filesystems/ext4/index.html)

[Ext4 (kernel.org)](https://ext4.wiki.kernel.org/index.php/Main_Page)