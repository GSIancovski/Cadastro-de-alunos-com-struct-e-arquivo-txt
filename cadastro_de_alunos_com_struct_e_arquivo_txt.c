#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{  //definindo tipo da struct DADOS
    char nome[30];
    int matricula;
}DADOS;
DADOS dados[10];  //vetor dados que receberá valores do tipo DADOS da struct

typedef struct{  //uma nova struct como forma de auxiliar, na hora de organizar os dados
    char nome[30];
    int matricula;
}AUX;
AUX aux[1];  //vetor apenas com uma posição, que já será o necessário

int main(void){  //programa principal

    FILE *p;  //ponteiro - aponta para tipos de dado FILE

    int opc,cont=0,i=0,k=0,j=0,matricula,teste=0,busca,achei;  //variáveis do programa

    p = fopen("dados.txt", "r");  //ponteiro - abre o arquivo "dados.txt" em modo leitura pelo caracter "r"

    if(p==NULL){  //teste para saber se o arquivo existe dentro do diretório que o proprio arquivo em C está
        printf("Erro ao acessar arquivo!");
        return 0;  //fim do programa
    }else{
        fscanf(p,"%d - ALUNOS CADASTRADOS\n\n",&cont);  //busca de dentro do arquivo a quantidade de alunos cadastrados para usar como indice
        if(cont!=0){  //caso a variavel cont não for zero então ele realiza a implementação de dados
            for(i=0;i<cont;i++){
                fscanf(p,"%d - %s\n",&dados[i].matricula,&dados[i].nome);//carrega os dados para dentro do programa novamente
            }
        }
    }
    fclose(p); //fecha o aquivo

    do{  //menu do programa
        system("cls");
        printf("\n------CADASTRO DE ALUNOS------\n");
        printf("\n 1 - Inserir");
        printf("\n 2 - Pesquisar");
        printf("\n 3 - Listar");
        printf("\n 4 - SAIR\n\n");

        printf("Opcao: ");  //pedindo instrucao no menu
        scanf("%d", &opc);  //lendo a instrucao solicitada

        switch(opc){  //possiveis ações cada opção de menu
        case 1:  //caso opção seja 1 - Inserir

            p = fopen("dados.txt", "w"); //abre o arquivo em modo escrita pelo caracter "w"
                                         //se o arquivo não existir ele será criado, caso exista será apagado todo o conteudo
                                         //porém já foi carregado todo conteudo dele no começo do programa

            do{  // repetição caso o usuário queira cadastrar outro aluno
                do{  //repetição para erro ao digitar matrícula

                    k=0;  //variavel "auxiliar" para realizar repetições sem mudar o indice que é a variavel i
                    teste=0; // variavel para saber se já existe a matricula no programa
                    system("cls");
                    printf("\n------INSERIR ALUNO------\n\n");

                    fflush(stdin);  //comando usando para limpar o buffer
                    printf("\n > Matricula: ");
                    scanf("%d",&matricula);  //salvando primeiro em uma variavel para passar pelos testes

                    if(matricula<=0 || matricula>9999999){  //teste básico para valores inválidos
                        printf("\nValor invalido!");
                        getch(); //espera o usuario apertar qualquer tecla para prosseguir
                        continue; //realiza de novo a repetição do erro ao digitar matricula
                    }

                    for(k=0;k<cont;k++){  //teste para ver se matricula ja foi cadastrada
                        if(matricula==dados[k].matricula){
                            matricula=-1;  //caso esta linha seja executada matricula passa a receber um valor simbolico
                            break;  //fim do laço for
                        }
                    }

                    if(matricula==-1){  //caso receba o valor simbolico é porque já existe no programa a mtricula digitada
                        printf("\n\n [i] Matricula ja cadastrada, tente novamente!");
                        getch();
                        continue; //realiza de novo a repetição do erro ao digitar matricula
                    }

                }while(matricula<=0 || matricula>9999999);  //condição para o laço continuar

                dados[i].matricula=matricula; //se a matrícula passar pelos testes ela será atribuida para tal indice de aluno

                fflush(stdin); //comando para limpar o buffer
                printf("\n > Nome:");
                gets(&dados[i].nome); //utilizando comando "gets" pois facilita entrada de nomes inteiros

                cont++; //variavel para saber a quantidade de alunos cadastrados
                i++; //indice incrementa 1 para a próxima posição do vetor

                printf("\n\nCadastrar outro aluno?(s/n)\n");

            }while(getch()=='s'); //condição para o laço continuar

            for(k=0;k<cont;k++){ //caso tudo seja aceito será feito uma organização no vetor passando
                                 //os valores inseridos para suas devidas posições, utilizando nossa struct auxiliar

                for(j=0;j<cont;j++){
                    if(dados[j].matricula>dados[k].matricula){

                        strcpy(aux[0].nome, dados[k].nome);
                        aux[0].matricula=dados[k].matricula;

                        strcpy(dados[k].nome, dados[j].nome);
                        dados[k].matricula=dados[j].matricula;

                        strcpy(dados[j].nome, aux[0].nome);
                        dados[j].matricula=aux[0].matricula;

                    }
                }
            }

            fprintf(p,"%d - ALUNOS CADASTRADOS\n\n",cont); //comando para escrever no arquivo de texto a quantidade de alunos cadastrados

            for(k=0;k<cont;k++){
                fprintf(p,"%d - %s\n",dados[k].matricula,dados[k].nome); //comando para escrever dentro do arquivo de texto, os alunos cadastrados
            }

            fclose(p);  //fecha o arquivo e assim salvando-o
            break; //fim do case 1

        case 2:  //caso opção seja 2 - pesquisar

            teste=0; //zera a varialvel toda vez que entrar para opção de pesquisar

            system("cls");
            printf("\n------PESQUISAR POR ALUNO------\n\n");
            printf("\nDigite a matricula:");
            scanf("%d",&busca);

            if((busca<=0 || busca>9999999) || cont==0){  //novamente teste para numeros inválidos
                    printf("\n\nValor invalido!");
                    getch();
                    continue;
            }

            //realizando uma busca binária

            int begin = 0;
            int end = cont - 1; //receberá o valor da quantidade total de registros -1 para fazer o laço

            while (begin <= end){  //condição para continuar o laço

                k = (begin + end) / 2;  //calcula o meio do sub-vetor

                if (dados[k].matricula == busca) {  //caso condição seja executada o item foi encontrado
                    achei=k;
                    break; //para o laço
                }

                if (dados[k].matricula < busca) {  //item está no sub-vetor da direita
                    begin = k + 1;
                } else {  //dados[k].matricula > busca. //Item está no sub-vetor à esquerda
                    end = k;
                }

                if((begin==cont) || (end==0)){  //condição de parada para o laço
                    teste=-1;  //caso execute esta linha o teste dará que não existe cadastro
                    break;
                }
            }

            if(teste==-1){  //teste para saber se a matricula ja foi cadastrada
                printf("\n\nNao existe cadastro com esta matricula!");
                getch();
                break;
            }else{  //caso encontrar a matricula procurada, ele lista o nome e a matricula
                printf("\n\nMatricula | Nome\n\n");
                printf("%d - %s\n",dados[achei].matricula,dados[achei].nome);
                getch();
            }

            break;  //fim do case 2

        case 3:  //caso opção seja 3 - Pesquisar

            if(cont!=0){  //teste para saber se existe cadastros

                printf("\nMatricula | Nome\n");

                for(k=0;k<cont;k++){  //lista todos os cadastros
                    printf("\n\n %d     |",dados[k].matricula);
                    printf("    %s",dados[k].nome);
                    printf("\n\n_____________________________");
                }

            }else  //caso cont seja zero não existe nenhum cadastro
                printf("\nNADA CADASTRADO!");

            getch();
            break;  //fim case 3

        case 4:  //caso opção seja 4 - SAIR

            continue;  //simplesmente continua o programa e retorna o valor 0

        default:  //para todas opções diferentes
            printf("Opcao invalida!");
            getch();
            break;
        }
    }while(opc!=4);

    return 0;  //fim programa
}
