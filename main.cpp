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
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <vector>


typedef struct Coord {
    int x;
    int y;
    int f;
};

std::vector<int> limits;

static int contpeople;
static int contframes;

Coord abc [14][375];


void Desenha(void)
{
    
    float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    
    // Limpa a janela de visualizaÁ„o com a cor branca
    glClearColor(1,1,1,0);
    glClear(GL_COLOR_BUFFER_BIT);
    

    
    // Desenha um triangulo no centro da janela
    glLineWidth(1);
    glBegin(GL_LINES);
    
    
    for(int l=0;l<contpeople;l++){
        float r = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float g = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        float b = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        glColor3f(r,g,b);
        for(int c=0;c<contframes;c++){
        if(abc [l][c].x != 0 && abc [l][c].y !=0){
            glVertex2f(abc [l][c].x,abc [l][c].y);
        }
      }
    }
    
    glEnd();
    
    //Executa os comandos OpenGL
    glFlush();
}

void DesenhaAux(void){
    //
}


void Cross(void){ // 2 ou mais pessoas com as mesmas coord e o mesmo frame
    
    for(int l=0;l<contpeople;l++){
        for(int c=0;c<contframes;c++){
			for(int aux=l+1;aux<contpeople+1;aux++){//varrer as linhas de baixo
				if(abc [l][c].f == abc [aux][c].f){
					if(abc [l][c].x == abc [aux][c].x && abc [l][c].y == abc [aux][c].y){
                    //chama a funcao para plotar as trajetorias
					for(int auxcoluna=0;auxcoluna<contframes;auxcoluna++){
						glVertex2f(abc [l][auxcoluna].x,abc [l][auxcoluna].y);
						glVertex2f(abc [aux][auxcoluna].x,abc [aux][auxcoluna].y);
                    }
                }
			}
         
        }
    }
    
}

void Split(void){ // TALVEZ PEGAR UM EVENTO MAIS FACIL
    
    for(int l=0;l<contpeople;l++){
        for(int c=0;c<contframes;c++){
            //comparar duas trajetorias que seguem proximas por no minimo 3 frames e depois se afastam
        }
    }
    
    
}


void Grupo(void){ //
    
    for(int l=0;l<contpeople;l++){
        for(int c=0;c<contframes;c++){
            //comparar 3 trajetorias que seguem proximas por no minimo 3 frames(distancia menor que 5)
        }
    }

}

void Afastamento(void){ //
    
    for(int l=0;l<contpeople;l++){
        for(int c=0;c<contframes;c++){
            //comparar duas trajetorias que seguem proximas por no minimo 3 frames e depois se afastam(mais de 5 de distancia)
        }
    }

}




// FunÁ„o callback chamada para gerenciar eventos de teclas
void Teclado (unsigned char key, int x, int y)
{
    if (key == 27)
        exit(0);
}

// FunÁ„o respons·vel por inicializar par‚metros e vari·veis
void Inicializa(void)
{
    // Define a janela de visualizaÁ„o 2D
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1800.0,0.0,1800);
    glMatrixMode(GL_MODELVIEW);
}



int main(void) {

    
    int argc = 0;
    char *argv[] = { (char *)"gl", 0 };
    
    int coordX, coordY,frame, numframe, temp, i;
    
    char url[]="Paths_D.txt";
    
    FILE *arq;
    
    arq = fopen(url, "rt");
    
    
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
        fscanf(arq,"[%d]",&temp);
        
        while(1){
            
            fscanf(arq,"%d",&numframe);
            
            if(fscanf(arq,"%d",&numframe)) break;
            
            contpeople++;
            if (numframe > contframes) contframes = numframe;
            
            for(i=1;i<=numframe;i++)
            {
                fscanf(arq," (%d,%d,%d)",&coordX, &coordY, &frame);
                //printf( "(" "%d,%d,%d" ")",coordX, coordY, frame);
            }
            
        }
    }
    
    fclose(arq);
    
    arq = fopen(url, "rt");
    
    
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else{
        fscanf(arq,"[%d]",&temp);
        
        
        int p = 0;
        
        while(1){
            
            fscanf(arq,"%d",&numframe);
            
            if(fscanf(arq,"%d",&numframe)) break;
            
            limits.push_back(numframe);
            
            //printf("Pessoa: %d\n", numframe);
            
            for(i=1;i<=numframe;i++)
            {
                fscanf(arq," (%d,%d,%d)",&coordX, &coordY, &frame);
                abc[p][i-1].x = coordX;
                abc[p][i-1].y = coordY;
                abc[p][i-1].f = frame;
                //printf("X: %d,Y: %d, Frame: %d\n", abc[p][i-1].x, abc[p][i-1].y, abc[p][i-1].f);
            }
            
            if(p <= contpeople) p++;
        }
    }
    
    fclose(arq);
    
    glutInit(&argc,argv);
    
    // Define do modo de operaÁ„o da GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    
    // Especifica o tamanho inicial em pixels da janela GLUT
    glutInitWindowSize(1200,1200);
    
    // Cria a janela passando como argumento o tÌtulo da mesma
    glutCreateWindow("Trajetórias");
    
    // Registra a funÁ„o callback de redesenho da janela de visualizaÁ„o
    glutDisplayFunc(Desenha);
    
    // Registra a funÁ„o callback para tratamento das teclas ASCII
    glutKeyboardFunc (Teclado);
    
    // Chama a funÁ„o respons·vel por fazer as inicializaÁıes
    Inicializa();
    
    // Inicia o processamento e aguarda interaÁıes do usu·rio
    glutMainLoop();
    
    return 0;
    
    
}
