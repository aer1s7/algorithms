#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Courier {
    int totalDistance;
    vector<int> orders;
    Courier(){
        totalDistance = 0;
    }
};

int assignOrders(vector<int> orders, int k, int t, vector<Courier>& couriers){
    sort(orders.begin(), orders.end(), greater<int>());
    for (int order : orders){
        bool assigned = false;

        for (int i = 0; i < couriers.size(); i++){
            if (couriers[i].totalDistance + order <= t){
                couriers[i].orders.push_back(order);
                couriers[i].totalDistance += order;
                assigned = true;
                break;
            }
        }

        if (!assigned){
            if (couriers.size() == k){
                return -1;
            }

            Courier newCourier;
            newCourier.orders.push_back(order);
            newCourier.totalDistance += order;
            couriers.push_back(newCourier);
        }
    }
    return couriers.size();
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    int n = 8;
    int k = 5;
    int t = 10;
    vector<int> orders = {4,3,7,2,6,5,8,1};
    cout << "Количество заказов: " << n << endl;
    cout << "Количество курьеров: " << k << endl;
    cout << "Максимальная дистанция: " << t << endl;
    cout << "Исходные заказы: ";
    for (int order : orders){
        cout << order << " ";
    }
    cout << endl;

    vector<Courier> couriers;

    int ans = assignOrders(orders, k, t, couriers);
    if (ans == -1){
        cout << "Распределение невозможно." << endl;
    } else {
        cout << "Минимальное число курьеров: " << ans << endl;
    }
}