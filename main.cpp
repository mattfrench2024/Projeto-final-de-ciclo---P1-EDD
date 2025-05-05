// alisson santos 
// davi coelho 
// matheus correia

#include <iostream>
#include <locale.h>
#include <string>
#include <ctime>
#include <cmath>
#include <cctype>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class StringFormatacao
{

    public: 
        StringFormatacao() {}

    string StringFormatada(string palavra){
        vector<string> partes;
        stringstream ss("alisson santos");


        while (ss >> palavra)
            partes.push_back(palavra);

        if (partes.size() == 0)
            return "Erro";

        string sobrenome = partes.back();
        partes.pop_back(); 


        string referencia = "";


        for (char& c : sobrenome)
            referencia += toupper(c);

        referencia += ", ";


        if (!partes.empty()) {
            referencia += partes[0] + " ";
        }


        for (size_t i = 1; i < partes.size(); ++i) {
            referencia += toupper(partes[i][0]);
            referencia += ". ";
        }

        return referencia;
    }
};

// Classe Data
class Data {
private:
    int dia;
    int mes;
    int ano;

public:
    Data(int dia, int mes, int ano) : dia(dia), mes(mes), ano(ano) {}
    Data() : dia(0), mes(0), ano(0) {}

    void setDia(int dia) { this->dia = dia; }
    void setMes(int mes) { this->mes = mes; }
    void setAno(int ano) { this->ano = ano; }

    int getDia() const { return dia; }
    int getMes() const { return mes; }
    int getAno() const { return ano; }

    string getDataFormatada() const {
        string diaStr = to_string(dia);
        string mesStr = to_string(mes);
        string anoStr = to_string(ano);

        return diaStr.insert(0, 2 - diaStr.size(), '0') + "/" +
               mesStr.insert(0, 2 - mesStr.size(), '0') + "/" +
               anoStr.insert(0, 4 - anoStr.size(), '0');
    }
};

// Classe Contato
class Contato {
private:
    string _email;
    string _nome;
    string telefone;
    Data dataNascimento;

public:
    Contato() {}
    Contato(const string& email, const string& nome, const string& telefone, const Data& dataNascimento)
        : _email(email), _nome(nome), telefone(telefone), dataNascimento(dataNascimento) {}

    void setEmail(const string& email) { this->_email = email; }
    void setNome(const string& nome) { this->_nome = nome; }
    void setTelefone(const string& telefone) { this->telefone = telefone; }
    void setDataNascimento(const Data& dataNascimento) { this->dataNascimento = dataNascimento; }

    string getEmail() const { return _email; }
    string getNome() const { return _nome; }
    string getTelefone() const { return telefone; }
    Data getDataNascimento() const { return dataNascimento; }

    int calcularIdade() const {
        time_t tempoAtual = time(nullptr);
        tm* dataAtual = localtime(&tempoAtual);

        int diaAtual = dataAtual->tm_mday;
        int mesAtual = dataAtual->tm_mon + 1;
        int anoAtual = dataAtual->tm_year + 1900;

        int idade = anoAtual - dataNascimento.getAno();
        if (mesAtual < dataNascimento.getMes() || (mesAtual == dataNascimento.getMes() && diaAtual < dataNascimento.getDia())) {
            idade--;
        }

        return idade;
    }

    void exibirContato() const {
        cout << "Nome: " << _nome << endl;
        cout << "Email: " << _email << endl;
        cout << "Telefone: " << telefone << endl;
        cout << "Idade: " << calcularIdade() << " anos" << endl;
        cout << "Data de nascimento: " << dataNascimento.getDataFormatada() << endl;
        cout << "-----------------------------" << endl;
    }
    void exibirContatoBibliografico() const {
        StringFormatacao formatacaoReferenciaBibliografica;
        cout << "Nome: " << formatacaoReferenciaBibliografica.StringFormatada(_nome) << endl;
        cout << "Email: " << _email << endl;
        cout << "Telefone: " << telefone << endl;
        cout << "Idade: " << calcularIdade() << " anos" << endl;
        cout << "Data de nascimento: " << dataNascimento.getDataFormatada() << endl;
        cout << "-----------------------------" << endl;
    }
};



int main() {
    setlocale(LC_ALL, "");

    const int quantidadeContatos = 3;
    Contato contato[quantidadeContatos];
    int mediaIdadeContato = 0;
    int TotalSomaIdadeContato = 0;
    int totalMaioresDeIdade = 0;

    for (int i = 0; i < quantidadeContatos; ++i) {
        cout << "\nCadastro do Contato [" << i + 1 << "]:" << endl;

        string nome, email, telefone;
        int diaNascimento, mesNascimento, anoNascimento;

        cout << "Nome: ";
        getline(cin, nome);

        cout << "Email: ";
        getline(cin, email);

        cout << "Telefone: ";
        getline(cin, telefone);

        cout << "Data de nascimento (dia mes ano): ";
        cin >> diaNascimento >> mesNascimento >> anoNascimento;
        cin.ignore();

        Data dataNascimento(diaNascimento, mesNascimento, anoNascimento);
        contato[i] = Contato(email, nome, telefone, dataNascimento);

        TotalSomaIdadeContato += contato[i].calcularIdade();
        
    }

    mediaIdadeContato = floor(TotalSomaIdadeContato / quantidadeContatos);

    cout << "\n=== Lista de Contatos ===" << endl;
    for (int i = 0; i < quantidadeContatos; ++i) {
        cout << "\nContato [" << i + 1 << "]:" << endl;
        contato[i].exibirContato();
    }

    cout << "\n=== Media de Idades de Contatos ===" << endl;
    cout << mediaIdadeContato << endl;
    StringFormatacao formatacaoReferenciaBibliografica;

    cout << "\n=== Lista de Contatos maiores que a média ===" << endl;
    for (int i = 0; i < quantidadeContatos; ++i) {
        int idadeContato = contato[i].calcularIdade();
        if ( idadeContato > mediaIdadeContato)
        {
            cout << "\nContato [" << i + 1 << "]:" << endl;
            cout << "Nome: " << formatacaoReferenciaBibliografica.StringFormatada(contato[i].getNome()) << endl;
        }
    }

    cout << "\n=== Quantidade de Contatos maiores que a média ===" << endl;

    
    for (int i = 0; i < quantidadeContatos; ++i) {
        int idadeContato = contato[i].calcularIdade();
        if ( idadeContato >= 18)
            totalMaioresDeIdade ++;
    }
    cout << totalMaioresDeIdade << endl;

    int idadeContato = 0;
    for (int i = 0; i < quantidadeContatos; ++i) {
        int _idadeContato = contato[i].calcularIdade();
        if ( _idadeContato > idadeContato)
            idadeContato = _idadeContato;
    }

    cout << "\n=== Lista de Contatos mais velhos ===" << endl;
    for (int i = 0; i < quantidadeContatos; ++i) {
        if (contato[i].calcularIdade() == idadeContato)
        {
            cout << "\nContato [" << i + 1 << "]:" << endl;

            contato[i].exibirContatoBibliografico();
        }
    }

    return 0;
}
