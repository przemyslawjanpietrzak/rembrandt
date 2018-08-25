open Common;
open Utils;

type moveType = Insert | Remove;
type move = { index: int, moveType: moveType, item: option(node) };
type moves = list(move);

type keyIndexes = {
  free: list(node),
  keyIndex: StringMap.t(int),
}

type diff = {
  moves: moves,
  children: list(option(node)),
}

let key = "key";

let identity = item => item;

let getItemKey = (node: node): option(string)  => {

  switch (List.find(((key, value)) => key === "key" && value !== "", node.attributes)) {
    | (key, value) => Some(value)
    | exception Not_found => None
  };
};

let isInMap = (map, optionalKey: option('a)): bool => switch (optionalKey) {
  | None => false;
  | Some(key) => StringMap.mem(key, map);
}

let makeKeyIndexAndFree = (list: list(node)): keyIndexes => {
  let keyIndex = ref(StringMap.empty);
  let free = ref([]);

  let _ = list |>
    List.iteri((i, item) => {
      let itemKey = getItemKey(item);
      let _ = switch (getItemKey(item)) {
        | None => {
          free := List.append(free^, [item])
        }
        | Some(itemKey) => {
          keyIndex := StringMap.add(itemKey, i, keyIndex^)
        }
      }
    });
  {
    free: free^,
    keyIndex: keyIndex^,
  }
}

let getFromSimulateList =  (collection: list('a), index: int): 'a => {
  if (List.length(collection) > index) {
    List.nth(collection, index);
  } else {
    None;
  }
}

let getListDiff = (oldNodes: list(node), newNodes: list(node)): diff => {
  let oldMap = makeKeyIndexAndFree(oldNodes);
  let newMap = makeKeyIndexAndFree(newNodes);

  let newFree = newMap.free;

  let oldKeyIndex = oldMap.keyIndex;
  let newKeyIndex = newMap.keyIndex;

  let moves = ref([]);
  let children = ref([]);
  let freeIndex = ref(0);

  /* first pass to check item in old list: if it's removed or not */
  oldNodes |> List.map((node) => {
    switch (getItemKey(node)) {
      | None => {
        let freeItem = List.nth(newFree, freeIndex^);
        children := List.append(children^, [Some(freeItem)]);
        freeIndex := freeIndex^ + 1;
      }
      | Some(itemKey) => {
        if (StringMap.mem(itemKey, newKeyIndex)) {
          let newItemIndex = StringMap.find(itemKey, newKeyIndex);
          let newItem = List.nth(newNodes, newItemIndex);
          children := List.append(children^, [Some(newItem)]);
        } else {
          children := List.append(children^, [None]);
        }
      }
    }
    node;
  });
  let simulateList = ref(List.map(identity, children^));
  /* remove items no longer exist */
  let i = ref(0);
  while (i^ < List.length(simulateList^)) {
    if (List.nth(simulateList^, i^) === None) {
      moves := List.append(moves^, [{ index: i^, moveType: Remove, item: None }]);
      simulateList := Utils.removeFromList(simulateList^, i^);
    } else {
      i := i^ + 1;
    }
  }

  let j = ref(0);
  newNodes |> List.iteri((i, item) => {
    let itemKey = getItemKey(item);
    switch (getFromSimulateList(simulateList^, j^)) {
      | Some(simulateItem) => {
        let simulateItemKey = getItemKey(simulateItem);
        if (itemKey === simulateItemKey) {
          j := j^ + 1;
        } else if (isInMap(oldKeyIndex, itemKey)) {
          /* new item, just inesrt it */
          switch (getFromSimulateList(simulateList^, j^ + 1)) {
            | Some(nextItem) => {
              let nextItemKey = getItemKey(nextItem);
              if (nextItemKey === itemKey) {
                moves := List.append(moves^, [{ index: i, moveType: Remove, item: None }]);
                simulateList := Utils.removeFromList(simulateList^, j^);
                j := j^ + 1;
                /* after removing, current j is right, just jump to next one */
              } else {
                /* else insert item */
                moves := List.append(moves^, [{ index: i, moveType: Insert, item: Some(item) }]);
              }
            }
            | None => 42 |> ignore;
          }
        } else {
          /* TODO: dead */
          moves := List.append(moves^, [{ index: i, moveType: Insert, item: Some(item) }]);
        }
      }
      | None => {
        moves := List.append(moves^, [{ index: i, moveType: Insert, item: Some(item) }]);
      }
    }
  });

  {
    moves: moves^,
    children: children^,
  }
}