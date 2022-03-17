#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;

struct Node{
    char ch; // Буква
    int freq; // Частота
    Node* left, * right; // Ссылки на поддеревья
};

// Новый узел
Node* getNode(char ch, int freq, Node* left, Node* right){
    Node* node = new Node();
    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;
    return node;
}

// Упорядочивание вероятностей
struct comp{
    bool operator()(Node* l, Node* r){
        return l->freq > r->freq;
    }
};

// Кодирование значений
void encode(Node* root, string str, unordered_map<char, string> &huffmanCode){
    if (root == nullptr) // Если конец дерева
        return;
    if (!root->left and !root->right) { // Присваиваем значение
        huffmanCode[root->ch] = str;
    } // Идём по поддеревьям
    encode(root->left, str + "0", huffmanCode); 
    encode(root->right, str + "1", huffmanCode);
}

// Строим и выводим дерево
void buildHuffmanTree(string text){
    unordered_map<char, int> freq;
    for (char ch: text) { // Подсчитываем вероятности
        freq[ch]++;
    }
    priority_queue<Node*, vector<Node*>, comp> pq; // Хранение активных узлов
    for (auto pair: freq) {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr)); // Создание нового узла
    }
    // В очереди не 1 узел
    while (pq.size() != 1){
        // Удаляем узлы с самой маленькой вероятностью
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        // Содаём новый узел, равный сумме предыдущих
        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }
    Node* root = pq.top(); // Указатель на вершину

    // Вывод
    // Проходим по дереву и выводим, сохраняем все значения узлов
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);
    cout << "Huffman коды:\n" << '\n';
    for (auto pair: huffmanCode) {
        cout << pair.first << " " << pair.second << '\n';
    }
    cout << "\nИзначальная строка: \n" << text << '\n';
    string str = "";
    string str1 = "";
    for (char ch: text) {
        str += huffmanCode[ch];
        str1 += ch;
    }
    cout << "\nЗакодированная строка: " << str << "\n\n";
    cout << "\nРаскодированная строка: " << str1 << "\n";
}

int main(){
    setlocale(LC_ALL, "rus");
    string text = "sorokin andrey aleksandrovich";
    buildHuffmanTree(text);
    return 0;
}