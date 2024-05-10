#!/bin/bash
PATH_PWD="$(dirname "$(realpath "${BASH_SOURCE[0]}")")"

bin_file="sudo ${PATH_PWD}/gpioc"



para3_do_mode(){
    $bin_file do_pri_mode_para $1 
}
para2_do_mode(){
    $bin_file do_pri_all_gpio_on_ph
}
do_mode(){
    $bin_file mode $1 $2
}
para3_do_write(){
    $bin_file do_pri_write_para
}
para2_do_write(){
    $bin_file do_pri_all_gpio_on_ph
}
do_write(){
    $bin_file write $1 $2
}

para2_do_toggle(){
    $bin_file do_pri_all_gpio_on_ph
}
do_toggle(){
    $bin_file toggle $1 
}


para2_do_read(){
    $bin_file do_pri_all_gpio_on_ph
}
do_read(){
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
    $bin_file pin $1
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
        para_function_name="para${para_num}_$FUNCTION_NAME $para_key2"
        if declare -f $para_function_name > /dev/null; then
            IFS=' ' read -ra ADDR <<< `$para_function_name`
            for i in "${ADDR[@]}"; do
                if [ "$i" == "$para_str" ]; then
                    return
                fi
            done
            echo "command  parameter error"
            exit 0
        fi
    fi
}
# 如果函数存在，执行它
if declare -f $FUNCTION_NAME > /dev/null; then
    paras=$@
    para_key2=$2
    para_num=2
    while [ ! -z "$1" ]
    do
        if [ ! -z "$1" ]; then
            check_para $para_num $1 $para_key2
            let para_num++
            shift
        fi
    done
    $FUNCTION_NAME $paras
fi


