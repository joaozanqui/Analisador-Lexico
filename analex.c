/*	
	TRABALHO I - Compiladores
	João Pedro de Freitas Zanqui
	Sistema operacional: Windows 10
	Compilador: Dev-C++
*/

#include <stdio.h>
#include <string.h>

#define MAX 30

char simbolo[MAX];

void PROXIMO(char *proximo, int *linha, int *posCodigo, char codigo[], int *tab)
{

    if (*posCodigo >= strlen(codigo))
    {
        *proximo = NULL;
        return;
    }

    *proximo = codigo[*posCodigo];
    *posCodigo = *posCodigo + 1;

    while (*proximo == '\t')
    {
        *proximo = codigo[*posCodigo];
        *posCodigo = *posCodigo + 1;
        *tab = *tab + 1;
    }

    // printf("linha: %d, outraLinha: %d, proximo: %c, posCodigo: %d, strlen(codigo): %d\n", *linha, *outraLinha, *proximo, *posCodigo, strlen(codigo));
}

char *CODIGO(char atomo[])
{
    // : = + * / - , . ; < > ( )
    // program var integer procedure begin if else then div end read while write do
    char codigo[MAX];

    if (strcmp(atomo, ":") == 0)
        strcpy(codigo, "i_doisPontos");
    else if (strcmp(atomo, "=") == 0)
        strcpy(codigo, "i_igual");
    else if (strcmp(atomo, ":=") == 0)
        strcpy(codigo, "i_atribuicao");
    else if (strcmp(atomo, "+") == 0)
        strcpy(codigo, "i_soma");
    else if (strcmp(atomo, "*") == 0)
        strcpy(codigo, "i_multiplicacao");
    else if (strcmp(atomo, "/") == 0)
        strcpy(codigo, "i_divisao");
    else if (strcmp(atomo, "-") == 0)
        strcpy(codigo, "i_subtracao");
    else if (strcmp(atomo, ",") == 0)
        strcpy(codigo, "i_virgula");
    else if (strcmp(atomo, ".") == 0)
        strcpy(codigo, "i_ponto");
    else if (strcmp(atomo, ";") == 0)
        strcpy(codigo, "i_pontoEVirgula");
    else if (strcmp(atomo, "<") == 0)
        strcpy(codigo, "i_menor");
    else if (strcmp(atomo, ">") == 0)
        strcpy(codigo, "i_maior");
    else if (strcmp(atomo, "(") == 0)
        strcpy(codigo, "i_abreParenteses");
    else if (strcmp(atomo, ")") == 0)
        strcpy(codigo, "i_fechaParenteses");
    else if (strcmp(atomo, "program") == 0)
        strcpy(codigo, "i_program");
    else if (strcmp(atomo, "var") == 0)
        strcpy(codigo, "i_var");
    else if (strcmp(atomo, "integer") == 0)
        strcpy(codigo, "i_integer");
    else if (strcmp(atomo, "procedure") == 0)
        strcpy(codigo, "i_procedure");
    else if (strcmp(atomo, "begin") == 0)
        strcpy(codigo, "i_begin");
    else if (strcmp(atomo, "if") == 0)
        strcpy(codigo, "i_if");
    else if (strcmp(atomo, "else") == 0)
        strcpy(codigo, "i_else");
    else if (strcmp(atomo, "then") == 0)
        strcpy(codigo, "i_then");
    else if (strcmp(atomo, "div") == 0)
        strcpy(codigo, "i_div");
    else if (strcmp(atomo, "end") == 0)
        strcpy(codigo, "i_end");
    else if (strcmp(atomo, "read") == 0)
        strcpy(codigo, "i_read");
    else if (strcmp(atomo, "while") == 0)
        strcpy(codigo, "i_while");
    else if (strcmp(atomo, "write") == 0)
        strcpy(codigo, "i_write");
    else if (strcmp(atomo, "do") == 0)
        strcpy(codigo, "i_do");

    return codigo;
}

void ERRO(int linha, char atomo[], char proximo, int opc)
{
    printf("\n\nERRO na linha %d - ", linha);
    if (opc == 1)
        printf("Variavel iniciada com digito: %s\n", atomo);
    else
        printf("Simbolo desconhecido: %c\n", proximo);
}

