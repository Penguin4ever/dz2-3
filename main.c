#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    int mode;
    printf("Введите 0 для ориентированного графа \nИли 1 для неориентированного\n");
    scanf("%d", &mode);
    
    if(!( mode == 1 || mode == 0 )){
        printf("О\nШ\nИ\nБ\nК\nА\n");
        exit(101);
    }
    
    printf("Введите количество вершин:\n> ");
    int Ver;
    scanf("%d",&Ver);
    if (Ver <= 0){
        printf("Не пойдет, давай по новой\n");
        exit(102);
    }
    
    getchar();
    printf("Название вершиш\n");
    
    char **table;
    table = calloc(Ver, sizeof(char*));
    for(int i=0; i<Ver; i++){
        table[i] = calloc(Ver+1, sizeof(char));
    }
    
    for(int i=0; i<Ver; i++){
        printf("%d: ",i);
        table[i][0] = getchar();
        getchar();

        if(!(('A' <= table[i][0] && table[i][0] <= 'Z') || ('a' <= table[i][0] && table[i][0] <= 'z'))){
            printf("Введите букву!\n");
            i--;
        } else {
            for(int j=0; j<i; j++){
                if( table[i][0] == table[j][0] ){
                    printf("Введите другую букву\n");
                    i--;
                }
            }
        }
    }
        
    for(int i=0; i<Ver; i++){
        for(int j=1; j<Ver; j++){
            table[i][j] = 0;
        }
    }
    
    printf("Для каждой вершины введите связь\n");
    for(int i=0; i<Ver; i++){
        printf("%c -> ", table[i][0]);
        char c;
        int flag = 1;
        while(flag){
        scanf("%c", &c);
            if(c == '\n'){
                flag = 0;
            } else {
                if(c-'0' <= Ver){
                    table[i][c-'0']++;
                }
            }
        }
    }

    printf("\n");
    int graph_check = 1;
    
    for(int i=0; i<Ver; i++){
        int temp_graph_check = 0;
        for(int j=0; j<Ver; j++){
            if(table[i][j+1] == 1)
                temp_graph_check = 1;
    
            if(table[j][i+1] == 1)
                temp_graph_check = 1;
        }
        if(temp_graph_check == 0)
            graph_check=0;
    }
    
    if(graph_check == 0){
        printf("Граф несвязанный\n");
    } else {
        printf("Граф свзяанный\n");
    }
     printf("\n");
    for(int i=0; i<Ver; i++) {
        
        printf("%c: ", table[i][0]);
        
        for (int j=1; j<Ver+1; j++) {
            printf("%d  ", table[i][j]);
        }
        printf("\n");
    }
    char command[1024] = {0};
    char arrow[3] = "";
        strcat(command, "echo ' ");
    if(mode == 0){
        strcat(command, "digraph G {");
        strcat(arrow, "->");
    } else {
        strcat(command, "graph G {");
        strcat(arrow, "--");
    }
    for(int i=0; i<Ver; i++){
        char elem[3] = "";
        elem[0] = table[i][0];
        strcat(command, elem);
        strcat(command, "; ");
    }
    for(int i=0; i<Ver; i++){
        for(int j=0; j<Ver; j++){
            for(int k=0; k<table[i][j+1]; k++){
                char elem[2] = "";
                elem[0] = table[i][0];
                
                strcat(command, elem);
                strcat(command, arrow);
                
                elem[0] = table[j][0];
                strcat(command, elem);
                strcat(command, "; ");
            }
        }
    }
    strcat(command, "}' | dot -Tpng > ./graph.png");
    system(command);
    return 0;
}

