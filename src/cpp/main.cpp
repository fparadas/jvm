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
    
    std::cout << "=============reading file=============" << std::endl;
    if(read_class_file(&cf, fp)) {
        std::cout << "=============file read=============" << std::endl;
        std::cout << "=============populating acc maps=============" << std::endl;
        populate_acc_maps();
        std::cout << "=============acc maps populated=============" << std::endl;

        std::cout << "=============populating opargs=============" << std::endl;
        init_opargs();
        std::cout << "=============opargs populated=============" << std::endl;



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
