#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

int minRooms(vector<pair<int, int>> exams){
    int k = exams.size();

    vector<int> startTimes;
    vector<int> endTimes;

    for (int i = 0; i < k; i++){
        startTimes.push_back(exams[i].first);
        endTimes.push_back(exams[i].second);
    }

    sort(startTimes.begin(), startTimes.end());
    sort(endTimes.begin(), endTimes.end());

    int curRooms = 0;
    int maxRooms = 0;
    int start = 0;
    int end = 0;

    while (start < k){
        if (startTimes[start] < endTimes[end]){
            curRooms++;
            maxRooms = max(curRooms, maxRooms);
            start++;
        } else {
            curRooms--;
            end++;
        }
    }
    return maxRooms;
}

int main(){
    setlocale(LC_ALL, "ru_RU.UTF-8");
    vector<pair<int,int>> exams = {{1,4}, {2,5}, {6,8}};
    cout << "Расписание: " << endl;
    for (int i = 0; i < exams.size(); i++){
        cout << "Начало: " << exams[i].first << ", конец: " << exams[i].second << endl;
    }
    int ans = minRooms(exams);
    cout << "Минимальное кол-во аудиторий: " << ans << endl;
}