## Git

### 配置

#### 用户信息

```shell
git config --global user.name "John Doe"
git config --global user.email johndoe@example.com
```

#### 查看配置

```shell
git config --list
```

### 基础

#### 新建仓库、克隆仓库、跟踪文件

#### 忽略文件

.gitignore文件

#### 查看仓库状态

```shell
git status 
```

#### 提交更新

```shell
git commit
```

#### 查看提交历史

```shell
git log --oneline --graph
```

#### 修补最后一次提交

```shell
git commit --amend
```

#### 版本回退

```shell
git reset --hard HEAD^
```

#### 撤销修改

```shell
git reset HEAD <file>
```

### 分支

#### 新建分支并切换

```shell
git checkout -b iss53
```

#### 跟踪远程分支

```shell
git checkout -b [分支名] [远程名]/[分支名]
```

### 衍合

#### 拉取代码

```shell
git pull --rebase
```

#### 交互衍合

```shell
git rebase -i 4cb600e
```

### 参考资料

[Git教程 - 廖雪峰的官方网站 ](https://www.liaoxuefeng.com/wiki/896043488029600)

《Pro Git》