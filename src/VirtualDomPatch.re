open Common
open Utils;
open VirtualDom;

type maps = StringMap.t(Dom.domElement) ;

let setProps = (element: Dom.domElement, attributes: attributes) => {
  attributes |> List.map(((key, value)) => {
    if (value === "") {
      Dom.removeAttribute(key, element);
    } else {
      Dom.setAttribute((key, value), element);
    }
  })
};

let reorderChildren = (element: Dom.domElement, moves: ListDiff.moves) => {
  let staticNodeList = ref(element.childNodes);
  let maps = ref(StringMap.empty);

  element.childNodes |> List.iter((childElement: Dom.domElement) => {
    if (childElement.nodeType === 1 && childElement.getAttribute("key") !== "") {
      maps := StringMap.add(childElement.getAttribute("key"), childElement, maps^);
    }
  });

  moves |> List.iter((move: ListDiff.move) => {
    switch (move.moveType, move.item) {
      | (Remove, None) => {
        let childToRemove = Dom.getNthChild(element.children, move.index);
        Dom.removeChild(element, childToRemove);
        staticNodeList := removeFromList(staticNodeList^, move.index);
      };
      | (Insert, Some(item)) => {
        let insertNode = {
          if (StringMap.mem(move.index |> string_of_int, maps^)) {
            /* maps[move.item.key].cloneNode(true) */
            StringMap.find(move.index |> string_of_int, maps^);
          } else {
            render(item);
          }
        }
        staticNodeList := replaceInList(staticNodeList^, move.index, insertNode);
        let _ = Dom.insertBefore(element, insertNode, Dom.getNthChild(element.childNodes, move.index));
      };
    }
  });
};

let applyPatches = (element: Dom.domElement, currentPatches: list(patch)) => {
  currentPatches |> List.iteri((i, patch) => {
    switch patch.patchType {
      | Replace => {
        switch patch.content {
          | Some(node) => {
            let newDomElement = render(node);
            Dom.replaceChild(element -> Dom.getParentNode, newDomElement, element) |> ignore;
          }
        }
      };
      | Props => {
        switch patch.attributes {
          | Some(attributes) => {
            setProps(element, attributes) |> ignore;
          }
        }
      };
      | Children => {
        reorderChildren(element, patch.moves) |> ignore;
      }
      | Text => {
        switch patch.content {
          | Some(node) => {
            Js.log("flag");
            let newDomElement = render(node);
            Dom.replaceChild(element -> Dom.getParentNode, newDomElement, element) |> ignore;
          };
        }
      };
    }
  });
}

let rec walker = (element: Dom.domElement, patches, step: int) => {
  let children = Dom.getChildren(element);
  children |> List.iteri((i, child) => {
    walker(child, patches, step + i + 1);
  });

  if (IntMap.mem(step, patches)) {
    let currentPatches = IntMap.find(step, patches);
    applyPatches(element, currentPatches)
  }
}

let patch = (node, patches) => walker(node, patches, 0);
