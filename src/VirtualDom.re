open Main;
open Dom;
open Utils;

type attributes = list((string, string));

type patchType =
  | Replace
  | Children
  | Text
  | Props;

type patch = {
  patchType: patchType,
  content: option(node),
  attributes: option(attributes),
  moves: list(ListDiff.move),
};

type patches = IntMap(patch)

let nthChildren = (nodes: option(node), index: int): option('a) => {
    switch (nodes) {
      | None => None
      | Some({ children }) => {
        if (List.length(children) > index) {
          Some(List.nth(children, index))
        } else {
          None;
        }
      }
    }
};

let rec setPositions = (~node: node, ~initialPosition: int): int => {
  let position = ref(initialPosition);
  node.children |> List.iter(child => {
    position := position^ + setPositions(~node=child, ~initialPosition=position^);
  });
  position := position^ + 1;
  node.position = position^;
  position^;
}

let getPrevChildPosition = (children: list(node), index: int): int => switch (index) {
  | 0 => 0
  | _ => List.nth(children, index - 1).position
};

let diffProps = (oldNode: node, newNode: node) => {

  let changedProps = oldNode.attributes
   |> List.filter(
      ((oldKey, oldValue)) => List.exists(((newKey, newValue)) => newKey === oldKey && newValue !== oldValue, newNode.attributes),
    )
    |> List.map(((oldKey, oldValue)) => List.find(((newKey, newValue)) => oldKey === newKey, newNode.attributes))

  let newProps = newNode.attributes
    |> List.filter(
      ((newKey, _)) => !List.exists(((oldKey, _)) => oldKey !== newKey, oldNode.attributes)
    )

  List.append(changedProps, newProps);
}

let getPatches = (oldNode, newNode: option(node)): list(patch) => {
   switch (newNode) {
    | None => []
    | Some(node) => {
         /* TextNode content replacing */
        if (node.name === TEXT && oldNode.name === TEXT && node.text !== oldNode.text) {
            [{ patchType: Text, content: Some(node), attributes: None, moves: [] }];
        } else if (node.name === oldNode.name) {
            /* Diff props */
            let propsPatches = diffProps(oldNode, node);
            switch (propsPatches) {
              | [] => []
              | _ =>  [{ patchType: Props, attributes: Some(propsPatches), content: None, moves: [] }]
            }
        } else {
          [{ patchType: Replace, content: Some(node), attributes: None, moves: [] }];
        }
      }
   }
}

let getChildrenPatches = (oldChildren, newChildren): list(patch) => {
  let listDiff = ListDiff.getListDiff(oldChildren, newChildren);
  switch (listDiff.moves) {
    | [] => []
    | _ => [{ patchType: Children, attributes: None, content: None, moves: listDiff.moves }]
  };
};

let rec walker = (~oldNode, ~newNode: option(node), ~patches, ~index) => {
  let currentPatches = ref(patches);
  getPatches(oldNode, newNode) |> List.iter((patch) => {
    currentPatches := IntMap.add(index, patch, currentPatches^);
  });

  let childrenPatches = switch (newNode) {
      | None => []
      | Some(node) => {
        getChildrenPatches(oldNode.children, node.children) |> List.iter((patch) => {
          currentPatches := IntMap.add(index, patch, currentPatches^);
        });
        if (node.name === oldNode.name) {
          oldNode.children
            |> List.iteri((i, oldChildNode) => {
                let newChildNode = nthChildren(newNode, i);
                let currentNodeIndex = getPrevChildPosition(oldNode.children, index);
                currentPatches := walker(~oldNode=oldChildNode, ~newNode=newChildNode, ~patches=currentPatches^, ~index=(index + currentNodeIndex + i + 1));
              });
          [];
        } else {
          [];
        }
      }
  }

  currentPatches^;
}

let getDiff = (~oldNode, ~newNode: option(node)) => walker(~oldNode=oldNode, ~newNode=newNode, ~patches=IntMap.empty, ~index=0)
