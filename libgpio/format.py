import re


# 将SUNXI_FUNCTION的参数2替换为指定内容
def replace_desc_into_fun(line, new_desc):
    mat_desc = re.search(r"\"[\S]*\"", line)
    if mat_desc:
        line = line[0 : mat_desc.start(0)] + '"' + new_desc + '"),\n'
    return line


# 将注释的内容插入为SUNXI_FUNCTION的参数2
def replace_desc_as_notes(line):
    mat_desc = re.search(r"\"[\S]*\"", line)
    if mat_desc:
        mat_note = re.search(r"/\* [\S]* \*/", line)
        if mat_note:
            note = mat_note.group(0)[3:-3]
            return replace_desc_into_fun(line, note)
    return line


def format_sunxi_function_lines(input_file_path, output_file_path):
    with open(input_file_path, "r") as file:
        lines = file.readlines()
    with open(output_file_path, "w") as file:
        for line in lines:
            mat_line = re.search(r"SUNXI_FUNCTION\([\s\S]*", line)
            if mat_line:
                # 将注释替换进函数内
                new_line = replace_desc_as_notes(line)
                mat_desc = re.search(r"\"[\S]*\"", new_line)
                if mat_desc:
                    desc = mat_desc.group(0)[1:-1]

                    # if "spi" in desc:
                    #     print("spi\t raw:", desc, end="")
                    #     # 删除/后面的字符
                    #     if desc.find("/") != -1:
                    #         desc = desc[0 : desc.find("/")]
                    #     desc
                    #     print("\t end:", desc)
                    #     new_line = replace_desc_into_fun(new_line, desc)

                    if "s_pwm" in desc:
                        print("s_pwm\t raw:", desc, end="")
                        desc = desc[5:]
                        pwm_num = 20 + int(desc[desc.find("_") + 1 :])
                        print(" match=", pwm_num, end="")
                        desc = "pwm" + str(pwm_num)
                        new_line = replace_desc_into_fun(new_line, desc)
                        print("\t end:", desc)
                    elif "mcu_pwm" in desc:
                        print("mcu_pwm\t raw:", desc, end="")
                        desc = desc[7:]
                        pwm_num = 22 + int(desc[desc.find("_") + 1 :])
                        print(" match=", pwm_num, end="")
                        desc = "pwm" + str(pwm_num)
                        new_line = replace_desc_into_fun(new_line, desc)
                        print("\t end:", desc)
                    elif "pwm" in desc:
                        print("pwm\t raw:", desc, end="")
                        pwm_num = int(desc[3 : desc.find("_")]) * 16 + int(
                            desc[desc.find("_") + 1 :]
                        )
                        print(" match=", pwm_num, end="")
                        desc = "pwm" + str(pwm_num)
                        new_line = replace_desc_into_fun(new_line, desc)
                        print("\t end:", desc)

                file.write(new_line)
                continue

            file.write(line)


input_file_path = "pinctrl-sun55iw3-r.c"
# input_file_path = "pinctrl-sun55iw3.c"
output_file_path = "格式化.c"
format_sunxi_function_lines(input_file_path, output_file_path)
