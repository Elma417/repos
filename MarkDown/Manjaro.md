# __Manjaro__

### __常用命令__

___Service___
>Tomcat Mysql5.7.n
  1. Mysql
    * 启动Mysql服务
    > sudo /usr/local/mysql/support-files/mysql.server start/stop 
    * 登陆
    >  bin/mysql -u root -p


___Cpu___ （考虑做成脚本）
1.  __开启boost__ 
>\# echo "1" > /sys/devices/system/cpu/cpufreq/boost
1. __关闭boost 省电__
>\# echo "0" > /sys/devices/system/cpu/cpufreq/boost

___Fan___   
通过Nbfc控制 
参考见URL    
https://wiki.archlinux.org/index.php/fan_speed_control#NBFC   
>nbfc status -a    确认风扇以及温度状态   
>nbfc set -a   自动模式    
>nbfc set -s  100 满载   
安装
   >yay -S nbfc

启用与配置 

    >sudo mv /opt/nbfc/Plugins/StagWare.Plugins.ECSysLinux.dll /opt/nbfc/Plugins/StagWare.Plugins.ECSysLinux.dll.old   
    >sudo systemctl enable nbfc --now    
    >nbfc config -r   
    >nbfc config --apply ""  

***
### __生产力__
1.  Zsh  
*  安装
>sudo pacman -S zsh
* 修改默认shell为zsh
>chsh -s /usr/bin/zsh
* 安装ohmyzsh（记得挂代理）
>wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | sh
* 安装插件
  * 安装zsh-syntax-highlighting：提供命令高亮
    >git clone https://github.com/zsh-users/zsh-syntax-highlighting.git ${ZSH_CUSTOM:-~/.oh-my-zsh/custom}/plugins/zsh-syntax-highlighting
  * 安装autosuggestions：记住你之前使用过的命令
    >git clone git://github.com/zsh-users/zsh-autosuggestions ~/.oh-my-zsh/custom/plugins/zsh-autosuggestions
  * 安装incr：命令联想与自动补全
    >git clone git://github.com/makeitjoe/incr.zsh $ZSH_CUSTOM/plugins/incr
  * 安装thefuck：帮你更加高效地学习linux命令
    >pip install --user thefuck
  * 启动所有插件
    * nano ~/.zshrc  

        修改 plugins=(git zsh-syntax-highlighting zsh-autosuggestions colored-man-pages sudo extract)   
        在最后一行添加 source ~/.oh-my-zsh/plugins/incr/incr*.zsh

    * 修改konsole的默认bash为zsh   
    >source ~/.zshrc
* 终端美化
    * 安装powerlevel10k主题   
    详细说明见https://github.com/romkatv/powerlevel10k#meslo-nerd-font-patched-for-powerlevel10k
    >git clone --depth=1 https://github.com/romkatv/powerlevel10k.git $ZSH_CUSTOM/themes/powerlevel10k
    * 安装所需的字体并选用
    * 启用主题
    >nano ~/.zshrc   
    改ZSH_THEME="powerlevel10k/powerlevel10k"  
    重启zsh    
    >p10k configure 进入配置界面 
    * 安装neofetch
    >pacman -S neofetch
    * 安装parrotsay
    >npm install --global parrotsay  
    >~/.oh-my-zsh/custom 新建一个名为hello.zsh的文件  
    >parrotsay "你想看到的内容"
    记得调节你的p10k configure 为quite 否则每次自启动都会报错
