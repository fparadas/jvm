#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "../h/dotclass.h"
#include "../h/reader.h"
#include "../h/printer.h"
#include "../h/deinit.h"

int main(int argc, char *argv[]) {
    char filename[BUFSIZ], option[BUFSIZ];
    classfile cf = {0};

    if (argc != 2 && argc != 3) {
        printf("Usage: %s [class file] [--summary | --show-all]\n", argv[0]);
        return 0;
    }

    if(argc == 2) {
        strcpy(option, "default");
    } else {
        strcpy(option, argv[2]);
    }

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
        if(!strcmp(option, "default") || !strcmp(option, "--summary")) {
            print_summary(&cf);
        } else if (!strcmp(option, "--show-all")) {
            print_all(&cf);
        }


        deinit_class_file(&cf);
    }
    

    fclose(fp);

    return 0;
}
