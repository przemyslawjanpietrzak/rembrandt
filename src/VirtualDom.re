open Main;
open Dom;

type attributes = list((string, string));

type patch = {
  patchType: string,
  content: option(node),
  attributes: option(attributes),
  moves: list(ListDiff.move),
};

type patches = list(patch);

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

let isIgnoredNode = node => false;

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
            [{ patchType: "text", content: Some(node), attributes: None, moves: [] }];
        } else if (node.name === oldNode.name) {
            /* Diff props */
            let propsPatches = diffProps(oldNode, node);
            switch (propsPatches) {
              | [] => []
              | _ =>  [{ patchType: "props", attributes: Some(propsPatches), content: None, moves: [] }]
            }
        } else {
          [{ patchType: "replace", content: Some(node), attributes: None, moves: [] }];
        }
      }
   }
}

let getChildrenPatches = (oldChildren, newChildren): list(patch) => {
  let listDiff = ListDiff.getListDiff(oldChildren, newChildren);
  switch (listDiff.moves) {
    | [] => []
    | _ => [{ patchType: "children", attributes: None, content: None, moves: [] }]
  };
};

/* let diffChildren =  (oldChildren, newChildren, index, patches, currentPatch) => {
  let diffs = listDiff(oldChildren, newChildren)
  newChildren = diffs.children

  if (diffs.moves.length) {
    let reorderPatch = { type: patch.REORDER, moves: diffs.moves }
    currentPatch.push(reorderPatch)
  }

  let leftNode = null
  let currentNodeIndex = index
  _.each(oldChildren, function (child, i) {
    let newChild = newChildren[i]
    currentNodeIndex = (leftNode && leftNode.count)
      ? currentNodeIndex + leftNode.count + 1
      : currentNodeIndex + 1
    dfsWalk(child, newChild, currentNodeIndex, patches)
    leftNode = child=
  })
} */
let rec walker = (~oldNode, ~newNode: option(node), ~patches=Hashtbl.create(10000), ~index) => {
  getPatches(oldNode, newNode) |> List.iter((patch) => {
    Hashtbl.add(patches, index, patch) |> ignore;
  });

  let childrenPatches = switch (newNode) {
      | None => []
      | Some(node) => {
        getChildrenPatches(oldNode.children, node.children) |> List.iter((patch) => {
          Hashtbl.add(patches, index, patch) |> ignore;
        });
        if (node.name === oldNode.name) {
          oldNode.children
            |> List.iteri((i, oldChildNode) => {
                let newChildNode = nthChildren(newNode, i);
                let currentNodeIndex = getPrevChildPosition(oldNode.children, index);
                walker(~oldNode=oldChildNode, ~newNode=newChildNode, ~patches=patches, ~index=index + currentNodeIndex + 1) |> ignore;
              });
          [];
        } else {
          [];
        }
      }
  }

  patches;
}
