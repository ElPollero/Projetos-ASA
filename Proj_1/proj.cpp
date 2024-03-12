#include <iostream>
#include <vector>

using namespace std;

int maxPlateValue(pair<int, int> plateSize, int amountOfTypes, vector<vector<int>> types) {
    int pLength = plateSize.first;
    int pWidth = plateSize.second;

    vector<vector<int>> dp(pLength + 1, vector<int>(pWidth + 1, 0));

    for (int x = 1; x <= pLength; ++x) {
        for (int y = 1; y <= pWidth; ++y) {

            int verticalValue = 0;
            int horizontalValue = 0;

            if (dp[x][y] != 0 ){
                continue;
            }
            for (int xAux = 1; xAux < x; ++xAux) 
                verticalValue = max(verticalValue, dp[xAux][y] + dp[x-xAux][y]);

            for(int yAux=1; yAux < y; ++yAux)
                horizontalValue = max(horizontalValue, dp[x][yAux] + dp[x][y-yAux]);

            int bestCut = max(verticalValue, horizontalValue);

            dp[x][y] = max(bestCut, types[x][y]);

            if  (y <= plateSize.first && x <= plateSize.second)
                dp[y][x] = max(bestCut, types[x][y]);
        }
    }
    return dp[pLength][pWidth];
}

int main(){
    // Leitura dos dados de entrada
    pair<int, int> plateSize;
    scanf("%d %d", &plateSize.first, &plateSize.second);

    int amountOfTypes;
    scanf("%d", &amountOfTypes);

    vector<vector<int>> types(plateSize.first + 1, vector<int>(plateSize.second + 1, 0));

    for (int i = 0; i < amountOfTypes; ++i) {
        int length = 0;
        int width = 0;
        int price = 0;
        scanf("%d %d %d", &length, &width, &price);

        if  (length <= plateSize.first && width <= plateSize.second)
            types[length][width] = max(types[length][width], price);

        if  (width <= plateSize.first && length <= plateSize.second)
            types[width][length] = max(types[width][length], price);
    }
    // Chamada da função
    int result = maxPlateValue(plateSize, amountOfTypes, types);
    // Saída
    cout << result << endl;
    return 0;
}

