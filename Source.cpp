#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::pair<std::string, bool> CommonPart(const std::string& first, const std::string& second) { //функция от двух переменных, которая вернет два значения
    std::string currentWord = first;  
    bool match = false;

    for (int j = 0; j < first.size(); j++) { //запускаем цикл, который будет сравнивать все подстроки первого и второго слов (берем все подстроки строки first при разных j, для слова ХУЙ при j = 1, будет слово УЙ)
        if (second.size() >= first.size() - j) { //если длина второй строки больше чем длина подстроки первого слова
            match = std::equal(first.begin() + j, first.end(), second.begin()); //сравниваем части подстрок, если подстрока первого слова, которая начинается с j-того символа равна подстроке второго слова

            if (match) { //если общая часть есть 
                currentWord = first + second.substr(first.size() - j); // присоединяем к первому слову оставшуюся часть второго слова
                break;
            }
        }
        else { //если второй строки меньше чем длина подстроки первого слова 
            match = std::equal(first.begin() + j, first.begin() + j + second.size(), second.begin());  //сравниваем части подстрок, лежит ли второе слово внутри первого

            if (match) { //если лежит
                currentWord = first; //присваиваем текущему слову значение первого слова
                break;
            }
        }
    }

    return std::make_pair(currentWord, match); //возвращаем текущее слово и есть ли вообще общая часть у этих двух слов
}


void CommonSequence(int n, std::vector<std::string>& subseqs, std::vector<int>& position) {
    std::string res_string; //создаем переменную, в которой будем хранить итоговый ответ
    bool flag = true; //создаем переменную, которая будет позволять выполняться циклу while

    while (flag) { //запускаем цикл, пока значение flag равно true 
        bool match = false; //создаем переменную, которая обозначает, есть ли у двух слов общая часть
        std::string currentWord = subseqs[position[0]];//инициализируем новую переменную, означающую текущее слово, относительно которого мы смотрим возможные комбинации строк

        for (int i = 1; i < subseqs.size(); i++) { // запускаем цикл, в котором мы пробежимся по вектору подпоследовательностей и сравним выбранное текущее слово с остальными
            match = false; //поставим, что пока что общей части нет
            std::string first = currentWord; //создаем новую переменную в которой будет храниться текущее слово
            std::string second = subseqs[position[i]]//создаем переменную в которой будет храниться i-ое слово из вектора
            

            auto [newWord, newMatch] = CommonPart(first, second); //commonpart - фукнция которая возвращает две переменные, такая запись говорит нам, что в переменную newWord мы положим новое слово, а в newmatch в целом, есть ли у них общая часть

            if (!newMatch) {
                currentWord = first + second; //если же у двух слов общих частей нет, то просто складываем их
            }
            else {
                currentWord = newWord; //если же общая часть есть, то присваиваем ее значение текущему слову 
                match = newMatch;
            }
        }

        if (res_string.empty() || (currentWord.size() < res_string.size())) { //если итоговая строчка пуста или же длина текущего слова меньше длины итогового 
            res_string = currentWord; //то присваиваем итоговой строчке значение текущего слова
        }

        flag = std::next_permutation(position.begin(), position.end()); //если вдруг комбинации всех подстрок кончились, выходим из цикла
    }

    std::cout << res_string.size() << std::endl;
}

int main() {
    int n; //инициализируем переменную, которая обозначает количество слов
    std::cin >> n; // вводим ее значение

    std::vector<std::string> subseqs(n); //создаем вектор, в котором будут лежать подпоследовательности
    std::vector<int> position(n); //создаем вектор, в котором будет лежать порядок вводимых слов (для первого вводимого слова позиция будет 1)

    for (int i = 0; i < n; i++) { //цикл, который проходится по всем ячейкам вектора
        std::string subseq;//инициализируем переменную, которая будет хранить в себе каждый раз новое слово
        std::cin >> subseq;//вводим слово

        subseqs[i] = subseq;//записываем его в i-ую ячейку вектора(первое слово будет записано в первую ячейку и тд)
        position[i] = i;//записываем в вектор позицию нашего слова (у первого слова будет позиция 0)
    }

    CommonSequence(n, subseqs, position); //запускаем функцию по поиску общей строки 

    return 0;
}