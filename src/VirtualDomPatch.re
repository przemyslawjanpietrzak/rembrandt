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

let applyPatches = (element: Dom.domElement, currentPatches) => {
  let r = a => 42 |> ignore;
  currentPatches |> IntMap.iter((key) => {
    let patch = IntMap.find(key, currentPatches);
    switch patch.patchType {
      | Replace => {
        switch patch.content {
          | Some(node) => {
            let newDomElement = render(node);
            Dom.replaceChild(element.parentElement, newDomElement, element)
            r;
          }
        }
      };
      | Props => {
        switch patch.attributes {
          | Some(attributes) => {
            setProps(element, attributes)
            r;
          }
        }
      };
      | Children => {
        reorderChildren(element, patch.moves);
        r;
      }
      | Text => {
        switch patch.content {
          | Some(node) => {
            let newDomElement = render(node);
            Dom.replaceChild(element.parentElement, newDomElement, element);
            r;
          };
        }
      };
    }
  });

}