2.  Visual Studio Code
   >C/C++ Python MarkDown   
  * C/C++       

    1. 安装g++ gdb   
    >g++ --vision  
    >gdb --vision   

    只缺少gdb因此
    >sudo pacman -S gdb
    1. 安装插件
    * C/C++
    * C++ Intellisense
  
    1. 编写测试代码并点击生成launch.json和task.json 选择gdb g++ 运行则完成
    2. 关于include问题
    >\$gcc -v -E -x c++ -    

    检查#include路径并添加到C/C++ Configurations中
    >运行 Ctrl+Shift+P 选择 C/C++编辑配置在包含路径中添加
    
    例如添加
     
    >/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/../../../../include/c++/10.2.0
    >/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/../../../../include/c++/10.2.0/x86_64-pc-linux-gnu
    >/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/../../../../include/c++/10.2.0/backward
    >/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include
    >/usr/local/include
    >/usr/lib/gcc/x86_64-pc-linux-gnu/10.2.0/include-fixed
    >/usr/include

    添加后检查c_cpp_properties.json   
    正常 则可以使用#include  
   
  * 插件推荐
    * GitHub Pull Requests and Issues
    //支持直接pull push
    
    应先安装gnome-keyring
    >sudo pacman -S gnome-keyring

    * Python  
    * Markdown ALL in One  //Markdown格式支持
    * Markdown Preview Enhanced //Markdown预览
    * Draw.io Integration  流程图
    * chinese   中文
    * Brackets Pair Colorize 彩虹括号
    * One Dark Pro 主题
3. IDEA
>Java8 Tomcat Mysql 
  * Tomcat
    * 1
  * Java8 
  采用adopt-openjdk-1.8.0_275 IDEA内下载
    * 配置环境路径
    > kate /etc/profile    

    最后加上以下行
    ```
    # Setting for jdk-oracle
    export JAVA_HOME=/home/null/.jdks/adopt-openjdk-1.8.0_275
    export JRE_HOME=${JAVA_HOME}/jre
    export CLASSPATH=.:${KAVA_HOME}/lib:${JRE_HOME}/lib
    export PATH=${JAVA_HOME}/bin:$PATH
    # End
    ```
    启用配置
    >source /etc/profile
    测试
    >java -version
     
  * MySql
    * 下载5.7.xx的数据库
    * 解压
    >tar -xzvf ～/Download/mysql-5.7.xx-linux-glibc2.5-x86_64.tar.gz
    * 移动并修改名字
    >mv ~/Download/mysql-5.7.xx-linux-glibc2.5-x86_64   /usr/local/mysql
    * 创建mysql数据库存放的路径
    >mkdir /usr/local/mysql/data 
    * 安装依赖
    >sudo pacman -S numactl
    >sudo pacman -S ncurses5-compat-libs 
    * 创建用户组
    >cd /usr/local  
    >sudo groupadd mysql//创建用户组mysql    
    >sudo useradd -r -g mysql mysql //-r参数表示mysql用户是系统用户，不可用于登录系统，创建用户mysql并将其添加到用户组mysql中  
    >sudo chown -R mysql mysql/  
    >sudo chgrp -R mysql mysql/ 
    * 修改配置文件
    > kate /etc/my.cnf
    > sudo chomd 644 my.cnf
    * 添加文件内容  
    ``` 
    [client]
    default-character-set=utf8
    port = 3306
    socket = /tmp/mysql.sock

    [mysql]
    default-character-set=utf8
    port = 3306
    socket = /tmp/mysql.sock

    [mysqld]  
    character_set_server=utf8   
    init_connect='SET NAMES utf8'   
    basedir=/usr/local/mysql    
    datadir=/usr/local/mysql/data   
    socket=/tmp/mysql.sock   
    log-error=/var/log/mysqld.log   
    pid-file=/var/run/mysqld/mysqld.pid   

    >\#不区分大小写
    lower_case_table_names = 1    
    sql_mode=STRICT_TRANS_TABLES,       NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER,NO_ENGINE_SUBSTITUTION
    max_connections=5000
    default-time_zone = '+8:00'

    \#开启查询缓存
    explicit_defaults_for_timestamp=true
    ```
    * 切换到/var/log/创建日志文件mysqld.log并设置读写权限
    > cd /var/log
      touch mysqld.log
      chmod 777 mysqld.log
    * 切换到/var/run/创建mysqld 并创建mysqld.pid并设置读写权限
    > sudo mkdir /var/run/mysqld   
      touch mysqld.pid      
      chmod 777 mysqld.pid      
    * 切换到mysql目录下并初始化数据库
    > cd /usr/local/mysql
      sudo bin/mysqld --initialize --user=mysql 
    * 启动Mysql服务
    > sudo /usr/local/mysql/support-files/mysql.server start 
    * 登陆并修改密码
    >  bin/mysql -u root -p
    
    初始密码在 /var/log/mysqld.log中可以找到
    > ALTER USER root@localhost IDENTIFIED BY '你要修改的密码';


  * 插件推荐
    * Alibaba Java Coding Guidelines
    * Chinese
    * Codota
    * Material Theme UI
    * Translation

