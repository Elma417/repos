# __Manjaro__

### __常用命令__
___Cpu___ （考虑做成脚本）
1.  __开启boost__ 
>#### # echo "1" > /sys/devices/system/cpu/cpufreq/boost
2. __关闭boost 省电__
>#### # echo "0" > /sys/devices/system/cpu/cpufreq/boost

___Fan___

    参考见URLhttps://wiki.archlinux.org/index.php/fan_speed_control#NBFC   
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