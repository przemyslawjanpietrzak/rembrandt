open Common;

let rec setPositions = (~node: node, ~initialPosition: int): int => {
  let position = ref(initialPosition);
  node.children |> List.iter(child => position := position^ + child.position);
  position := position^ + 1;
  node.position = position^;
  position^;
};