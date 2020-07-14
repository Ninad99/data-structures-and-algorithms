const graph = [
  [1,9],
  [0,8],
  [3],
  [2,4,5,7],
  [3],
  [3,6],
  [5,7],
  [3,6,10,11],
  [1,7,9],
  [0,8],
  [7,11],
  [7,10]
];
const visited = new Array(12).fill(false);
let path = "";

function dfs(index, graph, visited) {
  if (visited[index]) {
    path = path + ` -> ${index}`;
    return;
  }
  console.log("Visiting node ", index);
  visited[index] = true;
  path = path + ` -> ${index}`;
  const neighbours = graph[index];
  for (const n of neighbours) {
    dfs(n, graph, visited);
  }
}
dfs(0, graph, visited);

console.log(path);
