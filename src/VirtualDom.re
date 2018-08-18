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

let getPatch = (oldNode, newNode: option(node)): option(patch) => {
   switch (newNode) {
    | None => None
    | Some(node) => {
         /* TextNode content replacing */
        if (node.name === TEXT && oldNode.name === TEXT && node.text !== oldNode.text) {
            Some({ patchType: "text", content: Some(node), attributes: None });
        } else if (node.name === oldNode.name) {
            /* Diff props */
            let propsPatches = diffProps(oldNode, node);
            switch (propsPatches) {
              | [] => None
              | _ =>  Some({ patchType: "props", attributes: Some(propsPatches), content: None })
            }
        } else {
          Some({ patchType: "replace", content: Some(node), attributes: None });
        }
      }
   }
}

let rec walker = (~oldNode, ~newNode: option(node), ~patches=Hashtbl.create(10000), ~index=0) => {
  let _ = switch (getPatch(oldNode, newNode: option(node))) {
    | None => None
    | Some(patch) => {
        let _ = Hashtbl.add(patches, index, patch);
        None;
    }
  };
  let childrenPatches = switch (newNode) {
      | None => []
      | Some(node) => {
        if (node.name === oldNode.name) {
          oldNode.children
            |> List.mapi((i, oldChildNode) => {
                let newChildNode = nthChildren(newNode, i);
                walker(~oldNode=oldChildNode, ~newNode=newChildNode, ~patches=patches, ~index=index + 1);
                oldChildNode;
              });
          [];
        } else {
          [];
        }
      }
  }

  patches;
}