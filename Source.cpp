#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::pair<std::string, bool> CommonPart(const std::string& first, const std::string& second) { //������� �� ���� ����������, ������� ������ ��� ��������
    std::string currentWord = first;  
    bool match = false;

    for (int j = 0; j < first.size(); j++) { //��������� ����, ������� ����� ���������� ��� ��������� ������� � ������� ���� (����� ��� ��������� ������ first ��� ������ j, ��� ����� ��� ��� j = 1, ����� ����� ��)
        if (second.size() >= first.size() - j) { //���� ����� ������ ������ ������ ��� ����� ��������� ������� �����
            match = std::equal(first.begin() + j, first.end(), second.begin()); //���������� ����� ��������, ���� ��������� ������� �����, ������� ���������� � j-���� ������� ����� ��������� ������� �����

            if (match) { //���� ����� ����� ���� 
                currentWord = first + second.substr(first.size() - j); // ������������ � ������� ����� ���������� ����� ������� �����
                break;
            }
        }
        else { //���� ������ ������ ������ ��� ����� ��������� ������� ����� 
            match = std::equal(first.begin() + j, first.begin() + j + second.size(), second.begin());  //���������� ����� ��������, ����� �� ������ ����� ������ �������

            if (match) { //���� �����
                currentWord = first; //����������� �������� ����� �������� ������� �����
                break;
            }
        }
    }

    return std::make_pair(currentWord, match); //���������� ������� ����� � ���� �� ������ ����� ����� � ���� ���� ����
}


void CommonSequence(int n, std::vector<std::string>& subseqs, std::vector<int>& position) {
    std::string res_string; //������� ����������, � ������� ����� ������� �������� �����
    bool flag = true; //������� ����������, ������� ����� ��������� ����������� ����� while

    while (flag) { //��������� ����, ���� �������� flag ����� true 
        bool match = false; //������� ����������, ������� ����������, ���� �� � ���� ���� ����� �����
        std::string currentWord = subseqs[position[0]];//�������������� ����� ����������, ���������� ������� �����, ������������ �������� �� ������� ��������� ���������� �����

        for (int i = 1; i < subseqs.size(); i++) { // ��������� ����, � ������� �� ���������� �� ������� ���������������������� � ������� ��������� ������� ����� � ����������
            match = false; //��������, ��� ���� ��� ����� ����� ���
            std::string first = currentWord; //������� ����� ���������� � ������� ����� ��������� ������� �����
            std::string second = subseqs[position[i]]//������� ���������� � ������� ����� ��������� i-�� ����� �� �������
            

            auto [newWord, newMatch] = CommonPart(first, second); //commonpart - ������� ������� ���������� ��� ����������, ����� ������ ������� ���, ��� � ���������� newWord �� ������� ����� �����, � � newmatch � �����, ���� �� � ��� ����� �����

            if (!newMatch) {
                currentWord = first + second; //���� �� � ���� ���� ����� ������ ���, �� ������ ���������� ��
            }
            else {
                currentWord = newWord; //���� �� ����� ����� ����, �� ����������� �� �������� �������� ����� 
                match = newMatch;
            }
        }

        if (res_string.empty() || (currentWord.size() < res_string.size())) { //���� �������� ������� ����� ��� �� ����� �������� ����� ������ ����� ��������� 
            res_string = currentWord; //�� ����������� �������� ������� �������� �������� �����
        }

        flag = std::next_permutation(position.begin(), position.end()); //���� ����� ���������� ���� �������� ���������, ������� �� �����
    }

    std::cout << res_string.size() << std::endl;
}

int main() {
    int n; //�������������� ����������, ������� ���������� ���������� ����
    std::cin >> n; // ������ �� ��������

    std::vector<std::string> subseqs(n); //������� ������, � ������� ����� ������ ���������������������
    std::vector<int> position(n); //������� ������, � ������� ����� ������ ������� �������� ���� (��� ������� ��������� ����� ������� ����� 1)

    for (int i = 0; i < n; i++) { //����, ������� ���������� �� ���� ������� �������
        std::string subseq;//�������������� ����������, ������� ����� ������� � ���� ������ ��� ����� �����
        std::cin >> subseq;//������ �����

        subseqs[i] = subseq;//���������� ��� � i-�� ������ �������(������ ����� ����� �������� � ������ ������ � ��)
        position[i] = i;//���������� � ������ ������� ������ ����� (� ������� ����� ����� ������� 0)
    }

    CommonSequence(n, subseqs, position); //��������� ������� �� ������ ����� ������ 

    return 0;
}