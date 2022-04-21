#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "RLEList.h"
#include "AsciiArtTool.h"
#include "assert.h"

#define N 101
char myMapFunction(char c);

int main(){

    RLEListResult result;
    RLEList list = NULL;
    char* string = NULL;

    //Check Function Create
    list = RLEListCreate();
    assert(list);

    //Check Function Size for Empty List
    int size = RLEListSize(list);
    assert(size == 0);

    //Check Function Append
    assert(RLEListAppend(NULL, 'a') == RLE_LIST_NULL_ARGUMENT);
    assert(RLEListAppend(list, 0) == RLE_LIST_NULL_ARGUMENT);   
    RLEListAppend(list, '1');
    for (int i = 0; i < N; i++){
        assert(RLEListAppend(list, 'a') == RLE_LIST_SUCCESS);
    }

    //test1 - Current string should hold the string in test1
    string = RLEListExportToString(list, &result);
    assert(result == RLE_LIST_SUCCESS);
    char test1[] = "11\na101\n";
    if(strcmp(test1, string)!=0){
        free(string);
        printf("Error in test1\n");
        exit(1);
    }
    //Check Function Size for standart list
    size = RLEListSize(list);
    assert(size == 102);
    free(string);

    //test2 - Current string should hold the string in test2
    RLEListRemove(list, 0);
    RLEListRemove(list, 0);
    char test2[] = "a100\n";
    string = RLEListExportToString(list, NULL); //You should be able to pass NULL here
    if(strcmp(test2, string)!=0){
        free(string);
        printf("Error in test2\n");
        exit(2);
    }
    free(string);

    //Check Function Size for standart list
    size = RLEListSize(list);
    assert(size == 100);

    //Check function remove
    assert(RLEListRemove(NULL, 0) == RLE_LIST_NULL_ARGUMENT);
    assert(RLEListRemove(list, 100) == RLE_LIST_INDEX_OUT_OF_BOUNDS);
    for (int i = 0; i < 100; i++){
        assert(RLEListRemove(list, 0) == RLE_LIST_SUCCESS);
    }

    //List is now empty----------------------------------------------
    size = RLEListSize(list);
    assert(!size);

    //Check function Get
    char get_char;
    get_char = RLEListGet(0, 0, NULL); //You should be able to pass NULL here
    get_char = RLEListGet(0, 0, &result);
    assert(result == RLE_LIST_NULL_ARGUMENT);
    assert(get_char == 0);
    char sleeping_cat[] = "      |\\      _,,,---,,_\nZZZzz /,`.-'`'    -.  ;-;;,_\n     |,4-  ) )-,_. ,\\ (  `'-'\n    /_---''(_/--'  `-'\\_)";
    for (int i = 0; i < sizeof(sleeping_cat) - 1; i++){
        assert(RLEListAppend(list, sleeping_cat[i]) == RLE_LIST_SUCCESS);
    }
    get_char = RLEListGet(list, sizeof(sleeping_cat), &result);
    assert(result == RLE_LIST_INDEX_OUT_OF_BOUNDS);
    get_char = RLEListGet(list, 0, &result);
    assert(get_char == ' ');
    get_char = RLEListGet(list, 7, &result);
    assert(get_char == '\\');
    get_char = RLEListGet(list, 24, &result);
    assert(get_char == '\n');
    get_char = RLEListGet(list, sizeof(sleeping_cat) + 1, &result);
    assert(get_char == 0);
    assert(result == RLE_LIST_INDEX_OUT_OF_BOUNDS);

    printf("Attempting to destroy list.\n");
    RLEListDestroy(list);
    printf("Passed attempt to destroy list.\n");
    list = RLEListCreate();

    //Check Export to string
    RLEListAppend(list, 'a');
    RLEListAppend(list, 'a');
    RLEListAppend(list, 'a');
    RLEListAppend(list, 'b');
    RLEListAppend(list, 'b');
    RLEListAppend(list, 'b');
    RLEListAppend(list, 'c');
    RLEListAppend(list, 'c');
    RLEListAppend(list, 'c');
    RLEListAppend(list, 'd');
    RLEListAppend(list, 'd');
    RLEListAppend(list, 'd');
    size = RLEListSize(list);
    assert(size == 12);
    string = RLEListExportToString(NULL, &result);
    assert(result == RLE_LIST_NULL_ARGUMENT);
    if(string != NULL){
        free(string);
        printf("String should be NULL but is not\n");
        exit(3);
    }
    string = RLEListExportToString(list, &result);
    char test3[] = "a3\nb3\nc3\nd3\n";
    assert(strcmp(test3, string) == 0);
    free(string);

    //Test map function
    RLEListMap(list, myMapFunction);
    assert(result == RLE_LIST_SUCCESS);
    string = RLEListExportToString(list, &result);
    assert(string);
    char test4[] = "a3\nb3\nc3\ne3\n";
    assert(strcmp(test4, string) == 0);
    free(string);

    printf("Hurray - Test passed. Here is a Sleeping cat:\n\n%s\n\n", sleeping_cat);
    return 0;
}

char myMapFunction(char c){
    if (c == 'd')
        return 'e';
    else 
        return c;
}
