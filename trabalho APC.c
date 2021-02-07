#include <stdio.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TAM_E 4     // definindo o tamanho da string que vai ler o estado
#define TAM_C 100 // Tamanho da string do nome da cidade
#define TAM_MAX 100 // tamanho da string do nome da pessoa
#define TAM_DATA 20 // tamanho da string da data de nascimento

int idade_atual(char Dnascimento[]); // função que retorna a idade

int validar_data(char data[]); // funçãp para conferir se a data é válida


typedef struct
{
char nome[TAM_MAX];
char sexo;
char Dnascimento[TAM_DATA];
char cidadeEstado[TAM_C];
}PESSOA;
int main ()
{
     setlocale(LC_ALL, "portuguese");
    system("color F0");
    char x; // Variável para ser usada no menu de opções
    //uso de um do..while para retornar ao menu após os procedimentos

    do{
            fflush(stdin);
            system("cls");
        printf("                                       ********** Menu de opções:**********\n");
        printf("                                       * 1)Cadastrar Estado               *\n");
        printf("                                       * 2)Cadastrar Cidade               *\n");
        printf("                                       * 3)Cadastrar Pessoa               *\n");
        printf("                                       * 4)Listar pessoas por Estado      *\n");
        printf("                                       * 5)Listar pessoas por Cidade      *\n");
        printf("                                       * 6)Consultar pessoa por nome      *\n");
        printf("                                       * 7)Gerar relatório demográfico    *\n");
        printf("                                       * 8)Finalizar programa             *\n");
        printf("                                       ************************************\n");

            // switch para a escolha do procedimento
        printf("\n Digite qual operação deseja fazer: ");
        scanf("%c", &x);

        switch(x)
        {
            case '1' :
                system("cls");
                cadastrarEstado();
                break;
            case '2' :
                system("cls");
                cadastrarCidade();
                break;
            case '3' :
                system("cls");
                cadastrarPessoa();
                break;
            case '4' :
                system("cls");
                listarPessoaPorEstado();
                break;
            case '5' :
                system("cls");
                listarPessoaPorCidade();
                break;
            case '6' :
                system("cls");
                pesquisarPessoaPorNome();
                break;
            case '7':
                system("cls");
                relatorioDemografico();
                break;
            case '8' :
                system("cls");
                printf("--------------------------------\n");
                printf("             THE END\n");
                printf("--------------------------------\n");
                system("pause");
            break;
            default:
                printf("\nopção inválida\n");
                system("pause");
        }
    }while(x != '8');
return 0;
}

