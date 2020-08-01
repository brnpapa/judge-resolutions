#include <bits/stdc++.h>
using namespace std;

/*
   Motivação: dado um undirected graph G(V, E), encontre as bridges (or cut edges) e os articulation points (or cut vertices), ou seja, as arestas e vértices cuja remoção aumenta o número de componentes conectados de G (desconecta G).
*/

/* inputs */
vector<vector<int>> adj_list;
int V;

/* outputs */
vector<bool> is_art;             // is_art[u]: vértice u é um art point?
vector<pair<int, int>> bridges;  // u -> v que são bridge edges


const int UNVISITED = -1;

vector<int> order;  // order[v]: indicador da ordem de visitação do vértice pela DFS
vector<int> low;    // low[v]: menor order alcançável a partir de v (inclusive ele mesmo) na árvore gerada (pela DFS)
vector<int> parent; // parent[v]: pai de v na árvore gerada (pela DFS)

int count_order;
int root, root_out_degree; // raiz, quantas arestas saem dela (na árvore gerada pela DFS)

/* O(V+E) */
void dfs(int u) {
   low[u] = order[u] = count_order++;

   // para cada aresta u -> v
   for (int v : adj_list[u]) {
      if (order[v] == UNVISITED) {
         parent[v] = u;
         if (u == root) root_out_degree++; // p/ art point
         dfs(v);

         // callback propagation below

         low[u] = min(low[u], low[v]);
         if (order[u] <= low[v]) is_art[u] = true;
         if (order[u] < low[v])  bridges.push_back(make_pair(u, v));
      }
      // v já foi visitado
      else if (v != parent[u])         // é um ciclo não-direto (back edge)
         low[u] = min(low[u], low[v]); // low[v] == order[v], pois aqui v é a "raiz" do ciclo
   }
}

/* O(V+E) */
void tarjan() {
   count_order = 0;
   order.assign(V, -1); low.assign(V, -1); parent.assign(V, -1);
   is_art.assign(V, false); bridges.resize(V);

   for (int u = 0; u < V; u++) 
      if (order[u] == UNVISITED) {
         root = u, root_out_degree = 0;
         dfs(u);
         // caso especial do art point
         is_art[u] = root_out_degree >= 2; 
      }
}

/* e.g */
int main() {
   tarjan();
   return 0;
}