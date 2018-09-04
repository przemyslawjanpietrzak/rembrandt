open Common;
open Dom;
open Utils;

type attributes = list((string, string));

type patchType =
  | Replace
  | Children
  | Text
  | Props;

type patch = {
  patchType,
  content: option(node),
  attributes: option(attributes),
  moves: list(ListDiff.move),
};

type patches = IntMap.t(list(patch));

let nthChildren = (nodes: option(node), index: int): option('a) =>
  switch (nodes) {
  | None => None
  | Some({children}) =>
    if (List.length(children) > index) {
      Some(List.nth(children, index));
    } else {
      None;
    }
  };

/* TODO: */
let addPatch = (patch: list(patch), patches: patches, index: int): patches =>
  switch (patch) {
  | [] => patches
  | _ =>
    if (IntMap.mem(index, patches)) {
      let existingPatch = IntMap.find(index, patches);
      let concatedPatches = List.append(existingPatch, patch);
      IntMap.add(index, concatedPatches, patches);
    } else {
      IntMap.add(index, patch, patches);
    }
  };

let getPrevChildPosition = (children: list(node), index: int): int =>
  switch (index) {
  | 0 => 0
  | _ =>
    switch (List.nth(children, index - 1)) {
    | exception nth => 0
    | child => child.position
    }
  };

let getPatches = (oldNode, newNode: option(node)): list(patch) =>
  switch (newNode) {
  | None => []
  | Some(node) =>
    /* TextNode content replacing */
    if (node.name == TEXT
        && oldNode.name == TEXT
        && node.text != oldNode.text) {
      [{patchType: Text, content: Some(node), attributes: None, moves: []}];
    } else if (node.name === oldNode.name) {
      /* Diff props */
      let propsPatches = DiffProps.diffProps(oldNode, node);
      switch (propsPatches) {
      | [] => []
      | _ => [
          {
            patchType: Props,
            attributes: Some(propsPatches),
            content: None,
            moves: [],
          },
        ]
      };
    } else {
      [
        {
          patchType: Replace,
          content: Some(node),
          attributes: None,
          moves: [],
        },
      ];
    }
  };

let getChildrenPatches = (oldChildren, newChildren): list(patch) => {
  let listDiff = ListDiff.getListDiff(oldChildren, newChildren);
  switch (listDiff.moves) {
  | [] => []
  | _ => [
      {
        patchType: Children,
        attributes: None,
        content: None,
        moves: listDiff.moves,
      },
    ]
  };
};

let rec walker = (~oldNode, ~newNode: option(node), ~patches, ~index) => {
  let currentPatches = ref(patches);
  let patches = getPatches(oldNode, newNode);
  currentPatches := addPatch(patches, currentPatches^, index);

  let _childrenPatches =
    switch (newNode) {
    | None => []
    | Some(node) =>
      let childrenPatches =
        getChildrenPatches(oldNode.children, node.children);
      currentPatches := addPatch(childrenPatches, currentPatches^, index);

      if (node.name === oldNode.name) {
        let currentNodeIndex = ref(index);
        oldNode.children
        |> List.iteri((i, oldChildNode) => {
             let newChildNode = nthChildren(newNode, i);
             let prevChildPosition =
               getPrevChildPosition(oldNode.children, i);
             currentNodeIndex := currentNodeIndex^ + prevChildPosition + 1;
             currentPatches :=
               walker(
                 ~oldNode=oldChildNode,
                 ~newNode=newChildNode,
                 ~patches=currentPatches^,
                 ~index=currentNodeIndex^,
               );
           });
        [];
      } else {
        [];
      };
    };

  currentPatches^;
};

let getDiff = (~oldNode, ~newNode: option(node)): IntMap.t(list(patch)) =>
  walker(~oldNode, ~newNode, ~patches=IntMap.empty, ~index=0);