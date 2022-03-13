## Backtracking: 해를 찾는 도중 해가 아니어서 막히면, 되돌아가서 다시 해를 찾아가는 기법을 말한다. 최적화 문제와 결정 문제를 푸는 방법이 된다.

### DFS & Backtracking
* 깊이 우선 탐색(DFS)
  * DFS는 가능한 모든 경로를 탐색, 불필요할 것 같은 경로를 사전에 차단하거나하는 등의 행동이 없으므로 경우의 수를 줄이지 못한다.
  * 따라서 N! 가지의 경우의 수를 가진 문제는 DFS로 처리가 불가능할 것입니다.