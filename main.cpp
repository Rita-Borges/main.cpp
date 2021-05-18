/****************************************************/
/*  Estruturas de dados e algoritmos fundamentais   */
/*             21046->EFOLIO-A                      */
/*      Ana Rita Pinho-> 1800464->LEI               */
/****************************************************/

/****************************************************/
/*                  bibliotecas                     */
/****************************************************/

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <exception>


using namespace std;

/****************************************************/
/*                  classe erros                    */
/****************************************************/
class Erros: public exception{
private:
    string mensagem;
public:
    explicit Erros(int erro) noexcept(false);
    const char * what() const noexcept override;
};
//Funcão  Erros:
Erros::Erros(int erro) noexcept(false){
    switch(erro){
        case 1://caso a lista se encontre vazia
            this->mensagem="Lista vazia!\n";
            break;
        case 2:// caso a posicao seja inválida
            this->mensagem= "Posicao invalida!\n";
            break;
        default://outros erros possiveis
            this->mensagem= "Erro Desconhecido\n";
            break;
    }
}

const char * Erros::what() const noexcept{
    return mensagem.c_str();
}

/****************************************************/
/*          (circular single linked list)           */
/*         classe  lista && classe no lista         */
/****************************************************/

class lista{
private:
    class no_lista{
    private:
        int elemento_lista;// valor da lista
        no_lista *proximo; // proximo elemento_lista da lista
    public:
        ~no_lista();
        explicit no_lista(int elemento_lista);
        no_lista * get_no_proximo();
        int get_elemento_lista() const;
        void set_proximo (no_lista * item);
    };

    no_lista *head;// Primeiro Elemento da Lista
    no_lista *tail;// Ultimo Elemento da Lista
    int C;//Contador de posicoes
public:
    typedef no_lista node;
    void incrementar_lista();
    void decrementa_lista();
    bool insert_0(int elemento_lista);
    bool insert_end (int elemento_lista );
    string print_0 ();
    string print_end ();
    string print ();
    string dim () const;
    string find_max ();
    string find (int valor);
    bool delete_0 ();
    bool delete_end ();
    bool clear ();
    bool delete_pos (int pos);
    bool invert_range (int pos1, int pos2);
    bool  inserir_pos (int pos, int valor);
    ~lista();
    lista() noexcept(false);
    no_lista * get_head();
};

typedef lista::node no;

/****************************************************/
/*              classe comandos                     */
/****************************************************/
//
class comandos {
private:
    string mensagem;// mensagem de erro
    stringstream linha;
public:
    explicit comandos(string & linha);
    ~comandos( );
    void executar_comandos (lista * lista_elemento_listas);
    bool mensagem_vazia() const;
    string get_mensagem() const;
};


/****************************************************/
/*      Funcoes referentes aos nos da lista         */
/****************************************************/

// obter proximo no
no * no::get_no_proximo(){
    return proximo;
}

//obter elemento_lista do no
int lista::no_lista::get_elemento_lista() const{
    return elemento_lista;
}

// set(atualizar) elemento_lista seguinte
void lista::no_lista :: set_proximo (no_lista * item){
    proximo=item;
}

//funcao destrutora no_lista
lista::no_lista::~no_lista (){
    this->elemento_lista=0;
    proximo=nullptr;
}
//funcao construtora no_lista
lista::no_lista::no_lista(int elemento_lista) {
    this->elemento_lista = elemento_lista;
    this->proximo = nullptr;
}

/****************************************************/
/*          funcoes pertencestes a classe lista     */
/****************************************************/

// funcao construtora
lista:: lista() noexcept(false){
    this->head = nullptr;
    this->tail = nullptr;
    this->C=0;
}
//funcao que incrementa  o contador que indica o tamanho da lista
void lista :: incrementar_lista(){
    C++;
}

//funcao que decrementao contador que indica o  tamanho da lista
void lista:: decrementa_lista(){
    if(C>0){
        C--;
        if(C==0){
            head=nullptr;
            tail=nullptr;
        }
    }
}

