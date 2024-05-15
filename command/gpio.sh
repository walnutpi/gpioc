#!/bin/bash
this_script_version_str="Script version : V1.0"

bin_file="/usr/bin/_gpiocommand"

declare -A STR_CN
declare -A STR_EN
declare -A STR_AUTO

STR_CN['command_para_error']="命令参数错误"
STR_EN['command_para_error']="command parameter error"
STR_CN['para_can_choose']="该位置可选命令行参数有这些"
STR_EN['para_can_choose']="Available parameters are"

STR_CN['help_pins_desc']="gpio pins \n\t显示所有引脚及当前状态"
STR_EN['help_pins_desc']="gpio pins  \n\tDisplays all pins and current status"

STR_CN['help_mode_desc']="gpio mode [PIN] [MODE] \n\t设置[PIN]引脚的工作模式为[MODE]"
STR_EN['help_mode_desc']="gpio mode [PIN] [MODE]  \n\tSet the [PIN] work as [MODE]"
STR_CN['help_mode_example']="example: \n\t gpio mode 41 IN_PULLUP\n  设置引脚41为输入模式,并开启上拉 \n"
STR_EN['help_mode_example']="example: \n\t gpio mode 41 IN_PULLUP\n  set the pin 41 as INPUT mode and open the pull-up \n"

STR_CN['help_write_desc']="gpio write [PIN] [VALUE] \n\t控制[PIN]输出[VALUE]电平"
STR_EN['help_write_desc']="gpio write [PIN] [VALUE] \n\tset the [PIN] output [VALUE]"
STR_CN['help_write_example']="example: \n\t    gpio write 42 1\n  设置引脚42为输出模式,并输出高电平 \n"
STR_EN['help_write_example']="example: \n\t    gpio write 42 1\n  set the pin 42 as OUTPUT mode and output high level \n"

STR_CN['help_toggle_desc']="gpio toggle [PIN] \n\t控制[PIN]输出电平翻转"
STR_EN['help_toggle_desc']="gpio toggle [PIN] \n\tFlip the [PIN] output level"
STR_CN['help_toggle_example']="example: \n\t    gpio toggle 42 \n  翻转42引脚的输出电平 \n"
STR_EN['help_toggle_example']="example: \n\t    gpio toggle 42 \n  Flip the output level on pin 42 \n"

STR_CN['help_read_desc']="gpio read [PIN]  \n\t读取[PIN]引脚当前输入电平"
STR_EN['help_read_desc']="gpio read [PIN]  \n\tread the input level on [PIN]"
STR_CN['help_read_example']="example: \n\t    gpio read 41 \n  读取引脚41当前输入电平 \n"
STR_EN['help_read_example']="example: \n\t    gpio read 41 \n  read the input level from pin 41 \n"

STR_CN['help_pin_desc']="gpio pin [keyword]  \n\t显示带[keyword]功能的引脚的位置"
STR_EN['help_pin_desc']="gpio pin [keyword]  \n\tDisplays the position of the [keyword] function pin"
STR_CN['help_pin_example']="example: \n\t    gpio pin pwm \n  显示各pwm引脚的位置 \n"
STR_EN['help_pin_example']="example: \n\t    gpio pin pwm \n  Displays the position of the pwm pins \n"

STR_CN[' ']=" "
STR_EN[' ']=" "


if [[ $LANG ==  zh_CN* ]]; then
    LOG_URL=$LOG_URL_CN
    for key in "${!STR_CN[@]}"; do
        STR_AUTO[$key]="${STR_CN[$key]}"
    done
else
    LOG_URL=$LOG_URL_EN
    for key in "${!STR_EN[@]}"; do
        STR_AUTO[$key]="${STR_EN[$key]}"
    done
fi


para3_do_mode(){
    $bin_file do_pri_mode_para $1 
}
para2_do_mode(){
    $bin_file do_pri_all_gpio_on_ph
}
do_mode(){
    if [ $# -lt 2 ];then
        echo -e "${STR_AUTO['help_mode_desc']}"
        echo -e "\n${STR_AUTO['help_mode_example']}"
        return 
    fi
    $bin_file mode $1 $2
}
para3_do_write(){
    $bin_file do_pri_write_para
}
para2_do_write(){
    $bin_file do_pri_all_gpio_on_ph
}
do_write(){
    if [ $# -lt 2 ];then
        echo -e "${STR_AUTO['help_write_desc']}"
        echo -e "${STR_AUTO['help_write_example']}"
        return 
    fi
    $bin_file write $1 $2
}

para2_do_toggle(){
    $bin_file do_pri_all_gpio_on_ph
}
do_toggle(){
    if [ $# -lt 1 ];then
        echo -e "${STR_AUTO['help_toggle_desc']}"
        echo -e "${STR_AUTO['help_toggle_example']}"
        return 
    fi
    $bin_file toggle $1 
}


para2_do_read(){
    $bin_file do_pri_all_gpio_on_ph
}
do_read(){
    if [ $# -lt 1 ];then
        echo -e "${STR_AUTO['help_read_desc']}"
        echo -e "\n${STR_AUTO['help_read_example']}"
        return 
    fi
    $bin_file read $1 
}

do_pins(){
    $bin_file pins
}

do_readall(){
    $bin_file pins
}

do_search(){
    $bin_file search $1
}
para2_do_pin(){
    $bin_file do_pri_pin_para
}
do_pin(){
    if [ $# -lt 1 ];then
        echo -e "${STR_AUTO['help_pin_desc']}"
        echo -e "\n${STR_AUTO['help_pin_example']}"
        return 
    fi
    $bin_file pin $1
}

do_-h(){
    echo -e "$this_script_version_str\n"
    echo -e "${STR_AUTO['help_pins_desc']}\n"
    echo -e "${STR_AUTO['help_pin_desc']}\n"
    echo -e "${STR_AUTO['help_mode_desc']}\n"
    echo -e "${STR_AUTO['help_read_desc']}\n"
    echo -e "${STR_AUTO['help_write_desc']}\n"
    echo -e "${STR_AUTO['help_toogle_desc']}\n"
}

if [[ "$1" == para* ]] ;then
    FUNCTION_NAME="$1"
else
    FUNCTION_NAME="do_$1"
fi
shift

check_para() {
    para_num=$1
    para_str=$2
    para_key2=$3
    if [ ! -z "$para_str" ]; then
        para_function_name="para${para_num}_$FUNCTION_NAME"
        if declare -f $para_function_name > /dev/null; then
            IFS=' ' read -ra ADDR <<< `$para_function_name  $para_key2`
            for i in "${ADDR[@]}"; do
                temp1=$(echo $i | tr [a-z] [A-Z])    # 转变成大写再做比较
                temp2=$(echo $para_str | tr [a-z] [A-Z])    # 转变成大写再做比较

                if [ x"$temp1" = x"$temp2" ];then        # x$"temp1"前面加x防止其中为空
                    return
                fi
            done
            echo "${STR_AUTO['command_para_error']}  --> $para_str"
            echo -e "${STR_AUTO['para_can_choose']}"
            echo -e "\n\t${ADDR[@]}\n"
            exit 0
        fi
    fi
}
# 如果函数存在，执行它
if declare -f $FUNCTION_NAME > /dev/null; then
    paras=$@
    para_key2=$1
    para_num=2
    while [ ! -z "$1" ]
    do
        check_para $para_num $1 $para_key2
        let para_num++
        shift
    done
    $FUNCTION_NAME $paras
else
    do_-h
fi


