#include <vector>

// 定义其他必要的结构体和常量
const int SUCCESS = 0;
const int ANALYZE_SP_ERR = -1;
const int ANALYZE_GD_ERR = -2;

uint8_t sp_buffer[4096];
std::vector<struct group_desc> gd_vec;

struct superblock
{
  char fs_type[4];     // 例如: "50EF"
  uint32_t block_size; // 例如: 1024, 2048, 4096
  uint32_t group_desc_addr;
  uint32_t group_desc_size;
  uint32_t inode_nums;
  uint32_t cr_time;
};

struct group_desc
{
  uint32_t inode_table_addr;
  // 其他字段...
};

struct inode
{
  uint32_t inode_index; // 索引 2 表示根目录 "/"
  uint32_t cr_time;
  uint32_t size;
  uint32_t directory_addr;
  uint32_t tree[4]; // 块数量
}

struct directory
{
  char file_name[128];
  uint32_t inode_index; // 索引 2 表示根目录 "/"
}

int
analyze_superblock(diskhandle &disk)
{
  int ret = read(disk, 4096, sp_buffer, 4096);
  if (ret == SUCCESS)
  {
    // 解析超级块
    struct superblock *sb = (struct superblock *)sp_buffer;
    // 进一步处理 sb...
  }
  else
  {
    return ANALYZE_SP_ERR;
  }
}

int analyze_group_desc(diskhandle &disk)
{
  struct superblock *sp_point = (struct superblock *)sp_buffer;
  uint32_t gd_nums = sp_point->group_desc_size / sizeof(struct group_desc);
  uint8_t gd_buffer[4096];
  for (int i = 0; i < gd_nums; ++i)
  {
    int ret = read(disk, sp_point->group_desc_addr + i * sizeof(struct group_desc), gd_buffer, 4096);
    if (ret == SUCCESS)
    {
      // 解析组描述符
      struct group_desc *gd = (struct group_desc *)gd_buffer;
      // 检查 gd...
      gd_vec.push_back(*gd); // 注意这里使用了拷贝构造函数
    }
    else
    {
      return ANALYZE_GD_ERR;
    }
  }
}