***
### 美化
1. latte-dock
>sudo pacman -S latte-dock
2. application title
3. Theme    
    Adapta Kde
4. Icon  
   Papirus-Dark 包备份在Tim里
***
### __常用软件__
1. 微信 TIM
>yay -S com.qq.office.deepin com.qq.weixin.deepin 

    安装完成后WINE配置字体大小

>env WINEPREFIX="\$HOME/.deepinwine/Deepin-TIM" winecfg
>env WINEPREFIX="\$HOME/.deepinwine/Deepin-WeChat" /usr/bin/deepin-wine winecfg

    manjaro kde 会与TIM冲突
    先安装xsettingsd并将其添加到开机启动项中
>sudu pacman -S xsettingsd

    关于微信中聊天打字中文显示方块

>下载一个宋体字体文件simsun.ttf，如果你有Windows，也可以直接在C:\Windows\Fonts中找到。把这个文件拷贝到Manjaro中你的家目录里的.deepinwine/Deepin-WeChat/drive_c/windows/Fonts目录中重启即可

2. qV2ray
   
   >https://github.com/Qv2ray/Qv2ray
   
   >建议从AUR商店下载

3. chrome
>sudo pacman -S google-chrome

    在设置里修改Dark主题
    以及在设置->应用程序->文件关联->.html中 将Chrome置顶
4. Proxychains-ng
>yay -S proxychains-ng    

修改[ProxyList]为 socks5  127.0.0.1:xxx
>/etc/proxychains.conf

终端调用则在前加proxychains

5. 网易云音乐

商店中的网易云无法搜索栏无法输入中文

解决方案如下
>https://gitee.com/ForMat1/netease-cloud-music_For_Arch

6. Libreoffice
>yay -S libreoffice    

选择still版本下载 在设置中下载后修改语言包和 以及图标

***
待测试

3. Dingtalk

****
### __安装后配置__
1. 设置mirror
>kate /etc/pacman.d/mirrorlist
    
     添加以下镜像

>\## Country : China
Server = https://mirrors.bfsu.edu.cn/manjaro/stable/\$repo/\$arch

>\## Country : China
Server = https://mirrors.tuna.tsinghua.edu.cn/manjaro/stable/\$repo/\$arch

2. 更新软件源
>sudo pacman -Syyu
3. 点开设置更新内核
4. 加入archlinuxcn源
>kate /etc/pacman.conf
    
    添加两行
>[archlinuxcn]
Server = https://mirrors.bfsu.edu.cn/archlinuxcn/\$arch

>sudo pacman -S archlinuxcn-keyring

5. 安装必要的软件 

yay
>sudo pacman -S yay

fcitx5
>sudo pacman -S fcitx5-git fcitx5-gtk fcitx5-qt5-git fcitx5-chinese-addons-git fcitx5-pinyin-zhwiki fcitx5-configtool

    安装后不要忘记添加 开机启动 调整字体大小 以及手动配置
>kate ~/.pam_environment
>INPUT_METHOD  DEFAULT=fcitx5
>GTK_IM_MODULE DEFAULT=fcitx5
>QT_IM_MODULE  DEFAULT=fcitx5
>XMODIFIERS    DEFAULT=\@im=fcitx5

字体
1. Ubuntu字体包
>sudo pacman -S ttf-ubuntu-font-family
2. 文泉驿微米黑
>sudo pacman -S wqy-microhei

base-devel软件包组
>sudo pacman -S base-devel

Nodejs num
>sudo pacman -S nodejs npm
***
