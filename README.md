# Graphs‑MST

A tiny C program that builds an undirected, weighted graph with an adjacency‑list structure and prints its **Minimum Spanning Tree (MST)** using **Prim’s algorithm**.

---

## ✨ What’s inside?

| Function / Struct      | Purpose                                              |
|------------------------|------------------------------------------------------|
| `Graph`, `AdjList`, `Node` | Lightweight adjacency‑list representation           |
| `initializeGraph()`    | Allocate a graph with *V* vertices                   |
| `insertEdge()`         | Add an undirected, weighted edge                     |
| `checkCycle()`         | Detect cycles via Union‑Find (helper, not used)      |
| `generatePrimMST()`    | Classic Prim’s algorithm (O(V²)) returning an MST    |
| `displayGraph()`       | Pretty‑print adjacency lists                         |
| `displayMST()`         | Pretty‑print the resulting MST                       |

---

## 📝 Customising

* **Graph size / edges** – edit the `V` constant and the `insertEdge` calls in `main()`.
* **Edge weights** – change the third argument of each `insertEdge`.
* **Cycle checking** – call `checkCycle(graph, src, dest)` before adding edges if you need to prevent cycles.

---

## ⚖️ License

MIT — do whatever you like, just keep the notice.