int simbolosEspeciais(char caracter)
{
    char caracteres[] = {':', '=', '+', '*', '/', '-', ',', '.', ';', '<', '>', '(', ')'};
    int i;

    for (i = 0; i < (int)(sizeof(caracteres) / sizeof(caracteres[0])); i++)
        if (caracter == caracteres[i])
            return 1;

    return 0;
}

int palavrasReservadas(char palavra[])
{
    char palavras[][MAX] = {"program", "var", "integer", "procedure", "begin", "if", "else", "then", "div", "end", "read", "while", "write", "do"};
    int i;

    for (i = 0; i < (int)(sizeof(palavras) / sizeof(palavras[0])); i++)
        if (strcmp(palavra, palavras[i]) == 0)
            return 1;
    return 0;
}

int letras(char letra)
{
    // 65 - 90 , 97 - 122
    int letraInt = (int)letra;
    if ((letraInt >= 65 && letraInt <= 90) || (letraInt >= 97 && letraInt <= 122))
        return 1;
    else
        return 0;
}

int digitos(char digito)
{
    // 48 - 57
    int digitoInt = (int)digito;
    if (digitoInt >= 48 && digitoInt <= 57)
        return 1;
    else
        return 0;
}

void mostraSimbolos(int linha, int *outraLinha, int tab)
{
    if (*outraLinha)
    {
        if (linha != 1)
            printf("\n");
        printf("%d ", linha);
        *outraLinha = 0;
        while (tab--)
            printf("\t");
    }
    printf("%s ", simbolo);
}

int main()
{
    char atomo[MAX] = {""};
    char proximo = NULL, proximoString[2];
    int linha = 1, outraLinha = 1, i, tab = 0;

    FILE *arquivo;
    char codigo[500];
    int posCodigo = 0;

    for (i = 0; i < 500; i++)
        codigo[i] = NULL;

    arquivo = fopen("Trab1_Compiladores.txt", "r");
    fread(codigo, sizeof(char), 500, arquivo);
    fclose(arquivo);

    while (proximo == NULL)
        PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);

    while (proximo != NULL)
    {
        for (i = 0; i < strlen(atomo); i++)
            atomo[i] = NULL;

        if (simbolosEspeciais(proximo))
        {
            char s[3];
            s[0] = proximo;
            s[1] = s[2] = NULL;
            PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);

            if (s[0] == ':' && proximo == '=')
            {
                s[1] = proximo;
                PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);
            }
            strcpy(simbolo, CODIGO(s));

            while (proximo == ' ')
                PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);
        }
        else if (letras(proximo))
        {
            do
            {
                proximoString[0] = proximo; // Transforma o caractere proximo em string p/ passar como referencia
                proximoString[1] = NULL;
                strcat(atomo, proximoString);
                PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);
                if (proximo == ' ')
                {
                    while (proximo == ' ')
                        PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);
                    break;
                }
            } while (letras(proximo) || digitos(proximo));

            if (palavrasReservadas(atomo))
                strcpy(simbolo, CODIGO(atomo));
            else
                strcpy(simbolo, "i_identificador");
        }

        else if (digitos(proximo))
        {
            do
            {
                proximoString[0] = proximo; // Transforma o proximo caractere em string p/ passar como referencia
                proximoString[1] = NULL;
                strcat(atomo, proximoString);
                PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);
                if (proximo == ' ')
                {
                    while (proximo == ' ')
                        PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);
                    break;
                }
            } while (digitos(proximo));

            if (letras(proximo))
            {
                while (proximo!=NULL && !simbolosEspeciais(proximo) && proximo != ' ' && proximo != '\n')
                {
                    proximoString[0] = proximo; // Transforma o proximo caractere em string p/ passar como referencia
                    proximoString[1] = NULL;
                    strcat(atomo, proximoString);
                    PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);
                }
                ERRO(linha, atomo, proximo, 1);
                return 0;
            }

            strcpy(simbolo, "i_numero");
        }

        else
        {
            ERRO(linha, atomo, proximo, 2);
            return 0;
        }
        // printf("%s", simbolo);
        mostraSimbolos(linha, &outraLinha, tab);

        if (proximo == '\n')
        {
            tab = 0;
            PROXIMO(&proximo, &linha, &posCodigo, codigo, &tab);
            linha++;
            outraLinha = 1;
        }
    }

    return 0;
}
