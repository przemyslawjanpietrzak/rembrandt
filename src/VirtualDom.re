open Main;
open Dom;

type optionalNode =
  | Node
  | Null;

let changed = (node1: node, node2: node) =>
  node1.name !== node2.name;

let max = (a: int, b: int) => a > b ? a : b;

let nth = (items: list(node), index: int): node => {
  if (List.length(items) >= index) {
    List.nth(items, index);
  } else {
    null();
  }
}

/* let rec updateElement = (~parent: domElement, ~newNode: node, ~oldNode: node, ~index: int): domElement => {
  if (oldNode.null) {
    appendChild([render(newNode)], parent)
  } else if (newNode.null) {
    List.nth(parent.childNodes, index)
      |>removeChild(parent);
  } else if (changed(newNode, oldNode)) {
    replaceChild(
      parent,
      render(newNode),
      render(oldNode),
    )
  } else {
    let newLength = List.length(newNode.children);
    let oldLength = List.length(oldNode.children);

    for (i in max(newLength, oldLength) downto 0) {
      updateElement(
        ~parent=List.nth(parent.children, index),
        ~newNode=nth(newNode.children, i),
        ~oldNode=nth(oldNode.children, i),
        ~index=i,
      )
    }
    parent;
  }
}; */