void cadastrarEstado() // cadastrando o nome do estado e jogando no arquivo
{
    char estado[TAM_E];
    int i;
    FILE *arquivoEstado;
    int estado_existente = 0; // variável para auxiliar na lógica, se o estado já foi cadastrado ele vai para 1
    char estado_arquivo[TAM_E]; // variável para armazenar os dados vindos do arquivo

    printf("Digite a sigla do Estado que deseja cadastrar: \n");
    arquivoEstado = fopen("estado.txt", "a"); // para criar o arquivo se não existir
    fflush(stdin);
    fgets(estado, TAM_E, stdin);

    for (i=0 ; i < strlen(estado); i++)
    {
        estado[i] = toupper(estado[i]); /*para padronizar a escrita do estado no arquivo e o msm estado não ser cadastrado duas vezes
                                        só que escritos de formas diferentes*/
    }

    arquivoEstado = fopen("estado.txt", "r" ); // abrindo o arquivo para ler e verificar se o estado já foi cadastrado
        while(!feof(arquivoEstado)){ //while para verificar se o estado já foi cadastrado
                if(!feof(arquivoEstado)){
                    fgets(estado_arquivo,TAM_E,arquivoEstado);
                    if(strcmp(estado, estado_arquivo)==0){

                    estado_existente++;
                    }
                }
        }

        fclose(arquivoEstado);

        if(estado_existente==0){  // se o estado não existir no arquivo ele não foi cadastrado
            arquivoEstado = fopen("estado.txt", "a");
            fprintf(arquivoEstado, "%s", estado);
            printf("Estado cadastrado com sucesso!\n");
            system("pause");
        }else{
            printf("Estado já cadastrado\n");
            system("pause");
        }
        fclose(arquivoEstado);
}
void cadastrarCidade()
{
    FILE *arquivoCidade;
    FILE *arquivoEstado;
    int i;
    char estado_cidade[TAM_E]; //string para armazenar o estado da cidade
    char verificar_estado[TAM_E]; // string para armazenar os dados do arquivo estado
    char cidade[TAM_C]; //string para armazenar o nome da cidade
    int ct_estado; //contador para contar quantas vezes ele entrou no if
    char verificar_cidade[TAM_C];
    char *verificar_estado_cidade;
    char *verificarCidade;
    int cidade_existente = 0 ;

    printf("Digite a sigla do estado da Cidade cadastrada:\n");
    fflush(stdin);
    fgets(estado_cidade, TAM_E, stdin);
    arquivoEstado = fopen("estado.txt", "a");

    for(i=0; i<strlen(estado_cidade); i++)
    {
        estado_cidade[i] = toupper(estado_cidade[i]);
    }
    arquivoEstado = fopen("estado.txt", "r");
    ct_estado=0;

    while(!feof(arquivoEstado)) // while para importar do arquivo de estados e verificar se o estado da cidade já esta cadastrado
    {
        fgets(verificar_estado, TAM_E, arquivoEstado);
        if(!feof(arquivoEstado))    //if para não fazer o ultimo estado duas vezes
        {
            if(strcmp(verificar_estado, estado_cidade)==0 )
            {
                ct_estado = 1;
                printf("Digite o nome da Cidade:\n");
                fflush(stdin);                          // escrevendo o nome da cidade já, pois o estado já está cadastrado
                fgets(cidade, TAM_C, stdin );
                cidade[strlen(cidade)-1] = '\0';
                for(i=0; i<strlen(cidade); i++){
                    cidade[i] = tolower(cidade[i]);

                }
            }
        }
    }

    fclose(arquivoEstado);

    if(ct_estado == 0){
            printf("Não é possível cadastrar uma cidade sem cadastrar seu estado antes\n"); //se o contador for igual a zero, não armazenará a cidade e escreverá a seguinte mensagem
            system("pause");
        }

        arquivoCidade = fopen("cidade.txt", "a"); // para criar o arquivo se ele não existir

        if(ct_estado == 1){
            arquivoCidade = fopen("cidade.txt", "r");
                // while para verificar se a cidade já foi cadastrada
                while(!feof(arquivoCidade)){
                        if(fgets(verificar_cidade, TAM_C, arquivoCidade) != NULL){  // if para ultima linha do arquivo não seja verificada 2 vezes
                                fgets(verificar_cidade, TAM_C, arquivoCidade);
                                verificarCidade = strtok(verificar_cidade, "/"); // strtok para armazenar o nome da cidade no arquivo
                                verificar_estado_cidade = strtok(NULL, ""); // para pegar o resto da string, que no caso é o estado da cidade
                                // if para verificar se a cidade já existe(com mesmo nome e estado)
                            if(strcmp(verificarCidade, cidade)==0 && strcmp(verificar_estado_cidade, estado_cidade)==0){
                                    cidade_existente = 1;
                                    break;

                            }
                        }
                }
        }
            if(cidade_existente == 0 && ct_estado == 1){
                    arquivoCidade = fopen("cidade.txt", "a");
                    fprintf(arquivoCidade, "//\n%s/%s", cidade, estado_cidade);
                    printf("Cidade cadastrada com sucesso!\n");
                    system("pause");

                }
        fclose(arquivoCidade);
                if(cidade_existente != 0){
                        printf("Cidade já cadastrada\n");
                        system("pause");
                    }


}
void cadastrarPessoa()
{

    PESSOA individuo;
    char cidadeArquivo[TAM_C]; // variável para receber a cidade do arquivo e verificar se ela foi cadastrada
    FILE *arquivoCidade;
    FILE *arquivoPessoa;
    int i;
    int cidadeCadastrada = 0;
    int sexo_valido = 0;
    int data_valida=0;

    printf("Digite a cidade e o estado onde a pessoa reside no formato cidade/sigla do estado\nEX: brasilia/df\n");
    fflush(stdin);
    fgets(individuo.cidadeEstado, TAM_C, stdin);

    for(i = strlen(individuo.cidadeEstado)-3; i < strlen(individuo.cidadeEstado); i++){
        individuo.cidadeEstado[i] = toupper(individuo.cidadeEstado[i]);
    }
    for(i=0; i< strlen(individuo.cidadeEstado)-3; i++){
        individuo.cidadeEstado[i] = tolower(individuo.cidadeEstado[i]);
    }
    arquivoCidade = fopen("cidade.txt", "a"); //para criar o arquivo caso ele não exista
    arquivoCidade = fopen("cidade.txt", "r");
    while(!feof(arquivoCidade)){ // while para verificar se a cidade da pessoa já está cadastrada
           fgets(cidadeArquivo, TAM_C, arquivoCidade);
           if(!feof(arquivoCidade)){

                if(strcmp(cidadeArquivo,individuo.cidadeEstado)==0){
                    cidadeCadastrada = 1;
                }
            }
    }
    fclose(arquivoCidade);
    if(cidadeCadastrada == 0){
        printf("A cidade em que essa pessoa reside não está cadastrada\n");
        system("pause");

    }

            arquivoPessoa = fopen("pessoa.txt", "a+b"); // cria o arquivo caso ele não exista
            arquivoPessoa = fopen("pessoa.txt", "r+b");
    if(cidadeCadastrada == 1){
            printf("Digite o nome da pessoa:\n");
            fflush(stdin);
            fgets(individuo.nome, TAM_MAX, stdin);
                for(i=0; i<strlen(individuo.nome); i++){
                    individuo.nome[i]= toupper(individuo.nome[i]);
                }
            system("cls");
            while(sexo_valido != 1){ // while para retornar à leitura do sexo caso a pessoa escolha um caracter inválido
                     printf("Digite o sexo da pessoa(m se for homem e f se for mulher):\n");
                    fflush(stdin);
                scanf("%c", &individuo.sexo);
                if(individuo.sexo == 'M' || individuo.sexo == 'm' || individuo.sexo == 'f' || individuo.sexo == 'F'){
                    sexo_valido = 1;
                }else{
                        printf("sexo inválido\n");
                         system("pause");
                }

                        system("cls");
            }

            while(data_valida != 1){ // while para retornar à leitura da data caso a data seja inválida
                system("cls");
                printf("Digite a data de nascimento da pessoa no formato DD/MM/AAAA:\n");
                fflush(stdin);
                fgets(individuo.Dnascimento, TAM_DATA, stdin);
                if(individuo.Dnascimento[2] == '/' && individuo.Dnascimento[5]=='/'){ // if para certificar que a pessoa digite a data no padrão desejado
                    data_valida = validar_data(individuo.Dnascimento); // função para retornar se a data é válida ou não
                }
                    if(data_valida==0){
                        printf("Data inválida\n");
                        system("pause");
                    }
            }


            system("cls");
            fseek(arquivoPessoa, 0, SEEK_END);
            fwrite(&individuo, sizeof(individuo), 1, arquivoPessoa);
            printf("pessoa cadastrada com sucesso!\n");
            getch();
            fclose(arquivoPessoa);

    }

}
void listarPessoaPorEstado()
{
PESSOA individuo;
char estado[TAM_E];
FILE *arquivoPessoa;
int pessoasCadastradas=0;
int i;


    arquivoPessoa = fopen("pessoa.txt", "r+b");
    if(arquivoPessoa){ // if para verificar se o arquivo existe

        printf("Digite a sigla do estado que pretende pesquisar:\n ");

        fflush(stdin);
        fgets(estado, TAM_E, stdin);
        system("cls");
        for(i=0; i<strlen(estado); i++ ){
            estado[i]= toupper(estado[i]); // deixando tudo maiusculo no padrão que foi usado para cadastrar
        }
        fseek(arquivoPessoa,0,SEEK_SET );

        while(!feof(arquivoPessoa)){
           fread(&individuo, sizeof individuo, 1, arquivoPessoa);
            if(!feof(arquivoPessoa)){ // if para tirar o bug de printar o último do arquivo duas vezes
                if(estado[1]==individuo.cidadeEstado[strlen(individuo.cidadeEstado)-2] && estado[0] == individuo.cidadeEstado[strlen(individuo.cidadeEstado)-3]){ //comparando a sigla que a pessoa digitou com as duas ultimos caracteres da string cidadeEstado, ja que esses caracteres guardam o estado
                    pessoasCadastradas =1; // vai para 1 se existir uma pessoa desse estado
                    printf("Nome: %s", individuo.nome);
                    printf("Cidade: %s", individuo.cidadeEstado);
                        if(individuo.sexo == 'M' || individuo.sexo == 'm'){
                            printf("Sexo: Masculino\n");
                        }else{
                            printf("Sexo: Feminino\n");
                        }
                        printf("Data de Nascimento: %s", individuo.Dnascimento);
                        printf("Idade: %d anos\n\n", idade_atual(individuo.Dnascimento));


                }
            }
        }
        fclose(arquivoPessoa);

        if(pessoasCadastradas==0){ // se ficar em 0 quer dizer que nenhuma pessoa desse estado foi cadastrado
            printf("Nenhuma pessoa desse estado foi cadastrada\n");
           system("pause");
        }
        system("pause");
    }else{ // se o arquivo não existir printará isso
            printf("Antes de pesquisar você deve cadastrar ao menos uma pessoa\n");
            system("pause");
        }

}
void listarPessoaPorCidade()
{

PESSOA individuo;
char cidade[TAM_C];
FILE *arquivoPessoa;
int pessoasCadastradas=0;
int i;

 arquivoPessoa = fopen("pessoa.txt", "r+b");

 if(arquivoPessoa){ // if para verificar se o arquivo existe
        printf("Digite a cidade e o estado que deseja pesquisar no formato cidade/sigla do estado\nEX: brasilia/df\n");
        fflush(stdin);
        fgets(cidade, TAM_C, stdin);
        system("cls");
        for(i= strlen(cidade)-3; i<strlen(cidade); i++){
            cidade[i]= toupper(cidade[i]);
        }
        for(i=0; i<strlen(cidade)-3; i++){
            cidade[i]= tolower(cidade[i]);
        }
        fseek(arquivoPessoa,0,SEEK_SET );
        printf("Cidade: %s\n\n", cidade);

        while(!feof(arquivoPessoa)){
            fread(&individuo, sizeof individuo, 1, arquivoPessoa);
            if(!feof(arquivoPessoa)){ // if para não repetir a última linha do arquivo duas vezes
                if(strcmp(cidade, individuo.cidadeEstado)==0){
                    pessoasCadastradas =1;
                    printf("Nome: %s", individuo.nome);
                    if(individuo.sexo == 'M' || individuo.sexo == 'm'){
                        printf("Sexo: Masculino\n");
                    }else{
                            printf("Sexo: Feminino\n");
                        }
                    printf("Data de Nascimento: %s", individuo.Dnascimento);
                    printf("Idade: %d anos\n\n", idade_atual(individuo.Dnascimento));

                }
            }
        }

        fclose(arquivoPessoa);

        if(pessoasCadastradas==0){
            printf("Nenhuma pessoa dessa cidade foi cadastrada\n");
        }
          system("pause");

    }else { // se o arquivo não existir printará isso
            printf("Antes de pesquisar você deve cadastrar ao menos uma pessoa\n");
            system("pause");
        }

}
void pesquisarPessoaPorNome()
{
    PESSOA individuo;
    char nome[TAM_MAX];
    FILE *arquivoPessoa;
    int pessoasCadastradas = 0;
    int i;

    printf("Digite o nome ou parte do nome da pessoa que deseja pesquisar:\n");
    fflush(stdin);
    fgets(nome,TAM_MAX,stdin);
    for(i=0; i<strlen(nome); i++){
        nome[i]= toupper(nome[i]);
    }
    nome[strlen(nome)-1]= '\0';
    system("cls");

    arquivoPessoa = fopen("pessoa.txt", "r+b");
    fseek(arquivoPessoa,0,SEEK_SET );

    if(arquivoPessoa){ // if para verificar se o arquivo existe
        while(!feof(arquivoPessoa)){
            fread(&individuo, sizeof individuo, 1, arquivoPessoa);
            if(!feof(arquivoPessoa)){
                if(strstr(individuo.nome,nome) != NULL){ // verificando se a string pesquisada aparece no nome da pessoa do arquivo
                     pessoasCadastradas = 1;
                    printf("Nome: %s", individuo.nome);
                    printf("Cidade: %s", individuo.cidadeEstado);
                    if(individuo.sexo == 'M' || individuo.sexo == 'm'){
                        printf("Sexo: Masculino\n");
                    }else{
                        printf("Sexo: Feminino\n");
                    }
                    printf("Data de Nascimento: %s", individuo.Dnascimento);
                    printf("Idade: %d anos\n\n", idade_atual(individuo.Dnascimento));

                }
            }
        }
        fclose(arquivoPessoa);
    if(pessoasCadastradas == 0){
        printf("Nenhuma pessoa possui esse nome\n");
    }
    system("pause\n");
    }else{ // se o arquivo não existir printará isso
        printf("Antes de pesquisar você deve cadastrar ao menos uma pessoa\n");
        system("pause");
    }
}
int idade_atual(char data[]){ //função que retorna a idade atual da pessoa
    struct tm *data_atual;
    char*diaS; // dia retirado da sring
    char *mesS; //mes retirado da strig
    char *anoS; // ano retirado da strig
    int dia_atual,mes_atual,ano_atual;
    time_t segundos;
    int idade;
        diaS = strtok(data,"/"); //separando a string da data em tres strings
        mesS = strtok(NULL, "/");
        anoS = strtok(NULL, "");
        //transformando em inteiro
        int dia = atoi(diaS);
        int mes = atoi(mesS);
        int ano = atoi(anoS);
        // funções para pegar a data atual do relógio
        time(&segundos);
        data_atual = localtime(&segundos);

        dia_atual = data_atual->tm_mday;
        mes_atual = data_atual->tm_mon+1;
        ano_atual = data_atual->tm_year+1900;

        // calculo da idade da pessoa
        idade = (ano_atual-1)-ano;

        if(mes_atual> mes){
            idade++;
        }
        if(mes_atual == mes && dia_atual >= dia){
            idade++;
        }


    return idade;
}
struct tm *data_atual;
int validar_data(char Dnascimento[]){
char*diaS; // dia retirado da sring
char *mesS; //mes retirado da strig
char *anoS; // ano retirado da strig
int data_valida;
char data[TAM_MAX]; // string para ser alterada pelo strtok
time_t segundos;
int dia_atual,mes_atual,ano_atual;
    strcpy(data, Dnascimento);
    diaS = strtok(data,"/");//separando a string da data em tres strings
    mesS = strtok(NULL, "/");
    anoS = strtok(NULL, "");
    //transformando em inteiro
    int dia = atoi(diaS);
    int mes = atoi(mesS);
    int ano = atoi(anoS);

    // funções para pegar a data atual do relógio
        time(&segundos);
        data_atual = localtime(&segundos);

        dia_atual = data_atual->tm_mday;
        mes_atual = data_atual->tm_mon+1;
        ano_atual = data_atual->tm_year+1900;

    if(ano <= ano_atual){ // para não deixar uma pessoa ser cadastrada no futuro
        if(mes >= 1 && mes <= 12){ // mes não pode ser maior que 12
            if(mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12 ){
                if(dia>=1 && dia <= 31){ // meses com 31 dias
                        data_valida=1;

                }else{
                    data_valida = 0;
                }
            }
                if(mes==4 || mes==6 || mes==9 || mes==11){ // meses com 30 dias
                    if(dia>=1 && dia <=30){
                        data_valida=1;
                    }else{
                        data_valida = 0;
                    }
                }
                if(ano %4==0 && ano% 100 != 0 || ano%400 ==0 ){ // ano bissexto
                    if(mes == 2){
                        if(dia>=1 && dia<= 29 ){
                            data_valida = 1;
                        }else{
                            data_valida = 0;
                        }
                    }
                }else{
                    if(mes == 2){ // fevereiro com 28 dias, quando o ano não for bissexto
                        if(dia >= 1 && dia <= 28){
                            data_valida=1;
                        }else{
                            data_valida =0;
                        }
                    }
                }
                    // para que a data de nascimento não seja no futuro
                    if(ano == ano_atual && mes > mes_atual)
                    {
                        data_valida = 0;
                    }
                    if(ano == ano_atual && mes == mes_atual && dia > dia_atual){
                        data_valida = 0;
                    }
        }else{
            data_valida = 0;
        }

    }else{
        data_valida = 0;
    }
   return data_valida;
}

