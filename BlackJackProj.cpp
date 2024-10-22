#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define random(a, b) ((a) + rand() % ((b) - (a) + 1))

// создание главной колоды
int** CardsSet() {
    const int WIGHT = 52;
    int** set = new int* [WIGHT];
    for (int index = 0, value = 2; value < 15; value++) {
        for (int suit = 3; suit < 7; suit++) {
            set[index++] = new int[2]{ value, suit };
        }
    }
    return set;
}

// замешка колоды
void shuffleSet(int** set) {
    srand(static_cast<unsigned int>(time(0)));
    const int WIGHT = 52;
    for (int i = 0; i < WIGHT; i++) {
        int randomIndex = random(0, WIGHT - 1);
        swap(set[i], set[randomIndex]);
    }
}

// вывод карт
void showCards(int** set, int countCards) {
    for (int i = 0; i < countCards; i++) {
        switch (set[i][0]) {
        case 11: cout << "J"; break;
        case 12: cout << "Q"; break;
        case 13: cout << "K"; break;
        case 14: cout << "A"; break;
        default: cout << set[i][0];
        }
        cout << char(set[i][1]) << " ";
    }
}

// новый вывод карт
void showHands(int** playerCard, int playerCardCount, int** dealerCard, int dealerCardCount, bool revealDealer = false) {
    cout << endl << "Твои карты: ";
    showCards(playerCard, playerCardCount);

    cout << endl << "Карты дилера: ";
    if (revealDealer) {
        showCards(dealerCard, dealerCardCount);
    }
    else {
        showCards(dealerCard, 1);
        cout << " ";
    }
}

// раздача игроку и дилеру
void cardsUser(int** set, int& cardIndex, int** playerCard, int** dealerCard, int& playerCardCount, int& dealerCardCount) {
    playerCard[playerCardCount++] = set[cardIndex++];
    dealerCard[dealerCardCount++] = set[cardIndex++];
    playerCard[playerCardCount++] = set[cardIndex++];
    dealerCard[dealerCardCount++] = set[cardIndex++];
}

// добавление карты игроку
void addCard(int** set, int& cardIndex, int** playerHand, int& playerCardCount) {
    playerHand[playerCardCount++] = set[cardIndex++];
}

// подсчет суммы карт
int cardSumm(int** hand, int cardCount) {
    int summ = 0;
    int aceCount = 0;

    for (int i = 0; i < cardCount; i++) {
        int cardValue = hand[i][0];
        if (cardValue > 10 && cardValue < 14) {
            summ += 10;
        }
        else if (cardValue == 14) {
            summ += 11;
            aceCount++;
        }
        else {
            summ += cardValue;
        }
    }

    while (summ > 21 && aceCount > 0) {
        summ -= 10;
        aceCount--;
    }

    return summ;
}

bool more21(int** hand, int cardCount) {
    return cardSumm(hand, cardCount) > 21;
}

// добавление карты дилеру
void dealerAddCard(int** set, int& cardIndex, int** dealerHand, int& dealerCardCount) {
    while (cardSumm(dealerHand, dealerCardCount) < 17) {
        addCard(set, cardIndex, dealerHand, dealerCardCount);
    }
}

int main() {
    setlocale(LC_ALL, "");

    const int MAX = 10; // максимальное количество карт в руке
    int** set = CardsSet(); // вся колода
    shuffleSet(set);

    int playerCardCount = 0;
    int dealerCardCount = 0;
    int* playerCard[MAX] = { nullptr }; // колода игрока
    int* dealerCard[MAX] = { nullptr }; // колода дилера
    int cardIndex = 0;

    cardsUser(set, cardIndex, playerCard, dealerCard, playerCardCount, dealerCardCount);
    showHands(playerCard, playerCardCount, dealerCard, dealerCardCount, false);

    if (cardSumm(playerCard, playerCardCount) == 21) {
        cout << endl << "Вы выиграли с блэкджеком!" << endl;
        return 0;
    }

    bool playerMove = true; // проверка хода (чей ход , игрока или дилера)

    while (!more21(playerCard, playerCardCount) && playerMove) {
        int choice2 = 0;
        cout << endl << "1 - Взять карту, 2 - Оставить" << endl;
        cin >> choice2;

        switch (choice2) {
        case 1:
            addCard(set, cardIndex, playerCard, playerCardCount);
            showHands(playerCard, playerCardCount, dealerCard, dealerCardCount, false);
            if (more21(playerCard, playerCardCount)) {
                cout << "Вы превысили 21! Вы проиграли." << endl;
                playerMove = false;
            }
            break;

        case 2:
            dealerAddCard(set, cardIndex, dealerCard, dealerCardCount);
            showHands(playerCard, playerCardCount, dealerCard, dealerCardCount, true);
            playerMove = false;
            break;

        default:
            cout << "Неверный ввод. Попробуйте снова." << endl;
            break;
        }
    }

    if (!more21(playerCard, playerCardCount)) {
        int playerSum = cardSumm(playerCard, playerCardCount);
        int dealerSum = cardSumm(dealerCard, dealerCardCount);

        if (dealerSum > 21 || playerSum > dealerSum) {
            cout << endl << "Вы выиграли!" << endl;
        }
        else if (dealerSum == playerSum) {
            cout << endl << "Ничья!" << endl;
        }
        else {
            cout << endl << "Вы проиграли!" << endl;
        }
    }
}
