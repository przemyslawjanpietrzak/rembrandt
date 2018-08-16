open Main;
open Dom;

type attributes = list((string, string));

type patch = {
  patchType: string,
  content: option(node),
  attributes: option(attributes),
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

/* let diffChildren = (oldChildren, newChildren, index, patches, currentPatch) => {
  let diffs = listDiff(oldChildren, newChildren, "key");
  let newChildren = diffs.children;

  /* if (diffs.moves.length) {
    let reorderPatch = { patchType: "REORDER", moves: diffs.moves }
    /* currentPatch.push(reorderPatch); */
  } else {} */

  let leftNode = null;
  let currentNodeIndex = index;
  List.iter((child, i) => {
    let newChild = newChildren[i]
    currentNodeIndex = (leftNode && leftNode.count)
      ? currentNodeIndex + leftNode.count + 1
      : currentNodeIndex + 1
    dfsWalk(child, newChild, currentNodeIndex, patches)
    leftNode = child
  }, oldChildren)
} */

let getPatch = (oldNode, newNode: option(node)): patches => {
   let currentPatch: list(patch) = [];
   switch (newNode) {
    | None => currentPatch
    | Some(node) => {
         /* TextNode content replacing */
        if (node.name === TEXT && oldNode.name === TEXT && node.text !== oldNode.text) {
            let patch = { patchType: "text", content: Some(node), attributes: None };
            List.append(currentPatch, [patch]);
        } else if (node.name === oldNode.name) {
            /* Diff props */
            let propsPatches = diffProps(oldNode, node);
            let patch = { patchType: "props", attributes: Some(propsPatches), content: None };
            List.append(currentPatch, [patch]);
        } else {
          let patch = { patchType: "replace", content: Some(node), attributes: None };
          List.append(currentPatch, [patch]);
        }
      }
   }
}

let rec walker = (~oldNode, ~newNode: option(node), ~index=0): list(patches) => {
  let patch = getPatch(oldNode, newNode: option(node));
  let patches = ref([patch]);
  let childrenPatches = switch (newNode) {
      | None => []
      | Some(node) => {
        if (node.name === oldNode.name) {
          oldNode.children
            |> List.mapi((i, oldChildNode) => {
                let newChildNode = nthChildren(newNode, i);
                walker(~oldNode=oldChildNode, ~newNode=newChildNode, ~index=index);
              })
            |> List.flatten;
        } else {
          [];
        }
      }
  }
  patches := List.append(patches^, childrenPatches);
  patches^;
}