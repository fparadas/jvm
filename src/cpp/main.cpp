#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "../h/dotclass.h"
#include "../h/reader.h"
#include "../h/printer.h"
#include "../h/deinit.h"
#include "../h/jvm.h"

int main(int argc, char *argv[]) {
    char filename[BUFSIZ], option[BUFSIZ];
    classfile cf = {0};
    JVM mem = {0};
    char *class_name;
    if (argc != 2 && argc != 3) {
        printf("Usage: %s [class file] [--summary | --show-all]\n", argv[0]);
        return 0;
    }

    if(argc == 2) {
        strcpy(option, "default");
    } else {
        strcpy(option, argv[2]);
    }

    class_name = strrchr(argv[1], '/');
    strcpy(filename, argv[1]);
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        std::cout << "Error opening file" << filename << std::endl;
        return 1;
    }
    
    if(read_class_file(&cf, fp)) {
        populate_acc_maps();

        init_opargs();
        char *src_file = strtok(get_source_file(&cf), ".");
        char *this_file = strtok(filename, ".");
        if(strcmp(src_file, this_file)) {
            std::cout << "File name differs of source file name, aborting " << src_file << std::endl;
            return 1;
        }
        if(!strcmp(option, "default") || !strcmp(option, "--execute")) {
            init_jvm(&mem);

            jvm_load_class(&mem, argv[1]);
            jvm_set_current_class(&mem, class_name);
            jvm_exec_clinit(&mem);
            jvm_set_current_method(&mem, "main");

            jvm_push_frame(&mem);
            jvm_run(&mem);

            deinit_jvm(&mem);
        } else if (!strcmp(option, "--show-all")) {
            print_all(&cf);
        }


        deinit_class_file(&cf);
    }
    

    fclose(fp);

    return 0;
}