// funcao destrutora
lista:: ~lista( ){
    while (C!=0){
        delete_0();
    }
    this->tail= nullptr;
    this->head= nullptr;
}

//funcao que obtem o no da cabeça da lista
no * lista::get_head(){
    return this->head;
}

//funcao que implementa o comando insert_0
bool lista::insert_0(int elemento_lista) {
    if (C == 0 ){//quando a lista esta vazia
        auto * novo_no = new node(elemento_lista);
        novo_no->set_proximo(novo_no);
        head = novo_no;
        tail=  head;
        incrementar_lista();
    } else {//quando existem valores na lista
        auto * novo_no = new no_lista(elemento_lista);
        novo_no->set_proximo(head);
        head = novo_no;
        tail->set_proximo(head);
        incrementar_lista();
    }
    return true;
}

//funcao que implemnta o comando insert_end
bool lista :: insert_end ( int elemento_lista){
    if (C == 0 ){//quando a lista de encontra vazia
        auto * novo_no = new no_lista(elemento_lista);
        novo_no->set_proximo(novo_no);
        head = novo_no;
        tail=  head;
        incrementar_lista();
    } else {//quando existem valores na lista
        auto * novo_no = new no_lista(elemento_lista);
        novo_no->set_proximo(head);
        tail->set_proximo(novo_no);
        tail=novo_no;
        incrementar_lista();
    }
    return true;
}
//funcao que implementa o comando print_0
string lista:: print_0 (){
    try {
        if (C == 0) {//quando a lista esta vazia retorna erro
            throw Erros(1);
        }
        string s = "Lista(0)= ";//caso contrario emprime o elemento da cabeça
        s.append(to_string(this->head->get_elemento_lista()));
        s.append("\n");
        return s;
    } catch (const Erros & e){
        throw Erros(e);
    }
}

//funcao que implementa o comando print_end
string lista:: print_end ( ){
    try {
        if (C == 0) {//quando a lista esta vazia retorna erro
            throw Erros(1);
        }
        string s = "Lista(end)= ";//caso contrario imprime o elemento da cauda
        s.append(to_string(this->tail->get_elemento_lista()));
        s.append("\n");
        return s;
    } catch (const Erros & e){
        throw Erros(e);
    }
}

// funcao que implenta o comando print
string lista::print() {
    try{
        if(C==0)//quando a lista esta vazia retorna erro
            throw Erros(1);
        stringstream texto;//caso contrario imprime todos os elementos da lista
        texto << "Lista=";
        no_lista * temp = get_head();
        for(int i=0; i<C; i++){
            texto << " ";
            texto<< (to_string(temp->get_elemento_lista()));
            temp = temp->get_no_proximo();
        }
        texto << "\n";
        return texto.str();
    }catch (const Erros & e){
        throw Erros(e);
    }
}

//funcao que implemtenta o comando dim
string lista:: dim () const{
    stringstream res;//imprime a dimensao da lista
    res << "Lista tem " << C << " itens\n";
    return res.str();
}

//funcao que implementa o comando find_max
string lista :: find_max (){
    try {
        if (C == 0) {//quando a lista esta vazia retorna erro
            throw Erros(1);
        }//caso contrario procura o maior valor na lista
        no_lista * temporario = get_head()->get_no_proximo();
        int valor = get_head()->get_elemento_lista();
        int pos = 0;
        for(int i = 1;i < C ;i++ ){
            if (temporario->get_elemento_lista()>valor){
                valor = temporario->get_elemento_lista();
                pos = i;
            }
            temporario=temporario->get_no_proximo();
        }
        stringstream s ;// imprime o maior valor da lista
        s << "Max Item " << valor <<" na posicao " << pos << endl;
        return s.str();
    }catch (const Erros & e){
        throw Erros(e);
    }
}

