//
//  main.cpp
//  Trabalho1
//
//  Created by Ludgero Mascarenhas on 30/08/17.
//  Copyright © 2017 Ludgero Mascarenhas. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, const char * argv[]) {

    int coordX, coordY,frame, numframe, temp, i, contpeople=0, contframes=0;
    
    char url[]="Paths_D.txt";
    
    FILE *arq;
    
    arq = fopen(url, "rt");
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
        fscanf(arq,"[%d]",&temp);
        
        while(1){
            
            
            fscanf(arq,"%d",&numframe);
            
            if(fscanf(arq,"%d",&numframe)) break; // NAO SEI PORQUE ISSO FUNCIONA?????
    
            contpeople++;
            if (numframe > contframes) contframes = numframe;
            
            printf("\n%d\n", numframe);
            
            for(i=1;i<=numframe;i++)
            {
             fscanf(arq," (%d,%d,%d)",&coordX, &coordY, &frame);
             printf( "(" "%d,%d,%d" ")",coordX, coordY, frame);
            }
            
        }
    }
    
    
    fclose(arq);
    
    return 0;
    

}
