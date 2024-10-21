#include <iostream>
using namespace std;

// Функция для генерации случайного числа
int random(int min, int max) {
    static unsigned int seed = 5323;
    seed = (8253729 * seed + 29345734765);
    return min + (seed % (max - min + 1));
}


// Функция для подсчета очков
int calculateHandValue(const int hand[], int handSize) {
    int sum = 0;
    int aceCount = 0;

    for (int i = 0; i < handSize; i++) {
        int card = hand[i];
        if (card > 10) {
            sum += 10; // Король, Дама, Валет - 10
        }
        else if (card == 1) {
            aceCount++;
            sum += 11; // Сначала считаем туза - 11
        }
        else {
            sum += card;
        }
    }

    // Если сумма больше 21 и есть тузы, пересчитываем их как 1
    while (sum > 21 && aceCount > 0) {
        sum -= 10;
        aceCount--;
    }

    return sum;
}

// Функция для вывода руки игрока
void printHand(const int hand[], int handSize) {
    for (int i = 0; i < handSize; i++) {
        int card = hand[i];
        if (card == 1) {
            cout << "A ";
        }
        else if (card == 11) {
            cout << "J ";
        }
        else if (card == 12) {
            cout << "Q ";
        }
        else if (card == 13) {
            cout << "K ";
        }
        else {
            cout << card << " ";
        }
    }
    cout << endl;
}


int main()
{
    setlocale(LC_ALL, "Russian");
    const int DECK_SIZE = 52;
    int deck[DECK_SIZE];
    int playerHand[11], dealerHand[11];
    int playerHandSize = 0, dealerHandSize = 0;
        
    // Создаем колоду карт
    int cardIndex = 0;
    for (int i = 1; i <= 13; i++) { 
        for (int j = 0; j < 4; j++) {
            deck[cardIndex++] = i;
        }
    }

    // Тасуем колоду
    for (int i = 0; i < DECK_SIZE; i++) {
        int r = random(0, DECK_SIZE - 1);
        int temp = deck[i];
        deck[i] = deck[r];
        deck[r] = temp;
    }

    // Раздача первых двух карт игроку и дилеру
    playerHand[playerHandSize++] = deck[--cardIndex];
    dealerHand[dealerHandSize++] = deck[--cardIndex];
    playerHand[playerHandSize++] = deck[--cardIndex];
    dealerHand[dealerHandSize++] = deck[--cardIndex];

    cout << "Ваши карты: ";
    printHand(playerHand, playerHandSize);
    cout << "Ваши очки: " << calculateHandValue(playerHand, playerHandSize) << endl;

    cout << "Очки дилера (1 карта): ";
    cout << dealerHand[0] << endl;

    char choice;
    while (true) {
        cout << "Хотите взять еще карту? (a/b): ";
        cin >> choice;

        if (choice == 'a') {
            playerHand[playerHandSize++] = deck[--cardIndex];

            cout << "Ваши карты: ";
            printHand(playerHand, playerHandSize);
            cout << "Очки: " << calculateHandValue(playerHand, playerHandSize) << endl;

            if (calculateHandValue(playerHand, playerHandSize) > 21) {
                cout << "Вы проиграли!" << endl;
                return 0;
            }
        }
        else {
            break;
        }
    }

    cout << "Карты дилера: ";
    printHand(dealerHand, dealerHandSize);
    cout << "Очки дилера: " << calculateHandValue(dealerHand, dealerHandSize) << endl;

    while (calculateHandValue(dealerHand, dealerHandSize) < 17) {
        dealerHand[dealerHandSize++] = deck[--cardIndex];

        cout << "Карты дилера: ";
        printHand(dealerHand, dealerHandSize);
        cout << "Очки дилера: " << calculateHandValue(dealerHand, dealerHandSize) << endl;
    }

    int playerPoints = calculateHandValue(playerHand, playerHandSize);
    int dealerPoints = calculateHandValue(dealerHand, dealerHandSize);

    if (dealerPoints > 21 || playerPoints > dealerPoints) {
        cout << "Вы выиграли!" << endl;
    }
    else if (playerPoints < dealerPoints) {
        cout << "Вы проиграли!" << endl;
    }
    else {
        cout << "Ничья!" << endl;
    }

    return 0;
}
