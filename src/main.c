#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 12

struct AIRPLANE {
    int flightNumber;
    char departureTime[10];
    char arrivalTime[10];
    char direction[50];
    char airplaneModel[50];
    float distance;
};

void createFlights(struct AIRPLANE flights[], int n) {
    printf("Введите данные о %d авиарейсах:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Авиарейс #%d:\n", i + 1);
        printf("Номер авиарейса: ");
        scanf("%d", &flights[i].flightNumber);
        printf("Время вылета: ");
        scanf("%s", flights[i].departureTime);
        printf("Время прилёта: ");
        scanf("%s", flights[i].arrivalTime);
        printf("Направление: ");
        getchar(); // Очистка буфера ввода
        fgets(flights[i].direction, sizeof(flights[i].direction), stdin);
        flights[i].direction[strcspn(flights[i].direction, "\n")] = '\0'; // Удаление символа новой строки
        printf("Марка самолёта: ");
        fgets(flights[i].airplaneModel, sizeof(flights[i].airplaneModel), stdin);
        flights[i].airplaneModel[strcspn(flights[i].airplaneModel, "\n")] = '\0'; // Удаление символа новой строки
        printf("Расстояние: ");
        scanf("%f", &flights[i].distance);
    }
}

void printFlightWithLongestDuration(struct AIRPLANE flights[], int n) {
    float maxDuration = 0;
    int maxIndex = -1;
    for (int i = 0; i < n; i++) {
        float duration = flights[i].distance;
        if (duration > maxDuration) {
            maxDuration = duration;
            maxIndex = i;
        }
    }
    if (maxIndex != -1) {
        printf("Авиарейс с максимальной длительностью полёта:\n");
        printf("Номер авиарейса: %d\n", flights[maxIndex].flightNumber);
        printf("Время вылета: %s\n", flights[maxIndex].departureTime);
        printf("Время прилёта: %s\n", flights[maxIndex].arrivalTime);
        printf("Направление: %s\n", flights[maxIndex].direction);
        printf("Марка самолёта: %s\n", flights[maxIndex].airplaneModel);
        printf("Расстояние: %.2f\n", flights[maxIndex].distance);
    } else {
        printf("Нет данных об авиарейсах.\n");
    }
}

void printFlightsByDirection(struct AIRPLANE flights[], int n, const char* direction) {
    printf("Авиарейсы с направлением '%s':\n", direction);
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (strcmp(flights[i].direction, direction) == 0) {
            printf("Авиарейс #%d:\n", i + 1);
            printf("Номер авиарейса: %d\n", flights[i].flightNumber);
            printf("Время вылета: %s\n", flights[i].departureTime);
            printf("Время прилёта: %s\n", flights[i].arrivalTime);
            printf("Марка самолёта: %s\n", flights[i].airplaneModel);
            printf("Расстояние: %.2f\n", flights[i].distance);
            count++;
        }
    }
    if (count == 0) {
        printf("Нет данных об авиарейсах с направлением '%s'.\n", direction);
    }
}

float calculateAverageDistance(struct AIRPLANE flights[], int n) {
    float totalDistance = 0;
    for (int i = 0; i < n; i++) {
        totalDistance += flights[i].distance;
    }
    if (n > 0) {
        return totalDistance / n;
    } else {
        return 0;
    }
}

void printFlightCountsByModel(struct AIRPLANE flights[], int n) {
    printf("Количество авиарейсов для каждой марки самолёта:\n");
    for (int i = 0; i < n; i++) {
        int count = 1;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(flights[i].airplaneModel, flights[j].airplaneModel) == 0) {
                count++;
                flights[j].flightNumber = -1; // Помечаем авиарейсы, которые уже были учтены
            }
        }
        if (flights[i].flightNumber != -1) {
            printf("Марка самолёта '%s': %d\n", flights[i].airplaneModel, count);
        }
    }
}

int main() {
    struct AIRPLANE flights[MAX_FLIGHTS];
    int numFlights;

    printf("Введите количество авиарейсов (не более %d): ", MAX_FLIGHTS);
    scanf("%d", &numFlights);

    if (numFlights > MAX_FLIGHTS) {
        printf("Превышено максимальное количество авиарейсов.\n");
        return 0;
    }

    createFlights(flights, numFlights);

    printf("\n");

    printFlightWithLongestDuration(flights, numFlights);

    printf("\n");

    char direction[50];
    printf("Введите направление: ");
    getchar(); // Очистка буфера ввода
    fgets(direction, sizeof(direction), stdin);
    direction[strcspn(direction, "\n")] = '\0'; // Удаление символа новой строки

    printFlightsByDirection(flights, numFlights, direction);

    printf("\n");

    float averageDistance = calculateAverageDistance(flights, numFlights);
    printf("Среднее расстояние для всех авиарейсов: %.2f\n", averageDistance);

    printf("\n");

    printFlightCountsByModel(flights, numFlights);

    return 0;
}