//funcao que implementa o comando find
string lista::find(int valor) {
    try {
        if (C == 0) {//quando a lista esta vazia retorna erro
            throw Erros(1);
        }
        no_lista * temporario = get_head();
        //caso contrario procura na lista o valor introduzido
        for(int i = 1;i <= C ;i++ ){
            if (temporario->get_elemento_lista()==valor){//caso o valor introduzido seja igual a um item da lista
                stringstream s ;//imprime o valor e a respetiva posicao
                s << "item " << valor <<" na posicao "<< (i-1) << endl;
                return s.str();
            }
            temporario=temporario->get_no_proximo();
        }//caso o valor introduzido seja diferente de todos os itens da lista entao imprime não encontrado
        stringstream d ;
        d << "Item " << valor << " nao encontrado!" << endl;
        return d.str();
    }catch (const Erros & e){
        throw Erros(e);
    }
}

//funcao que implementa o comando delete_0
bool lista:: delete_0 ( ){
    try {
        if (C==0)//quando a lista esta vazia retorna erro
            throw Erros(1);
        no_lista* temp = head; //caso contrario passa o no da cabeca para uma variavel temporaria
        head = head->get_no_proximo();// atualiza novo no da cabeca
        tail->set_proximo(head);//cauda aponta para o novo no da cabeca
        decrementa_lista();//decrementa os nos da lista
        delete(temp);//apaga o no da cabeca
        return true;
    }catch (const Erros & e){
        throw Erros(e);
    }
}

//funcao que implementa o comando delete_end
bool lista:: delete_end ( ){
    try {
        if (C==0)//quando a lista esta vazia retorna erro
            throw Erros(1);
        no_lista* temp = head;//caso contrario passa o no da cabeca para uma variavel temporaria
        for (int i= 0; i < (C-2); i++){//percorre a lista ate a posicao anterior a solicitada
            temp = temp->get_no_proximo();
        }
        no_lista * aux = temp->get_no_proximo();//a variavel auxiliar obtem o proximo no
        temp->set_proximo(aux->get_no_proximo());//atualiza o no da variavel temporaria
        tail= temp;//o valor da cauda passa a ser a variavel temporaria
        decrementa_lista();//decrementa os nos da lista
        delete(aux);//elimina a variavel auxiliar
        return true;
    }catch (const Erros & e){
        throw Erros(e);
    }
}
// funcao que implementa o comando clear
bool lista :: clear (){
    try {
        if(C==0){//quando a lista esta vazia retorna erro
            throw Erros(1);
        }
        while (C != 0) {//enquanto existem itens na lista, estes serao eliminados pela cabeca
            delete_0();
        }
        return true;
    }catch (const Erros & e){
        throw Erros(e);
    }
}

// funcao que implementa o comando delete_posicao
bool lista:: delete_pos (int pos){
    try {
        if(C==0){//quando a lista esta vazia retorna erro
            throw Erros(1);
        }
        if (pos < 0 || pos >= C){// quando a lista assuma uma posicao  inválida
            throw Erros(2);
        }
        if (pos == 0){// caso a posicao seja 0 entao vai eliminar pela cabeca
            delete_0();
        } else if ( pos == (C-1)) {//quando a posicao e a ultima entao elimina a cauda
            delete_end();
        } else {
            no_lista *temp = head;
            for (int i = 0; i < (pos - 1); i++) {//quando nenhuma das opccoes anteriores se verificam e necessario procurar a posicao anterior a que se pretende apagar
                temp = temp->get_no_proximo();
            }
            no_lista * aux = temp->get_no_proximo();//variavel auxiliar guarda o valor no proximo no
            temp->set_proximo(aux->get_no_proximo());//atualiza o valor do no em questao
            decrementa_lista();//decrementa o no da lista
            delete(aux);//elimina variavel auxiliar
        }

        return true;
    }catch (const Erros & e){
        throw Erros(e);
    }
}

