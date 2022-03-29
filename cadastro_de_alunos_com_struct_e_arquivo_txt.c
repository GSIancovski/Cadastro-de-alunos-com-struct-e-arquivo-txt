#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{  //definindo tipo da struct DADOS
    char nome[30];
    int matricula;
}DADOS;
DADOS dados[10];  //vetor dados que receber� valores do tipo DADOS da struct

typedef struct{  //uma nova struct como forma de auxiliar, na hora de organizar os dados
    char nome[30];
    int matricula;
}AUX;
AUX aux[1];  //vetor apenas com uma posi��o, que j� ser� o necess�rio

int main(void){  //programa principal

    FILE *p;  //ponteiro - aponta para tipos de dado FILE

    int opc,cont=0,i=0,k=0,j=0,matricula,teste=0,busca,achei;  //vari�veis do programa

    p = fopen("dados.txt", "r");  //ponteiro - abre o arquivo "dados.txt" em modo leitura pelo caracter "r"

    if(p==NULL){  //teste para saber se o arquivo existe dentro do diret�rio que o proprio arquivo em C est�
        printf("Erro ao acessar arquivo!");
        return 0;  //fim do programa
    }else{
        fscanf(p,"%d - ALUNOS CADASTRADOS\n\n",&cont);  //busca de dentro do arquivo a quantidade de alunos cadastrados para usar como indice
        if(cont!=0){  //caso a variavel cont n�o for zero ent�o ele realiza a implementa��o de dados
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

        switch(opc){  //possiveis a��es cada op��o de menu
        case 1:  //caso op��o seja 1 - Inserir

            p = fopen("dados.txt", "w"); //abre o arquivo em modo escrita pelo caracter "w"
                                         //se o arquivo n�o existir ele ser� criado, caso exista ser� apagado todo o conteudo
                                         //por�m j� foi carregado todo conteudo dele no come�o do programa

            do{  // repeti��o caso o usu�rio queira cadastrar outro aluno
                do{  //repeti��o para erro ao digitar matr�cula

                    k=0;  //variavel "auxiliar" para realizar repeti��es sem mudar o indice que � a variavel i
                    teste=0; // variavel para saber se j� existe a matricula no programa
                    system("cls");
                    printf("\n------INSERIR ALUNO------\n\n");

                    fflush(stdin);  //comando usando para limpar o buffer
                    printf("\n > Matricula: ");
                    scanf("%d",&matricula);  //salvando primeiro em uma variavel para passar pelos testes

                    if(matricula<=0 || matricula>9999999){  //teste b�sico para valores inv�lidos
                        printf("\nValor invalido!");
                        getch(); //espera o usuario apertar qualquer tecla para prosseguir
                        continue; //realiza de novo a repeti��o do erro ao digitar matricula
                    }

                    for(k=0;k<cont;k++){  //teste para ver se matricula ja foi cadastrada
                        if(matricula==dados[k].matricula){
                            matricula=-1;  //caso esta linha seja executada matricula passa a receber um valor simbolico
                            break;  //fim do la�o for
                        }
                    }

                    if(matricula==-1){  //caso receba o valor simbolico � porque j� existe no programa a mtricula digitada
                        printf("\n\n [i] Matricula ja cadastrada, tente novamente!");
                        getch();
                        continue; //realiza de novo a repeti��o do erro ao digitar matricula
                    }

                }while(matricula<=0 || matricula>9999999);  //condi��o para o la�o continuar

                dados[i].matricula=matricula; //se a matr�cula passar pelos testes ela ser� atribuida para tal indice de aluno

                fflush(stdin); //comando para limpar o buffer
                printf("\n > Nome:");
                gets(&dados[i].nome); //utilizando comando "gets" pois facilita entrada de nomes inteiros

                cont++; //variavel para saber a quantidade de alunos cadastrados
                i++; //indice incrementa 1 para a pr�xima posi��o do vetor

                printf("\n\nCadastrar outro aluno?(s/n)\n");

            }while(getch()=='s'); //condi��o para o la�o continuar

            for(k=0;k<cont;k++){ //caso tudo seja aceito ser� feito uma organiza��o no vetor passando
                                 //os valores inseridos para suas devidas posi��es, utilizando nossa struct auxiliar

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

        case 2:  //caso op��o seja 2 - pesquisar

            teste=0; //zera a varialvel toda vez que entrar para op��o de pesquisar

            system("cls");
            printf("\n------PESQUISAR POR ALUNO------\n\n");
            printf("\nDigite a matricula:");
            scanf("%d",&busca);

            if((busca<=0 || busca>9999999) || cont==0){  //novamente teste para numeros inv�lidos
                    printf("\n\nValor invalido!");
                    getch();
                    continue;
            }

            //realizando uma busca bin�ria

            int begin = 0;
            int end = cont - 1; //receber� o valor da quantidade total de registros -1 para fazer o la�o

            while (begin <= end){  //condi��o para continuar o la�o

                k = (begin + end) / 2;  //calcula o meio do sub-vetor

                if (dados[k].matricula == busca) {  //caso condi��o seja executada o item foi encontrado
                    achei=k;
                    break; //para o la�o
                }

                if (dados[k].matricula < busca) {  //item est� no sub-vetor da direita
                    begin = k + 1;
                } else {  //dados[k].matricula > busca. //Item est� no sub-vetor � esquerda
                    end = k;
                }

                if((begin==cont) || (end==0)){  //condi��o de parada para o la�o
                    teste=-1;  //caso execute esta linha o teste dar� que n�o existe cadastro
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

        case 3:  //caso op��o seja 3 - Pesquisar

            if(cont!=0){  //teste para saber se existe cadastros

                printf("\nMatricula | Nome\n");

                for(k=0;k<cont;k++){  //lista todos os cadastros
                    printf("\n\n %d     |",dados[k].matricula);
                    printf("    %s",dados[k].nome);
                    printf("\n\n_____________________________");
                }

            }else  //caso cont seja zero n�o existe nenhum cadastro
                printf("\nNADA CADASTRADO!");

            getch();
            break;  //fim case 3

        case 4:  //caso op��o seja 4 - SAIR

            continue;  //simplesmente continua o programa e retorna o valor 0

        default:  //para todas op��es diferentes
            printf("Opcao invalida!");
            getch();
            break;
        }
    }while(opc!=4);

    return 0;  //fim programa
}
