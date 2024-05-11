#!/bin/bash
_gpio () {
    local cur=${COMP_WORDS[COMP_CWORD]}
    if [ $COMP_CWORD -eq 1 ]; then
        local functions=$(grep -oP '^do_\w+\s*\(\)' /usr/bin/gpio | sed 's/do_//g' | sed 's/()//')
        COMPREPLY=($(compgen -W "$functions" -- $cur))
    elif [ $COMP_CWORD -gt 1 ]; then
        local function_name=${COMP_WORDS[1]}
        local para_function="para${COMP_CWORD}_do_${function_name}"
        local second_arg=${COMP_WORDS[2]}
        local options=$(bash -c "/usr/bin/gpio $para_function $second_arg")
        COMPREPLY=($(compgen -W "$options" -- $cur))
    fi
}
complete -F _gpio gpio
