// gcc use.c -lmylibrary

#include <darray.h>

int main(){
    int carray[] = {1, 2, 3};
    Darray *arr = array_from_carray(carray, 3, sizeof(int));
    array_delete(arr);
    return 0;
}

