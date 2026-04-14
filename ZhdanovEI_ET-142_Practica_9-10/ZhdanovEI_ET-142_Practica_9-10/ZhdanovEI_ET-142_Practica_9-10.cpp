// ZhdanovEI_ET-142_Practica_9-10.cpp : определяет точку входа для консольного приложения.
//

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
using namespace std;

enum MarketplaceType { GROCERY, HOME_GOODS, EVERYTHING };
enum BusinessType { MAIN, SUBSIDIARY, FRANCHISE };

struct Marketplace {
    char name[50];
    int points;
    char city[50];
    float value;
    int type;
    int business;
};

void changeMarketplaceByName(struct Marketplace* marketplaces, int n, char name[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(marketplaces[i].name, name) == 0) {
            printf("Найден маркетплейс: %s \n", marketplaces[i].name);
            printf("Введите новое название: ");
            scanf_s("%s", marketplaces[i].name, 50);
            printf("Введите новое количество ПВЗ: ");
            scanf_s("%d", &marketplaces[i].points);
            printf("Введите новый город: ");
            scanf_s("%s", marketplaces[i].city, 50);
            printf("Введите новую рыночную стоимость: ");
            scanf_s("%f", &marketplaces[i].value);
            int t = 0;
            printf("Введите новый тип (0 - продуктовый, 1 - товары для дома, 2 - всё подряд): ");
            scanf_s("%i", &t);
            marketplaces[i].type = t;
            int b = 0;
            printf("Введите новый тип бизнеса (0 - основной, 1 - вспомогательный, 2 - франшиза): ");
            scanf_s("%i", &b);
            marketplaces[i].business = b;
            const char* typeName = "";
            const char* businessName = "";
            switch (marketplaces[i].type) {
            case GROCERY: typeName = "Продуктовый"; break;
            case HOME_GOODS: typeName = "Товары для дома"; break;
            case EVERYTHING: typeName = "Всё подряд"; break;
            }
            switch (marketplaces[i].business) {
            case MAIN: businessName = "Основной"; break;
            case SUBSIDIARY: businessName = "Вспомогательный"; break;
            case FRANCHISE: businessName = "Франшиза"; break;
            }
            printf("Успешно! Новая информация: \nНазвание: %s \nПВЗ: %d \nГород: %s \nСтоимость: %.2f млн \nТип: %s \nБизнес: %s",
                marketplaces[i].name, marketplaces[i].points, marketplaces[i].city, marketplaces[i].value, typeName, businessName);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    struct Marketplace marketplaces[20] = {
        {"Ozon", 1500, "Москва", 500.5, EVERYTHING, MAIN},
        {"Wildberries", 2000, "Москва", 800.2, EVERYTHING, MAIN},
        {"Яндекс.Маркет", 800, "Санкт-Петербург", 300.7, EVERYTHING, SUBSIDIARY},
        {"Самокат", 500, "Москва", 150.3, GROCERY, MAIN},
        {"Перекрёсток", 600, "Санкт-Петербург", 200.1, GROCERY, MAIN},
        {"Магнит", 1200, "Краснодар", 350.0, GROCERY, MAIN},
        {"Лента", 700, "Новосибирск", 280.5, GROCERY, SUBSIDIARY},
        {"Fix Price", 900, "Екатеринбург", 180.0, HOME_GOODS, FRANCHISE},
        {"Hoff", 300, "Москва", 120.0, HOME_GOODS, MAIN},
        {"IKEA", 150, "Санкт-Петербург", 450.0, HOME_GOODS, MAIN},
        {"KazanExpress", 400, "Казань", 90.0, EVERYTHING, MAIN},
        {"Lamoda", 250, "Москва", 210.0, HOME_GOODS, SUBSIDIARY},
        {"СберМаркет", 450, "Москва", 170.0, GROCERY, SUBSIDIARY},
        {"ВкусВилл", 350, "Москва", 110.0, GROCERY, MAIN},
        {"Детский мир", 500, "Нижний Новгород", 95.0, HOME_GOODS, FRANCHISE},
        {"М.Видео", 600, "Москва", 320.0, HOME_GOODS, MAIN},
        {"Эльдорадо", 550, "Самара", 280.0, HOME_GOODS, MAIN},
        {"Ашан", 450, "Москва", 400.0, GROCERY, MAIN},
        {"METRO", 80, "Москва", 250.0, GROCERY, MAIN},
        {"AliExpress Россия", 300, "Москва", 150.0, EVERYTHING, FRANCHISE}
    };

    struct Marketplace grocery[20];
    int groceryCount = 0;

    for (int i = 0; i < 20; i++) {
        if (marketplaces[i].type == GROCERY) {
            grocery[groceryCount] = marketplaces[i];
            groceryCount++;
        }
    }

    for (int i = 0; i < groceryCount - 1; i++) {
        for (int j = i + 1; j < groceryCount; j++) {
            if (grocery[i].points > grocery[j].points) {
                struct Marketplace temp = grocery[i];
                grocery[i] = grocery[j];
                grocery[j] = temp;
            }
        }
    }

    printf("\n=== Продуктовые маркетплейсы (отсортировано по ПВЗ) ===\n");
    for (int i = 0; i < groceryCount; i++) {
        const char* businessName = "";
        switch (grocery[i].business) {
        case MAIN: businessName = "Основной"; break;
        case SUBSIDIARY: businessName = "Вспомогательный"; break;
        case FRANCHISE: businessName = "Франшиза"; break;
        }
        printf("%s | ПВЗ: %d | %s | %.2f млн | Продуктовый | %s\n",
            grocery[i].name, grocery[i].points, grocery[i].city, grocery[i].value, businessName);
    }

    char searchName[50];
    printf("\nВведите название маркетплейса для поиска: ");
    scanf_s("%s", searchName, 50);

    int found = -1;
    for (int i = 0; i < 20; i++) {
        if (strcmp(marketplaces[i].name, searchName) == 0) {
            found = i;
            break;
        }
    }

    if (found >= 0) {
        const char* typeName = "";
        const char* businessName = "";
        switch (marketplaces[found].type) {
        case GROCERY: typeName = "Продуктовый"; break;
        case HOME_GOODS: typeName = "Товары для дома"; break;
        case EVERYTHING: typeName = "Всё подряд"; break;
        }
        switch (marketplaces[found].business) {
        case MAIN: businessName = "Основной"; break;
        case SUBSIDIARY: businessName = "Вспомогательный"; break;
        case FRANCHISE: businessName = "Франшиза"; break;
        }
        printf("\nНайден маркетплейс:\n%s | ПВЗ: %d | %s | %.2f млн | %s | %s\n",
            marketplaces[found].name, marketplaces[found].points, marketplaces[found].city,
            marketplaces[found].value, typeName, businessName);
    }
    else {
        printf("Маркетплейс '%s' не найден\n", searchName);
    }

    struct Marketplace top3[3];
    int topCount = 0;

    for (int i = 0; i < 20; i++) {
        if (topCount < 3) {
            top3[topCount] = marketplaces[i];
            topCount++;
            for (int j = topCount - 1; j > 0 && top3[j].points > top3[j - 1].points; j--) {
                struct Marketplace temp = top3[j];
                top3[j] = top3[j - 1];
                top3[j - 1] = temp;
            }
        }
        else if (marketplaces[i].points > top3[2].points) {
            top3[2] = marketplaces[i];
            for (int j = 2; j > 0 && top3[j].points > top3[j - 1].points; j--) {
                struct Marketplace temp = top3[j];
                top3[j] = top3[j - 1];
                top3[j - 1] = temp;
            }
        }
    }

    printf("\n=== Топ-3 по ПВЗ ===\n");
    for (int i = 0; i < topCount; i++) {
        printf("%d. %s (ПВЗ: %d)\n", i + 1, top3[i].name, top3[i].points);
    }

    char changeName[50];
    printf("\nВведите название маркетплейса для изменения: ");
    scanf_s("%s", changeName, 50);
    changeMarketplaceByName(marketplaces, 20, changeName);

    struct Marketplace notMoscow[20];
    int notMoscowCount = 0;

    for (int i = 0; i < 20; i++) {
        if (strcmp(marketplaces[i].city, "Москва") != 0) {
            notMoscow[notMoscowCount] = marketplaces[i];
            notMoscowCount++;
        }
    }

    printf("\n=== Маркетплейсы не из Москвы ===\n");
    if (notMoscowCount == 0) {
        printf("Нет маркетплейсов не из Москвы");
    }
    else {
        for (int i = 0; i < notMoscowCount; i++) {
            const char* typeName = "";
            const char* businessName = "";
            switch (notMoscow[i].type) {
            case GROCERY: typeName = "Продуктовый"; break;
            case HOME_GOODS: typeName = "Товары для дома"; break;
            case EVERYTHING: typeName = "Всё подряд"; break;
            }
            switch (notMoscow[i].business) {
            case MAIN: businessName = "Основной"; break;
            case SUBSIDIARY: businessName = "Вспомогательный"; break;
            case FRANCHISE: businessName = "Франшиза"; break;
            }
            printf("%s | ПВЗ: %d | %s | %.2f млн | %s | %s\n",
                notMoscow[i].name, notMoscow[i].points, notMoscow[i].city,
                notMoscow[i].value, typeName, businessName);
        }
    }
    ofstream fout("points.txt", ios::binary | ios::out);
    char name[50];
    int newPoints;

    printf("Введите данные (название ПВЗ, -1 для завершения):\n");

    while (1) {
        scanf_s("%s", name, 50);
        scanf_s("%d", &newPoints);
        if (newPoints == -1) return 0;

        for (int i = 0; i < 20; i++) {
            if (strcmp(marketplaces[i].name, name) == 0) {
                marketplaces[i].points = newPoints;
                fout.write((char*)marketplaces, sizeof(Marketplace) * 20);
                printf("Обновлено: %s -> %d\n", marketplaces[i].name, marketplaces[i].points);
                break;
            }
        }
    }
    fout.close();
    system("Pause");
}