// funcao que implementa o comando inserir_posicao
bool lista:: inserir_pos (int pos, int valor){
    try {
        if (pos < 0 || pos > C){// quando a lista assume uma posicao  inválida
            throw Erros(2);
        }
        if (pos == 0){//quando a posicao e a 0 insere o item  na cabeca
            insert_0(valor);
        } else if ( pos == (C)) {//quando a posicao e igual ao contador entao insere item na cauda
            insert_end(valor);
        } else {//caso nenhuma das condicoes anteriores se verifique entao vai criar uma variavel temporaria
            no_lista *temp = head;
            auto * aux = new no_lista(valor); //criar uma variavel auxiliar
            for (int i = 0; i < (pos - 1); i++) {//percorrer a lista ate a posicao anterior a que se pretende inserir
                temp = temp->get_no_proximo();
            }
            aux->set_proximo(temp->get_no_proximo());//atualiza o valor da aux novo_no, aponta para o no que esta na posicao onde se pretende inserir
            temp->set_proximo(aux);//insere o novo no na lista
            incrementar_lista();//incrementar no da lista
        }
        return true;
    }catch (const Erros & e){
        throw Erros(e);
    }
}

// funcao que implementa o comando invert_range-> inverte os elemento_listas da lista tendo em conta as posicoes fornecidas
bool  lista:: invert_range(int pos1, int pos2){
    try{
        if(C==0){//quando a lista esta vazia retorna erro
            throw Erros(1);
        }
        if ((pos1 < 0 || pos1 >= C) || (pos2 < 0 || pos2 >= C)){
            throw Erros(2);//quando as posicoes assumem valores inválidos
        }
        // Cria uma lista temporaria e inseres os elemento_listas fornecidos (pos1,pos2) nessa mesma lista
        if(C >0){
            auto * temp = new lista();
            no_lista * temp2;
            temp2= get_head();
            for (int a=0; a <= (pos1-1); a++){
                temp2 = temp2->get_no_proximo();
            }
            for(int i= pos1; i <= pos2; i++){
                int aux= temp2->get_elemento_lista();
                temp->insert_0(aux);
                temp2 = temp2->get_no_proximo();
                delete_pos(pos1);
            }
            //copia para a lista original os elemento_listas já invertidos
            for(int i= 0; i <= pos2-pos1; i++){
                this->inserir_pos(pos1+i,temp->get_head()->get_elemento_lista());
                temp->delete_0();
            }
            delete(temp); //Apaga a lista temporária
            return true;
        }
        return false;
    } catch(Erros &e){
        throw Erros(e);
    }
}

/****************************************************/
/*      funcoes pertencentes a  classe  Comandos   */
/****************************************************/

//funcao contrutora da classe comandos
comandos:: comandos (string & linha){
    this->mensagem= "";
    this->linha.str(linha);
}

//funcao destrutora da classe comandos
comandos:: ~comandos ( ){
    this->mensagem =  "";
    this->linha.str("");
}