void relatorioDemografico()
{
int ct_total=0; // contador total de pessoas
int ct_faixa_et_0_5=0, ct_faixa_et_6_10=0,ct_faixa_et_11_20=0;
int ct_faixa_et_21_40=0, ct_faixa_et_41_60=0, ct_faixa_et_60_=0; // contadores para fazer o cálculo do percentual
int ct_masculinos=0, ct_femininos=0;
float percentual_0_5, percentual_6_10, percentual_11_20, percentual_21_40, percentual_41_60, percentual_60_;
float percentual_masculinos, percentual_femininos;
int idade;
FILE *arquivoPessoa;
PESSOA individuo;

arquivoPessoa = fopen("pessoa.txt", "r+b");
    fseek(arquivoPessoa,0,SEEK_SET );
    // while para saber quantas pessoas existem, e quantas tem em cada faixa etária
    if(arquivoPessoa){
        while(!feof(arquivoPessoa)){
            fread(&individuo, sizeof individuo, 1, arquivoPessoa);
                if(!feof(arquivoPessoa)){
                    if(individuo.sexo == 'M'|| individuo.sexo == 'm'){
                        ct_masculinos++;
                    }else{
                        ct_femininos++;
                    }
                    idade = idade_atual(individuo.Dnascimento);

                    if(idade>=0 && idade<=5 ){
                        ct_faixa_et_0_5++;
                    }
                    if(idade >=6 && idade <=10){
                        ct_faixa_et_6_10++;
                    }
                    if(idade >=11 && idade <=20){
                        ct_faixa_et_11_20++;
                    }
                    if(idade >=21 && idade <=40){
                        ct_faixa_et_21_40++;
                    }
                    if(idade >=41 && idade <=60){
                        ct_faixa_et_41_60++;
                    }
                    if(idade > 60){
                        ct_faixa_et_60_++;
                    }

                   ct_total++;
                }
        }
    }
    fclose(arquivoPessoa);
    //cálculo do percentual só é feito se tem a quantidade de pessoas for maior que 0, por conta da divisão
    if(ct_total > 0){
        percentual_0_5 = (float)(ct_faixa_et_0_5*100)/ct_total;
        percentual_6_10 = (float)(ct_faixa_et_6_10*100)/ct_total;
        percentual_11_20 = (float)(ct_faixa_et_11_20*100)/ct_total;
        percentual_21_40 = (float)(ct_faixa_et_21_40*100)/ct_total;
        percentual_41_60 = (float)(ct_faixa_et_41_60*100)/ct_total;
        percentual_60_ = (float)(ct_faixa_et_60_*100)/ct_total;
        percentual_masculinos = (float)(ct_masculinos*100)/ct_total;
        percentual_femininos = (float)(ct_femininos*100)/ct_total;
    }
    // if para evitar a divisão por 0
    if(ct_total == 0){
            percentual_0_5 = 0;
            percentual_6_10 = 0;
            percentual_11_20 = 0;
            percentual_21_40 = 0;
            percentual_41_60 = 0;
            percentual_60_ = 0;
            percentual_femininos = 0;
            percentual_masculinos = 0;
    }



    printf("******Relatório demográfico******\n");
    printf("*percentual de:                 *\n");
    printf("*pessoas de 0 a 5 anos: %.1f%%    *\n", percentual_0_5);
    printf("*pessoas de 6 a 10 anos: %.1f%%   *\n", percentual_6_10);
    printf("*pessoas de 11 a 20 anos: %.1f%%  *\n", percentual_11_20);
    printf("*pessoas de 21 a 40 anos: %.1f%%  *\n", percentual_21_40);
    printf("*pessoas de 41 a 60 anos: %.1f%%  *\n", percentual_41_60);
    printf("*pessoas acima de 60 anos: %.1f%% *\n", percentual_60_);
    printf("*pessoas do sexo masculino: %.1f%%*\n", percentual_masculinos);
    printf("*pessoas do sexo feminino: %.1f%% *\n", percentual_femininos);
    printf("*********************************\n");
    system("pause");

}


























