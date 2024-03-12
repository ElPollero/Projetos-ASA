#include <iostream>
#include <vector>
#include <stack>

using namespace std;
int indexSCC = 0;

void processNeighbours(const std::vector<std::vector<int>> & adjacencias, int atual, std::vector<bool> & visitado, std::stack<int> &pilha, bool &temVizinhosNaoVisitados)
{
for (int vizinho : adjacencias[atual]) {
            if (!visitado[vizinho]) {
                visitado[vizinho] = true;
                pilha.push(vizinho);
                temVizinhosNaoVisitados = true;
                break;
            }
        }
}

void processVertices(std::vector<int> &arraySCC, int vizinho, int vertice, std::vector<int> &resultados, int &saltos)
{
    if (arraySCC[vizinho] == arraySCC[vertice] )
    {
        // Vertices in diff SCC
        resultados[vertice] = max(resultados[vizinho] , resultados[vertice]);
    }
    else if (arraySCC[vertice] != 0 && arraySCC[vizinho] != 0)
    {
        resultados[vertice] = max(resultados[vizinho] + 1, resultados[vertice]);
    }
    saltos = max(saltos, resultados[vertice]);
}

int dfsSCC(int vertice, const vector<vector<int> >& adjacencias, vector<int>& arraySCC, vector<bool>& visitado,
vector<int>& resultados) {
    int saltos = 0;
    stack<int> pilha = stack <int>();
    pilha.push(vertice);
    visitado[vertice] = true;
    

    while (!pilha.empty()) {
        bool temVizinhosNaoVisitados = false;
        int atual = pilha.top();
        processNeighbours(adjacencias, atual, visitado, pilha, temVizinhosNaoVisitados);
        if(!temVizinhosNaoVisitados){
            pilha.pop();
            
            arraySCC[atual] = indexSCC;
            arraySCC[vertice] = indexSCC;
            for (int vizinho : adjacencias[vertice]) {
                processVertices(arraySCC, vizinho, vertice, resultados, saltos);
            }

            if(vertice != atual) {
                for (int vizinho : adjacencias[atual]) {
                    processVertices(arraySCC, vizinho, atual, resultados, saltos);
                }
            }
        }
    }
    return saltos;
}

void dfsTopologica(int vertice, const vector<vector<int> >& adjacencias, vector<bool>& visitado, stack<int>& pilha) {
    visitado[vertice] = true;  // Mark the starting vertex as visited
    stack<int> pilhaDFS = stack <int>();  // Par (vertice, indice_vizinho)
    pilhaDFS.push(vertice);

    while (!pilhaDFS.empty()) {
        bool temVizinhosNaoVisitados = false;
        int atual = pilhaDFS.top();

        processNeighbours(adjacencias, atual, visitado, pilhaDFS, temVizinhosNaoVisitados);

        // If there are no unvisited neighbors, pop from the stack
        if (!temVizinhosNaoVisitados) {
            pilhaDFS.pop();
            pilha.push(atual);
        }
    }
}

int calcularMaxSaltos(int n, const vector<vector<int> >& grafo, const vector<vector<int> >& grafoTransposto) {
    
    stack<int> pilha1 = stack<int>();
    vector<bool> visitado(n + 1);
    // Preencher a pilha com a ordem topológica inversa

    for (int i = 1; i <= n; i++) {
        if (!visitado[i]) {
            dfsTopologica(i, grafo, visitado, pilha1);
        }
    }

    // Reinicializar vetor de visitados
    fill(visitado.begin(), visitado.end(), false);
    //printStack(pilha);
    int maxSaltos = 0;
    vector<int>resultados(n + 1, 0);
    vector<int>arraySCC(n + 1, 0);

    // Calcular SCCs e número máximo de saltos
    while (!pilha1.empty()) {
        int vertice = pilha1.top();
        pilha1.pop();

        if (!visitado[vertice]) {
            indexSCC++;
            maxSaltos = max(maxSaltos, dfsSCC(vertice, grafoTransposto, arraySCC, visitado, resultados));
        }
    }
    return maxSaltos;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    vector<vector<int> > grafo(n + 1);
    vector<vector<int> > grafoTransposto(n + 1);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);

        if (x < n + 1 && y < n + 1) {
            grafo[x].push_back(y);
            grafoTransposto[y].push_back(x);
        }
    }

    int resultado = calcularMaxSaltos(n, grafo, grafoTransposto);

    printf("%d\n", resultado);

    return 0;
}