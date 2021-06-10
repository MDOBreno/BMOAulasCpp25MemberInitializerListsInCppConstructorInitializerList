//
//  main.cpp
//  BMOAulasCpp25MemberInitializerListsInCppConstructorInitializerList
//
//  Created by Breno Medeiros on 10/06/21.
//

#include <iostream>
#include <string>


class Exemplo {
public:
    Exemplo(){
        std::cout << "Entidade EXEMPLO Criado!" << std::endl;
    }
    Exemplo(int x){
        std::cout << "Entidade EXEMPLO Criado com " << x << "!" << std::endl;
    }
};


class Entidade {
private:
    std::string m_Nome;
    int m_Score;
    Exemplo m_Exemplo;
public:
    /*Entidade() {                          //'Primeiro caso': Para usar esse caso descomente-o aqui na 'Entidade' e na 'main',
        m_Nome = "Desconhecido";            // e comente o 'Terceiro caso' aqui na 'Entidade' e na 'main'
        m_Score = 0;
        m_Exemplo = Exemplo(8);
    }*/
    
    Entidade(const std::string& nome) {     //Segundo caso: Recebendo os atributos de 'Entidade' pelos parametros
        m_Nome = nome;
        m_Score = 0;
        m_Exemplo = Exemplo(8);
    }
    
    //Obs:No caso abaixo voce TEM que escrever os atributos abaixo na mesma ordem em os declarou, pois da erros em alguns compiladores
    Entidade():                             //'Terceiro caso': Para usar esse caso descomente-o aqui na 'Entidade' e na 'main',
            m_Nome("Desconhecido"),         // e comente o 'Primeiro caso' aqui na 'Entidade' e na 'main'
            m_Score(0),
            m_Exemplo(8){                   //Obs: Escrever 'm_Exemplo(8)' é o mesmo que escrever 'm_Exemplo(m_Exemplo(8))'
        //inicializarClasse();              //Isso aqui é muito usado, e separar RegraDeNogocio de Instaciacoes é visualmente melhor
    }
    
    const std::string& GetNome() const {
        return m_Nome;
    }
};


int main(int argc, const char * argv[]) {
    // insert code here...
    
    //std::cout << "------------------------- COMECO CASO 1 -------------------------" << std::endl;
    /* Entidade e0; //Primeiro caso: Usando o construtor generico
    std::cout << e0.GetNome() << std::endl; */
    
    
    std::cout << "------------------------- COMECO CASO 2 -------------------------" << std::endl;
    Entidade e1("Breno"); //Segundo caso: Usando o construtor que nos criamos
    std::cout << e1.GetNome() << std::endl;
    //Repare no console que, mesmo nos tendo inicializado 'm_Exemplo = Exemplo(8);' com nosso construtor personalizado,
    // o construtor ganerico 'Exemplo::Exemplo()' foi executado desnecessariamente(perdendo desempenho), e podemos perceber isso
    // no console pois "Entidade EXEMPLO Criado!" foi printado antes de "Entidade EXEMPLO Criado com 8!".
    // Isso ocorreu porque idealmente deveriamos fazer inicializacoes usando ListaInicializadoraDeMembros como no Caso 3 abaixo:
    
    std::cout << "------------------------- COMECO CASO 3 -------------------------" << std::endl;
    Entidade e2;    //Terceiro caso: Usando uma ListaInicializadoraDeMembros(MemberInitializerLists ou ConstructorInitializerList)
    std::cout << e2.GetNome() << std::endl;
    //Existem tres motivos para se usar uma ListaInicializadoraDeMembros em vez dos outros dois casos:
    // 1) Esteticamente fica mais nitido o que se faz, pois separar RegraDeNogocio de Instaciacoes é visualmente melhor.
    // 2) Quando se deixa algum(ou todos os) atributo(s) fora da ListaInicializadoraDeMembros, por exemplo assim:
    //          Entidade():
    //                  m_Score(0) {
    //              m_Nome = "Desconhecido";
    //              inicializarClasse();
    //          }
    // ...o que esta acontecendo na pratica é:
    //          Entidade():
    //                  m_Score(0) {
    //              m_Nome = std::string("");  //Esta linha esta ocorrendo desnecessariamente pelo construtor generico
    //              m_Nome = std::string("Desconhecido");
    //              inicializarClasse();
    //          }
    // ...Resultando em perda de performace ao criarAutomaticamente/executar a linha 'm_Nome = std::string("");'
    // 3) O unico jeito de inicializar atributos 'const' é com uma ListaInicializadoraDeMembros.
    
    
    
    
    return 0;
}