//funcao que trata dos outputs (interface->que executa os comandos)
void comandos :: executar_comandos (lista * lista_elemento_listas ){
    string texto;
    this->linha >> texto;
    if (texto=="insert_0") {
        while (!this->linha.eof()){//enquanto a linha nao chegue ao final
            this->linha >> texto;
            int elemento_lista = stoi(texto);
            if(lista_elemento_listas->insert_0(elemento_lista)){//chama a funcao insert_0
                this->mensagem="";
            }
        }
    }else if (texto=="insert_end") {
        while (!this->linha.eof()){//enquanto a linha nao chegue ao final
            this->linha >> texto;
            int elemento_lista = stoi(texto);
            lista_elemento_listas->insert_end(elemento_lista);//chama a funcao insert_end
        }
    } else if(texto=="print_0"){
        try {
            this->mensagem = lista_elemento_listas->print_0();//caso leia o comando print_0 chama a funcao print_0
        }catch (const Erros &e){
            this->mensagem = "Comando print_0: ";
            this->mensagem.append(e.what());
        }
    } else if(texto=="print_end"){
        try {
            this->mensagem = lista_elemento_listas->print_end();//caso leia o comando print_end chama a funcao print_end
        }catch (const Erros &e){
            this->mensagem = "Comando print_end: ";
            this->mensagem.append(e.what());
        }
    } else if(texto=="print"){
        try {
            this->mensagem = lista_elemento_listas->print();//caso leia o comando print chama a funcao print
        }catch (const Erros &e) {
            this->mensagem = "Comando print: ";
            this->mensagem.append(e.what());
        }
    } else if(texto=="dim"){
        this->mensagem = lista_elemento_listas->dim();//caso leia o comando dim chama a funcao dim
    }else if(texto=="find_max") {
        try {
            this->mensagem = lista_elemento_listas->find_max();//caso leia o comando find_max chama a funcao find_max
        } catch (const Erros &e) {
            this->mensagem = "Comando find_max: ";
            this->mensagem.append(e.what());
        }
    } else if(texto=="find") {
        try {
            this->linha >> texto;
            int elemento_lista = stoi(texto);
            this->mensagem = lista_elemento_listas->find(elemento_lista);//caso leia o comando find chama a funcao find
        } catch (const Erros &e) {
            this->mensagem = "Comando find: ";
            this->mensagem.append(e.what());
        }
    }else if(texto=="delete_0") {
        try {
            if(lista_elemento_listas->delete_0()){//caso leia o comando delete_0 chama a funcao delete_0
                this->mensagem="";
            }
        } catch (const Erros &e) {
            this->mensagem = "Comando delete_0: ";
            this->mensagem.append(e.what());
        }
    }else if(texto=="delete_end") {
        try {
            if(lista_elemento_listas->delete_end()){//caso leia o comando delete_end chama a funcao delete_end
                this->mensagem="";
            }
        } catch (const Erros &e) {
            this->mensagem = "Comando delete_end: ";
            this->mensagem.append(e.what());
        }
    }else if(texto=="clear") {
        try {//caso leia o comando clear chama a funcao clear
            if(lista_elemento_listas->clear()){
                this->mensagem="";
            }
        } catch (const Erros &e) {
            this->mensagem = "Comando clear: ";
            this->mensagem.append(e.what());
        }
    }else if(texto=="delete_pos") {
        try {//caso leia o comando delete_pos chama a funcao delete-pos
            this->linha >> texto;
            int elemento_lista = stoi(texto);
            if(lista_elemento_listas->delete_pos(elemento_lista)){
                this->mensagem="";
            }
        } catch (const Erros &e) {
            this->mensagem = "Comando delete_pos: ";
            this->mensagem.append(e.what());
        }
    }else if(texto=="invert_range") {
        try {//caso leia o comando invert_range chama a funcao inveret_range
            this->linha >> texto;
            int pos1 = stoi(texto);
            this->linha >> texto;
            int pos2 = stoi(texto);
            if(lista_elemento_listas->invert_range(pos1,pos2)){
                this->mensagem="";
            }
        } catch (const Erros &e) {
            this->mensagem = "Comando invert_range: ";
            this->mensagem.append(e.what());
        }
    }
}

//funcao que verifica se a string esta vazia
bool comandos::mensagem_vazia() const{
    return this->mensagem.empty();
}
// funcao que obtem(neste caso retorna) uma mensagem
string  comandos::get_mensagem() const{
    return mensagem;
}

/****************************************************/
/*                  funcao principal                */
/****************************************************/
/*
int main() {
    string linha;
    auto * lista_elemento_listas = new lista();
    while(getline(cin,linha)){ //Ler ficheiro
        if(linha.substr(0,1)!= "#" || linha.empty()){//caso encontre um # ignora a linha
            auto * novo_comando = new comandos(linha);
            novo_comando->executar_comandos(lista_elemento_listas);
            if(!novo_comando->mensagem_vazia()){//caso a execucao do novo_comando gere alguma mensagem
                cout << novo_comando->get_mensagem();
            }
            delete(novo_comando);
        }
    }
    delete(lista_elemento_listas);
    return 0;
}*/

int main() {
    string linha;
    auto * lista_elemento_listas = new lista();
    fstream file;
    file.open("cmd.txt", ios::in);
    while(getline(file,linha)){ //Ler ficheiro
        if(linha.substr(0,1)!= "#" || linha.empty()){
            auto * novo_comando = new comandos(linha);
            novo_comando->executar_comandos(lista_elemento_listas);
            if(!novo_comando->mensagem_vazia()){
                cout << novo_comando->get_mensagem();
            }
            delete(novo_comando);
        }
    }
    file.close();
    delete(lista_elemento_listas);
    return 0;
}

