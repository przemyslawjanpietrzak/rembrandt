open Main;

type moveType = Insert | Remove;
type move = { index: int, moveType: moveType, item: option(node) };
type moves = list(move);

type keyIndexes = {
  free: list(node),
  keyIndex: Hashtbl.t(string, int),
}

type diff = {
  moves: moves,
  children: list(option(node)),
}

let key = "key";

let identity = item => item;

let getItemKey = (node: node): option(string)  => {
  let item = node.attributes
    |> List.find(((key, value)) => key === "key" && value !== "");

  switch (item) {
    | (key, value) => Some(value)
    | exception Not_found => None
  };
};

let isInHashTable = (hashTable, optionalKey: option('a)): bool => switch (optionalKey) {
  | None => false;
  | Some(key) => Hashtbl.mem(hashTable, key);
}

let makeKeyIndexAndFree = (list: list(node)): keyIndexes => {
  let keyIndex = Hashtbl.create(10000);
  let free = ref([]);

  let _ = list |>
    List.iteri((i, item) => {
      let itemKey = getItemKey(item);
      let _ = switch (getItemKey(item)) {
        | None => {
          free := List.append(free^, [item])
        }
        | Some(itemKey) => {
          Hashtbl.add(keyIndex, itemKey, i);
        }
      }
    });
  {
    free: free^,
    keyIndex,
  }
}

let removeFromSimulateList = (collection: list('a), index: int): list('a) => {
  let rec removeFromSimulateListAcc = (collection, index: int, acc) => switch (collection) {
    | [] => []
    | [head, ...tail] => {
      if (index === 0) {
        List.append(acc, tail)
      } else {
        removeFromSimulateListAcc(tail, index - 1,  List.append(acc, [head]));
      }
    }
  }
  removeFromSimulateListAcc(collection, index, []);
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
        if (Hashtbl.mem(newKeyIndex, itemKey)) {
          let newItemIndex = Hashtbl.find(newKeyIndex, itemKey);
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
      simulateList := removeFromSimulateList(simulateList^, i^);
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
        } else if (isInHashTable(oldKeyIndex, itemKey)) {
          /* new item, just inesrt it */
          switch (getFromSimulateList(simulateList^, j^ + 1)) {
            | Some(nextItem) => {
              let nextItemKey = getItemKey(nextItem);
              Js.log({ nextItemKey });
              Js.log({ itemKey });
              if (nextItemKey === itemKey) {
                moves := List.append(moves^, [{ index: i, moveType: Remove, item: None }]);
                simulateList := removeFromSimulateList(simulateList^, j^);
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