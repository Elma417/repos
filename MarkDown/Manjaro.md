# __Manjaro__

### __常用命令__
___Cpu___ （考虑做成脚本）
1.  __开启boost__ 
>#### # echo "1" > /sys/devices/system/cpu/cpufreq/boost
2. __关闭boost 省电__
>#### # echo "0" > /sys/devices/system/cpu/cpufreq/boost

___Fan___

参考见URL    
https://wiki.archlinux.org/index.php/fan_speed_control#NBFC   
1. 通过Nbfc控制   
    https://www.rockyourcode.com/fan-speed-control-on-manjaro-linux-with-nbfc/

    安装
   >yay -S nbfc
    启用与配置
    >sudo mv /opt/nbfc/Plugins/StagWare.Plugins.ECSysLinux.dll /opt/nbfc/Plugins/StagWare.Plugins.ECSysLinux.dll.old   
    >sudo systemctl enable nbfc --now    
    >nbfc config -r   
    >nbfc config --apply ""  

***
### __生产力__
1.  Visual Studio Code
   >C/C++ Python MarkDown 

* C/C++   
    1. 安装g++ gdb   
    >g++ --vision  
    >gdb --vision   

    只缺少gdb因此
    >sudo pacman -S gdb
    2. 安装插件
    * C/C++
    * C++ Intellisense
  
    3. 编写测试代码并点击生成launch.json和task.json 选择gdb g++ 运行则完成
    4. 关于include问题
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

1. IDEA
>Java8 Tomcat Mysql 
* 插件推荐
  * github
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

***
待测试

1. WPS
>sudo pacman -S wps-office-cn wps-office-mime-cn wps-office-mui-zh-cn ttf-wps-fonts

3. Dingtalk
4. 网易云音乐


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

***
