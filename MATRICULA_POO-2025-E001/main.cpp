#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

// Classe Equipamento
class Equipamento {
private:
    int id;
    string nome;
    string categoria;
    bool disponivel;

public:
    // Construtor garantindo estado válido
    Equipamento(int id, const string& nome, const string& categoria)
        : id(id), nome(nome), categoria(categoria), disponivel(true) {
        if (id <= 0) {
            throw invalid_argument("ID deve ser positivo");
        }
        if (nome.size() < 3) {
            throw invalid_argument("Nome deve ter no mínimo 3 caracteres");
        }
        if (categoria.empty()) {
            throw invalid_argument("Categoria não pode ser vazia");
        }
    }

    // Getters
    int getId() const { return id; }
    string getNome() const { return nome; }
    string getCategoria() const { return categoria; }
    bool isDisponivel() const { return disponivel; }

    // Métodos de negócio
    bool marcarEmprestado() {
        if (!disponivel) return false;
        disponivel = false;
        return true;
    }

    bool marcarDevolvido() {
        if (disponivel) return false;
        disponivel = true;
        return true;
    }
};

// =======================
// Classe Emprestimo
// =======================
class Emprestimo {
private:
    int idEquipamento;
    string nomePessoa;
    string data;
    bool ativo;

public:
    Emprestimo(int idEquipamento, const string& nomePessoa, const string& data)
        : idEquipamento(idEquipamento), nomePessoa(nomePessoa), data(data), ativo(true) {
        if (nomePessoa.empty()) {
            throw invalid_argument("Nome da pessoa não pode ser vazio");
        }
    }

    int getIdEquipamento() const { return idEquipamento; }
    bool isAtivo() const { return ativo; }

    void encerrar() {
        ativo = false;
    }
};

// Classe SistemaLab
class SistemaLab {
private:
    vector<Equipamento> equipamentos;
    vector<Emprestimo> emprestimos;

    Equipamento* buscarEquipamentoInterno(int id) {
        for (auto &e : equipamentos) {
            if (e.getId() == id) return &e;
        }
        return nullptr;
    }

    Emprestimo* buscarEmprestimoAtivo(int idEquipamento) {
        for (auto &emp : emprestimos) {
            if (emp.getIdEquipamento() == idEquipamento && emp.isAtivo()) {
                return &emp;
            }
        }
        return nullptr;
    }

public:
    void cadastrarEquipamento() {
        int id;
        string nome, categoria;

        cout << "ID do equipamento: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (buscarEquipamentoInterno(id)) {
            cout << "Erro: ID já cadastrado.\n";
            return;
        }

        cout << "Nome: ";
        getline(cin, nome);
        cout << "Categoria: ";
        getline(cin, categoria);

        try {
            equipamentos.emplace_back(id, nome, categoria);
            cout << "Equipamento cadastrado com sucesso.\n";
        } catch (const exception &e) {
            cout << "Erro: " << e.what() << "\n";
        }
    }

    void listarEquipamentos() const {
        if (equipamentos.empty()) {
            cout << "Nenhum equipamento cadastrado.\n";
            return;
        }

        for (const auto &e : equipamentos) {
            cout << "ID: " << e.getId()
                 << " | Nome: " << e.getNome()
                 << " | Categoria: " << e.getCategoria()
                 << " | Status: " << (e.isDisponivel() ? "Disponível" : "Emprestado")
                 << "\n";
        }
    }

    void emprestarEquipamento() {
        int id;
        string nomePessoa, data;

        cout << "ID do equipamento: ";
        cin >> id;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        Equipamento* eq = buscarEquipamentoInterno(id);
        if (!eq) {
            cout << "Equipamento não encontrado.\n";
            return;
        }

        if (!eq->isDisponivel()) {
            cout << "Equipamento já está emprestado.\n";
            return;
        }

        cout << "Nome da pessoa: ";
        getline(cin, nomePessoa);
        cout << "Data do empréstimo: ";
        getline(cin, data);

        try {
            if (eq->marcarEmprestado()) {
                emprestimos.emplace_back(id, nomePessoa, data);
                cout << "Empréstimo realizado com sucesso.\n";
            }
        } catch (const exception &e) {
            cout << "Erro: " << e.what() << "\n";
        }
    }

    void devolverEquipamento() {
        int id;
        cout << "ID do equipamento: ";
        cin >> id;

        Equipamento* eq = buscarEquipamentoInterno(id);
        if (!eq) {
            cout << "Equipamento não encontrado.\n";
            return;
        }

        if (eq->isDisponivel()) {
            cout << "Equipamento já está disponível.\n";
            return;
        }

        Emprestimo* emp = buscarEmprestimoAtivo(id);
        if (!emp) {
            cout << "Erro interno: empréstimo ativo não encontrado.\n";
            return;
        }

        emp->encerrar();
        eq->marcarDevolvido();
        cout << "Equipamento devolvido com sucesso.\n";
    }

    void buscarPorId() const {
        int id;
        cout << "ID do equipamento: ";
        cin >> id;

        for (const auto &e : equipamentos) {
            if (e.getId() == id) {
                cout << "ID: " << e.getId()
                     << " | Nome: " << e.getNome()
                     << " | Categoria: " << e.getCategoria()
                     << " | Status: " << (e.isDisponivel() ? "Disponível" : "Emprestado")
                     << "\n";
                return;
            }
        }
        cout << "Equipamento não encontrado.\n";
    }
};

// Função principal (menu)
int main() {
    SistemaLab sistema;
    int opcao;

    do {
        cout << "\n===== Sistema de Empréstimos de Laboratório =====\n";
        cout << "1. Cadastrar equipamento\n";
        cout << "2. Listar equipamentos\n";
        cout << "3. Emprestar equipamento\n";
        cout << "4. Devolver equipamento\n";
        cout << "5. Buscar equipamento por ID\n";
        cout << "6. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
            case 1: sistema.cadastrarEquipamento(); break;
            case 2: sistema.listarEquipamentos(); break;
            case 3: sistema.emprestarEquipamento(); break;
            case 4: sistema.devolverEquipamento(); break;
            case 5: sistema.buscarPorId(); break;
            case 6: cout << "Encerrando sistema.\n"; break;
            default: cout << "Opção inválida.\n";
        }
    } while (opcao != 6);

    return 0;
}
