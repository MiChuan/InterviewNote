# Github无法访问解决

## 问题原因

- 访问慢：服务器或 CDN 节点的地理位置相对较远，难以物理超度。注意这里的表现是延迟高，不一定是每秒传输速度慢。
- 无法加载：可能由于长时间的未响应，即访问慢的情况，导致浏览器判定无法加载内容；可能由于网址对应内容不能被直接访问，即无可访问内容或无权限访问。
- 无法通讯：这类情况往往是 IP 解析错误，即遭受 DNS 污染；否则就是 IP 服务器出现了内部错误。

## 测试

### 使用批量ping工具测试

在站长之家ping之后发现有的服务器能ping通，说明是遭受DNS污染，而IP是可以访问的。

[Ping Github.com服务器](https://ping.chinaz.com/github.com)

## 解决

### 修改hosts

#### Windows

1. 在开始菜单徽标处右键->选择管理员模式powershell

2. 资源管理器打开`C:\Windows\System32\drivers\etc\hosts`

3. 右键属性->取消勾选"只读"

4. 属性->安全->授予当前用户全部权限

5. 使用VSCode或Vim打开hosts文件

6. 添加ip，来源于[GitHub520](https://gitee.com/mi_chuan/GitHub520)

   ```powershell
   # GitHub520 Host Start
   140.82.113.25                 alive.github.com
   140.82.113.25                 live.github.com
   185.199.108.154               github.githubassets.com
   140.82.113.21                 central.github.com
   185.199.108.133               desktop.githubusercontent.com
   185.199.108.153               assets-cdn.github.com
   185.199.108.133               camo.githubusercontent.com
   185.199.108.133               github.map.fastly.net
   199.232.69.194                github.global.ssl.fastly.net
   140.82.114.3                  gist.github.com
   185.199.108.153               github.io
   140.82.113.4                  github.com
   192.0.66.2                    github.blog
   140.82.112.6                  api.github.com
   185.199.108.133               raw.githubusercontent.com
   185.199.108.133               user-images.githubusercontent.com
   185.199.108.133               favicons.githubusercontent.com
   185.199.108.133               avatars5.githubusercontent.com
   185.199.108.133               avatars4.githubusercontent.com
   185.199.108.133               avatars3.githubusercontent.com
   185.199.108.133               avatars2.githubusercontent.com
   185.199.108.133               avatars1.githubusercontent.com
   185.199.108.133               avatars0.githubusercontent.com
   185.199.108.133               avatars.githubusercontent.com
   140.82.112.9                  codeload.github.com
   52.217.197.185                github-cloud.s3.amazonaws.com
   54.231.132.25                 github-com.s3.amazonaws.com
   52.217.1.76                   github-production-release-asset-2e65be.s3.amazonaws.com
   52.217.203.169                github-production-user-asset-6210df.s3.amazonaws.com
   52.216.241.132                github-production-repository-file-5c1aeb.s3.amazonaws.com
   185.199.108.153               githubstatus.com
   64.71.144.211                 github.community
   23.100.27.125                 github.dev
   140.82.112.22                 collector.github.com
   13.107.42.16                  pipelines.actions.githubusercontent.com
   185.199.108.133               media.githubusercontent.com
   185.199.108.133               cloud.githubusercontent.com
   185.199.108.133               objects.githubusercontent.com
   
   
   # Update time: 2022-05-27T08:21:03+08:00
   # Update url: https://raw.hellogithub.com/hosts
   # Star me: https://github.com/521xueweihan/GitHub520
   # GitHub520 Host End
   ```

7. powershell中刷新网络 DNS 缓存 

   ```powershell
   ipconfig /flushdns
   ```

8. 选择站长之家中能ping通不超时，最快的ip进行访问

#### macOS

1. 查看写权限

   ```shell
   sudo ls -l /etc/ | grep hosts
   ```

2. 修改hosts

   ```shell
   sudo vim /etc/hosts
   ```

3. 添加ip地址

4. 刷新网络 DNS 缓存

   ```shell
   sudo killall -HUP mDNSResponder
   ```

#### Linux

1. 查看写权限

   ```shell
   sudo ls -l /etc/ | grep hosts
   ```

2. 修改hosts

   ```shell
   sudo vim /etc/hosts
   ```

3. 添加ip地址

4. 安装工具

   ```shell
   sudo apt install nscd 
   ```

5. 刷新网络 DNS 缓存

   ```shell
   sudo nscd restart
   sudo /etc/init.d/nscd restart
   ```

## 参考资料

[GitHub520](https://gitee.com/mi_chuan/GitHub520)

[修改 Hosts 解决 Github 访问失败](https://zhuanlan.zhihu.com/p/107334179)