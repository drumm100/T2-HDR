#include <math.h>
#include <string.h>		// para usar strings

// Rotinas para acesso da OpenGL
#include "opengl.h"

// Variáveis globais a serem utilizadas:

// Dimensões da imagem de entrada
int sizeX, sizeY;

// Imagem de entrada
unsigned char* image;

// Imagem de saída
unsigned char* image8;

// Fator de exposição inicial
float exposure = 1.0;

// Função principal de processamento: ela deve chamar outras funções
// quando for necessário (ex: algoritmo de tone mapping, etc)
void process()
{
    printf("Exposure: %.3f\n", exposure);
    //
    // EXEMPLO: preenche a imagem com pixels cor de laranja...
    //
    //
    // SUBSTITUA este código pelos algoritmos a serem implementados
    //
    unsigned char* ptrEntrada = image;
    unsigned char* ptrSaida = image8;

    //int pos = 0;
    //for(pos = 0; pos<sizeX*sizeY*3; pos+=3) {
     //   *ptr++ = (unsigned char) (255 * exposure);
      //  *ptr++ = (unsigned char) (127 * exposure);
       // *ptr++ = (unsigned char) (0 * exposure);
    //}

    //
    // NÃO ALTERAR A PARTIR DAQUI!!!!
    //
    buildTex();
}


// ------------Para criar Cabeçalho-------------
unsigned long ObtemTamanhoDoArquivo(FILE* f)
{
    fseek(f, 0, SEEK_END);
    unsigned long len = (unsigned long)ftell(f);
    fseek(f, SEEK_SET, 0);
    return len;
}

void LeArquivo(FILE* f, unsigned char* ptr, unsigned long TamanhoEsperado)
{
    unsigned long NroDeBytesLidos;
    NroDeBytesLidos = fread(ptr, sizeof(unsigned char), TamanhoEsperado, f);

    if(NroDeBytesLidos != TamanhoEsperado) { // verifica se a leitura funcionou
    printf("Erro na Leitura do arquivo!\n");
    printf("Nro de bytes lidos: %ld", NroDeBytesLidos);
    exit(1);
    } else
    printf("Leitura realizada com sucesso!\n");
}

unsigned char* LeImagemDeEntrada(char *nomeEntrada, unsigned long *tamEntrada)
{
    FILE* arq;
    // Tenta abrir o arquivo
    arq = fopen(nomeEntrada, "rb");
    if(arq == NULL) {
    printf("Arquivo %s não existe.\n", nomeEntrada);
    exit(1);
    }
    *tamEntrada = ObtemTamanhoDoArquivo(arq);
    printf("O tamanho do arquivo %s é %ld bytes.\n", nomeEntrada, *tamEntrada);

    // Aloca memória para ler todos os bytes do arquivo
    image = (unsigned char*)malloc(sizeof(unsigned char) * *tamEntrada);
    if(image == NULL) { // Testa se conseguiu alocar
    printf("Erro na alocação da memória!\n");
    exit(1);
    }
    LeArquivo(arq, image, *tamEntrada);
    fclose(arq); // fecha o arquivo
    return image; //Ponteiro para o primeiro pixel[ID]
}
//--------------------------------------------------------





//-------------Main------------------------------------
int main(int argc, char** argv)
{
    if(argc==1) {
        printf("hdrvis [image file.hdf]\n");
        exit(1);
    }

    // Inicialização da janela gráfica
    init(argc,argv);

    //
    // INCLUA aqui o código para LER a imagem de entrada
    //
    // Siga as orientações no enunciado para:
    //
    // 1. Descobrir o tamanho da imagem (ler header)
    // 2. Ler os pixels
    //
	unsigned long TamanhoDoArquivo;
    unsigned char* Dados;
    Dados = LeImagemDeEntrada(argv[1], &TamanhoDoArquivo);

	//printf("Teste: %d", *Dados);

	unsigned char* largura =  (int*)(Dados + 3);
	unsigned char* altura =  (int*)(Dados + 4);

    // TESTE: cria uma imagem de 800x600

    sizeX = 800;
    sizeY = 600;

    printf("%d x %d\n", *largura, *altura);

    // Aloca imagem de entrada (32 bits RGBE)
    //image = (unsigned char*) malloc(sizeof(unsigned char) * sizeX * sizeY * 4);

    // Aloca memória para imagem de saída (24 bits RGB)
    image8 = (unsigned char*) malloc(sizeof(unsigned char) * sizeX * sizeY * 3);

    exposure = 1.0f; // exposição inicial

    // Aplica processamento inicial
    process();

    // Não retorna... a partir daqui, interação via teclado e mouse apenas, na janela gráfica
    glutMainLoop();
    return 0;
}




//PRECISO pegar altura e largura, e depois pular 11 posições para começar a ler o arquivo


